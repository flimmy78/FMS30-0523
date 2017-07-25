#include "matrox_interface_consumer.h"

#include <MatroxDSXsdk.h>
#include <MatroxDSXsdkGuids.h>
#include <MvFlexAPI.h>
#include "SfpSdiStatusCallback.h"
#include "ErrorNotificationCallback.h"
#include "MvErrorCallbackHandler.h"
#include <assert.h>

#include <assert.h>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>

namespace caspar {
	namespace matrox {
		//板卡上的信息，初始化就应该用
		struct OutSCardInfo
		{
			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			SMvGeneralHardwareInformation     sHwInfo;
			//光端子
			std::vector<TMvSmartPtr<IMvSfpSdi> > vecpJSfp;
			std::vector<TMvSmartPtr<CSfpSdiStatusCallback> > vecpJSfpCallback;
			////
			//sdi输出虚拟通道不是物理通道
			std::vector<TMvSmartPtr<IMvSdiVideoOutputConnector> >				OutputConnectors;
			//声音通道数 一般在输出模块上不需要知道这个，是FMS设置通道数量的
			std::vector<TMvSmartPtr<IMvSdiEmbeddedAudioOutputPairConnector>>		SDIEAAudioOutConnectors;
		};
		//fms frame 和matrox frame 互换的中间量
		struct transferconfig
		{
			void * pVideoBuffer;
			void * pAudioBuffer;
			SMvVancPacket in_paVancPackets;
			uint32_t in_ui32PacketCount;
			bool secondfiel;
			unsigned int RowPitchInbytes;

		};



		struct matrox_interface_consumer::impl : public CMvUnknown, public IMvSystemClockNotificationCallback
		{
			//zanc

			MVDECLARE_IUNKNOWN;
			//COM接口
			TMvSmartPtr<IMvSystemConfiguration>				m_IMvSystemConfiguration_ = NULL;
			//板卡数量记录
			std::vector<OutSCardInfo>						m_CardConfigs;
			//指定所需板卡的序号，从0开始计数，即：板卡索引
			unsigned int									m_Card = 0;
			//指定所需要的虚拟SDI输入的信号通道索引，从0开始
			unsigned int									m_Sdi = 0;
			//锁相
			TMvSmartPtr<IMvSystemClock>						m_pJClock = NULL;
			//拓扑对象
			TMvSmartPtr<IMvSystemTopology>					m_pJSystemTopology = NULL;
			//node
			TMvSmartPtr<IMvNode>							m_pJIOCardNodeForPlayback = NULL;
			TMvSmartPtr<IMvHostNode>						m_pJIOHostNodeForPlayback = NULL;
			TMvSmartPtr<IMvVancDataPackets>					m_pJVancDataPackets = NULL;

			//获取队列接口
			TMvSmartPtr<IMvFlexEngine>						m_pJFlexEngine = NULL;
			//Asynch error notification
			TMvSmartPtr<IMvErrorNotification>				m_pJErrorNotification = NULL;
			TMvSmartPtr<IMvErrorNotificationCallback>		m_pJCardErrorCallback = NULL;

			TMvSmartPtr<IMvSystemTopologyErrorCallback>		m_pJSystemTopologyErrorCallback = NULL;

			//Video user buffer surface pool manager
			TMvSmartPtr<IMvSurfacePool>						m_pJVideoUserBufferSurfacePoolForPlayback = NULL;
			TMvSmartPtr<IMvAudioSamplesPool>				m_pJAudioSamplesPoolForPlayback = NULL;
			SMvUserBufferSurfaceDescription					m_sUserBufferSurfaceDescription;
			SMvUserBufferAudioSamplesDescription			m_sUserBufferAudioSamplesDescription;

			//Video surface/Auduo sample aynch error callback
			TMvSmartPtr<IMvSurfacePoolCallback>				m_pJVideoSurfaceAsynchErroCallback = NULL;
			TMvSmartPtr<IMvAudioSamplesPoolCallback>		m_pJAudioSamplesAsynchErroCallback = NULL;


			TMvSmartPtr<CMvErrorCallbackHandler>			m_pJErrorCallback;
			uint32_t										m_ui32WriteToReadDelayInFrame = 1;
			uint32_t										m_ui32WriteToReadDelayInFrameOutputNode = 0;
			uint32_t										m_ui32DepthInFrame = 12;

			//FMS
			SMvResolutionInfo								m_Out_Resolution;

			//指定输出的通道数
			int												m_preset_Channels;
			bool											m_IsVanc;
			bool											m_IsKey;
			std::wstring									m_ratio;
			core::video_format								m_format_;

			uint64_t										m_ui64LastPlaybackSampleTime = 0;
			/////////////////////////
			tbb::concurrent_bounded_queue<transferconfig>	BuffersQueue;


			bool											m_isRunning = false;

			boost::thread									thread_;

			impl(consumer_need need, core::video_format format, int channels)
				:CMvUnknown(L"ConsumerMvsNotificationCallback", NULL)
				, m_Card(need.card)
				,m_Sdi(need.sdi)
				, m_format_{ format }
				, m_preset_Channels(channels)
				,m_ratio(need.ratio)
				, m_IsVanc(need.vanc)
				, m_IsKey(need.key)
			{
				CMvHResult oHr = MV_NOERROR;

				// 1.Initialize system configuration com接口  板卡参数等等
				oHr = _SysConfiguration();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox consumer, _SysConfiguration"));
				}

				// 2.Create system topology
				oHr = _CreateSystemTopology();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox consumer, _CreateSystemTopology"));
				}

				// 3. Create FlexEngine

				oHr = _GetFlexEngine();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox consumer, _GetFlexEngine"));
				}
				// 4. Creating video/audio pool
				oHr = _CreateVideoAudioPoolManagers();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox consumer, _CreateVideoAudioPoolManagers"));
				}

				// 5. Set card asynch error callback

				oHr = m_CardConfigs[m_Sdi].pJCardConfig->GetErrorNotification(&m_pJErrorNotification);
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox consumer, card GetErrorNotification error"));
				}
				if (m_pJErrorNotification == NULL)
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info("m_pJErrorNotification NULL")
						<< boost::errinfo_api_function("in matrox consumer, GetErrorNotification"));
				}

				m_pJCardErrorCallback = new CErrorNotificationCallback;
				if (m_pJCardErrorCallback == nullptr)
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info("in matrox consumer,m_pJCardErrorCallback NULL"));
				}
				oHr = m_pJErrorNotification->RegisterCallbackForNotification(m_pJCardErrorCallback);
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox consumer, m_pJErrorNotification->RegisterCallbackForNotification"));
				}


				// 6. register for system topology asynch error call back

				m_pJSystemTopologyErrorCallback = new CErrorNotificationCallback(m_Out_Resolution);
				if (m_pJSystemTopologyErrorCallback == nullptr)
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info("in matrox consumer, new m_pJSystemTopologyErrorCallback"));
				}
				oHr = m_pJSystemTopology->RegisterCallbackForErrorNotification(m_pJSystemTopologyErrorCallback);
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox consumer, topology RegisterCallback"));
				}

				//这个暂时先不弄
				// 7. create events used
				/*	if (!m_hClockEvent)
				{
				m_hClockEvent = ::CreateEvent(NULL, false, false, NULL);

				}*/
				m_isRunning = true;
				thread_ = boost::thread([this] {playback();});
			}
			~impl(){
				m_isRunning = false;
				CMvHResult oHr = _CleanUp();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(std::wstring(L"release matrox_interface error:") + mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, _CleanUp"));
				}
			}
			//---------------------------------------------------------------------------------
			//   system init

			CMvHResult _SysConfiguration()
			{
				//获取设定分辨率
				_GetResolution(&m_Out_Resolution);
				if (m_Out_Resolution.ulWidth>=3840)
				{
					m_Sdi = 4;
				}
				CMvHResult oHr;
				//获取matrox系统配置
				oHr = CoCreateInstance(CLSID_MvSystemConfiguration,
					NULL,
					CLSCTX_INPROC_SERVER,
					IID_IMvSystemConfiguration,
					(void**)&m_IMvSystemConfiguration_);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, CoCreateInstance";
					return oHr;
				}

				if (m_IMvSystemConfiguration_ == NULL)
				{
					CASPAR_LOG(error) << L"in matrox consumer,m_IMvSystemConfiguration_ NULL";
					return oHr;
				}
		
				//板卡
				oHr = _EnumerateCards();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}

				if (m_Out_Resolution.ulWidth>= 3840)
				{
					if (m_CardConfigs[m_Card].OutputConnectors.size()<4)
					{
						CASPAR_LOG(error) << L"in matrox consumer, input connectors  less than 4";
						return MV_E_INVALID_PARAMETER;
					}
				}
				else
				{
					if (m_CardConfigs[m_Card].OutputConnectors.size() == 0 ||
						m_CardConfigs[m_Card].OutputConnectors.size() < (m_Sdi + 1))
					{
						CASPAR_LOG(error) << L"in matrox consumer, input connectors empty or less than connector index";
						return MV_E_INVALID_PARAMETER;
					}
				}
				
				return MV_NOERROR;
			}

			void _GetResolution(SMvResolutionInfo *out_pResInfo)
			{
				out_pResInfo->size = sizeof(*out_pResInfo);
				std::string szResolution;
				switch (m_format_)
				{
				case caspar::core::video_format::pal:
					szResolution = "PAL";
					break;
				case caspar::core::video_format::ntsc:
					szResolution = "NTSC";
					break;
				case caspar::core::video_format::x1080i5000:
					szResolution = "1920x1080i@25";
					break;
				case caspar::core::video_format::x1080p2500:
					szResolution = "1920x1080p@25";
					break;
				case caspar::core::video_format::x2160p2500:
					szResolution = "3840x2160p@25";//单路不支持
					break;
				case caspar::core::video_format::x576p2500:
					szResolution = "720x576p@25";//不支持
					break;
				case caspar::core::video_format::x720p2500:
					szResolution = "1280x720p@25";
					break;
				default:
					break;
				}
				if (m_format_ != core::video_format::invalid)
				{
					if (m_format_ == core::video_format::ntsc)
					{
						out_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
						out_pResInfo->eFrameRate = keMvFrameRate30M;
						//out_pResInfo->eFrameRate = keMvFrameRate25;
						out_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
						out_pResInfo->ulComponentBitCount = 8;
						out_pResInfo->ulWidth = 720;
						out_pResInfo->ulHeight = 486;
						return;
					}
					else if (m_format_ == core::video_format::pal)
					{
						out_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
						out_pResInfo->eFrameRate = keMvFrameRate25;
						out_pResInfo->eScanMode = keMvScanModeFirstFieldTop;
						out_pResInfo->ulComponentBitCount = 8;
						out_pResInfo->ulWidth = 720;
						out_pResInfo->ulHeight = 576;
						return;
					}
					else
					{
						size_t posX = szResolution.find("x");
						size_t posAt = szResolution.find("@");
						if (posX == std::string::npos)
						{
							posX = szResolution.find("X");
						}

						if (posX != std::string::npos && posAt != std::string::npos)
						{
							bool bSucceeded = true;
							std::string szSubStr = szResolution.substr(0, posX + 1); // Width
							out_pResInfo->ulWidth = atoi(szSubStr.c_str());
							szSubStr = szResolution.substr(posX + 1, (posAt - 1) - (posX + 1)); // Height
							out_pResInfo->ulHeight = atoi(szSubStr.c_str());

							szSubStr = szResolution.substr(posAt - 1, 1); // i or p
							if (szSubStr == "i" || szSubStr == "I")
							{
								if (out_pResInfo->ulHeight == 486)
								{
									out_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
								}
								else
								{
									out_pResInfo->eScanMode = keMvScanModeFirstFieldTop;
								}
							}
							else if (szSubStr == "p" || szSubStr == "P")
							{
								out_pResInfo->eScanMode = keMvScanModeProgressive;
							}
							else
							{

								bSucceeded = false;
							}

							szSubStr = szResolution.substr(posAt + 1, std::string::npos);
							if (szSubStr == "24")
							{
								out_pResInfo->eFrameRate = keMvFrameRate24;
							}
							else if (szSubStr == "24M" || szSubStr == "23.98" || szSubStr == "24m")
							{
								out_pResInfo->eFrameRate = keMvFrameRate24M;
							}
							else if (szSubStr == "25")
							{
								out_pResInfo->eFrameRate = keMvFrameRate25;
							}
							else if (szSubStr == "30")
							{
								out_pResInfo->eFrameRate = keMvFrameRate30;
							}
							else if (szSubStr == "30M" || szSubStr == "29.97" || szSubStr == "30m")
							{
								out_pResInfo->eFrameRate = keMvFrameRate30M;
							}
							else if (szSubStr == "50")
							{
								out_pResInfo->eFrameRate = keMvFrameRate50;
							}
							else if (szSubStr == "60")
							{
								out_pResInfo->eFrameRate = keMvFrameRate60;
							}
							else if (szSubStr == "60M" || szSubStr == "59.94" || szSubStr == "60m")
							{
								out_pResInfo->eFrameRate = keMvFrameRate60M;
							}
							else
							{
								bSucceeded = false;

							}

							out_pResInfo->ulComponentBitCount = 8;
							out_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
							if (m_ratio == L"16:9")
							{
								out_pResInfo->eAspectRatio = keMvAspectRatio_16_9;
							}
							if (bSucceeded)
							{
								return;
							}
						}
					}
				}

				out_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
				out_pResInfo->eFrameRate = keMvFrameRate30M;
				out_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
				out_pResInfo->ulComponentBitCount = 8;
				out_pResInfo->ulWidth = 720;
				out_pResInfo->ulHeight = 486;
				CASPAR_LOG(error) << L"in matrox consumer, Unspecified or invalid resolution format";
			}

			CMvHResult _EnumerateCards()
			{
				CMvHResult oHr = MV_NOERROR;
				// Get the cards enumerator
				TMvSmartPtr<IMvSystemConfigurationCardEnumerator> pJEnum;
				oHr = m_IMvSystemConfiguration_->CreateCardEnumerator(&pJEnum);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, _EnumerateCards CreateCardEnumerator";
					return oHr;
				}
				if (pJEnum == nullptr)
				{
					CASPAR_LOG(error) << L"in matrox_interface, get cards pJEnum NULL";
					return MV_E_FAIL;
				}
				TMvSmartPtr<IMvCardConfiguration> pJCardConfig;

				do {
					pJCardConfig = NULL;
					oHr = pJEnum->Next(&pJCardConfig);
					if (!oHr.DidSucceed())
					{
						break;
					}

					OutSCardInfo	CardInfo;
					CardInfo.sHwInfo.size = sizeof(CardInfo.sHwInfo);
					CardInfo.sHwInfo.sConnectorsDescription.size = sizeof(CardInfo.sHwInfo.sConnectorsDescription);

					oHr = pJCardConfig->GetCardInformation(&CardInfo.sHwInfo, 0);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox consumer, GetCardInformation";
						return oHr;
					}
					//
					CardInfo.pJCardConfig = pJCardConfig;
					oHr = FillOutConnectors(CardInfo);
					if (!oHr.DidSucceed())
						return oHr;

					//光端子
					oHr = _FillSfp(CardInfo);
					if (!oHr.DidSucceed())
						return oHr;
					//通知光端子变化的函数通知注册
					_RegisterSfpCallbacks(CardInfo);
					//检测卡温度
					oHr = _ValidateAndDisplayCardTemperature(CardInfo);
					if (!oHr.DidSucceed())
						return oHr;
					//视频和声音的不用获取的 producer需要获取声音通道数和视频格式
					/*oHr = FillAudioOutConnectors(CardInfo);
					if (!oHr.DidSucceed())
						return oHr;*/

					m_CardConfigs.push_back(CardInfo);

				} while (oHr.DidSucceed());

				//判断板卡数量
				if (m_CardConfigs.size() < m_Card+1)
				{
					CASPAR_LOG(error) << L"in matrox consumer, card count less than deviceIndex";
					return MV_E_INVALID_PARAMETER;
				}
				//判断指定板卡的输出通道
				if (m_CardConfigs[m_Card].OutputConnectors.size() == 0 ||
					m_CardConfigs[m_Card].OutputConnectors.size() < (m_Sdi + 1))
				{
					CASPAR_LOG(error) << L"in matrox consumer, input connectors empty or less than connector index";
					return MV_E_INVALID_PARAMETER;
				}

				return MV_NOERROR;
			}
			CMvHResult FillOutConnectors(OutSCardInfo & io_rsCardInfo)
			{
				CMvHResult oHr = NO_ERROR;

					TMvSmartPtr<IMvSdiVideoOutputConnectorsEnumerator>	pJOutputEnum;

				oHr = io_rsCardInfo.pJCardConfig->CreateSdiVideoOutputConnectorsEnumerator(&pJOutputEnum);
					// Enumerate all connectors
				if (oHr.DidSucceed())
					{
					TMvSmartPtr<IMvSdiVideoOutputConnector> pJConnector;

					// Get first connector						
					oHr.AssignNoAssert(pJOutputEnum->Next(&pJConnector));

					while (oHr.DidSucceed())
					{
						io_rsCardInfo.OutputConnectors.push_back(pJConnector);

						// Next card
						pJConnector = NULL;
						oHr.AssignNoAssert(pJOutputEnum->Next(&pJConnector));
					}

					// Ignore the error from the NEXT of the enumerator.
					oHr = MV_NOERROR;
				}
				return oHr;
			}
			CMvHResult FillAudioOutConnectors(OutSCardInfo & io_rsCardInfo)
			{
				CMvHResult oHr = NO_ERROR;
					// We get audio from SDI Embedded audio connector 0 by default
				TMvSmartPtr<IMvSdiEmbeddedAudioOutputPairConnector> pJSdiEmbeddedAudioOutputConnector;
				TMvSmartPtr<IMvSdiEmbeddedAudioOutputPairConnectorsEnumerator> pJEnumerator;
					uint32_t ui32AudioConnectorCount = 0;

				if (io_rsCardInfo.OutputConnectors.size() < (m_Sdi + 1))
					{
						CASPAR_LOG(error) << L"in matrox consumer,vecpJInputConnectors count less than index.";
						return MV_E_INVALID_PARAMETER;
					}
				oHr = io_rsCardInfo.OutputConnectors[m_Sdi]->CreateSdiEmbeddedAudioOutputPairConnectorsEnumerator(&pJEnumerator);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox consumer, Create Audio Input Pair Connectors Enumerator";
						return oHr;
					}
				while (pJEnumerator->Next(&pJSdiEmbeddedAudioOutputConnector) == MV_NOERROR && ui32AudioConnectorCount < 8)
					{
					io_rsCardInfo.SDIEAAudioOutConnectors.push_back(pJSdiEmbeddedAudioOutputConnector);
					pJSdiEmbeddedAudioOutputConnector = NULL;
						ui32AudioConnectorCount++;
					}

					if (ui32AudioConnectorCount == 0)
					{
						CASPAR_LOG(error) << L"in matrox consumer, audio input connectors empty";
						return MV_E_NOT_FOUND;
					}
			}

			//获取光端子，跟卡有关系
			CMvHResult _FillSfp(OutSCardInfo & io_rsCardInfo)
			{
				CMvHResult oHr;

				//
				// Enumerate all Sfp
				//
				TMvSmartPtr<IMvSfpSdiEnumerator> pJSfpEnum;

				oHr = io_rsCardInfo.pJCardConfig->CreateSfpSdiEnumerator(&pJSfpEnum);

				if (oHr.DidSucceed())
				{
					TMvSmartPtr<IMvSfpSdi> pJSfp;

					// Get first Sfp
					oHr.AssignNoAssert(pJSfpEnum->Next(&pJSfp));

					while (oHr.DidSucceed())
					{
						io_rsCardInfo.vecpJSfp.push_back(pJSfp);

						// Next card
						pJSfp = NULL;
						oHr.AssignNoAssert(pJSfpEnum->Next(&pJSfp));
					}

					// Ignore the error from the NEXT of the enumerator.
					oHr = MV_NOERROR;
				}

				return oHr;
			}
			void _RegisterSfpCallbacks(OutSCardInfo & io_rsCardInfo)
			{
				std::for_each(io_rsCardInfo.vecpJSfp.begin(),
					io_rsCardInfo.vecpJSfp.end(),
					[&io_rsCardInfo](TMvSmartPtr<IMvSfpSdi> in_pJSfp)
				{
					CMvHResult oHr;
					TMvSmartPtr<CSfpSdiStatusCallback> m_pJSfpStatusCallback = new CSfpSdiStatusCallback();

					oHr = in_pJSfp->RegisterCallbackForNotification(m_pJSfpStatusCallback);

					if (oHr.DidSucceed())
					{
						io_rsCardInfo.vecpJSfpCallback.push_back(m_pJSfpStatusCallback);
					}
					else
					{
						CASPAR_LOG(warning) << L"Unable to register for SFP SDI notification:" << mvErrorToString(oHr);
					}
				});
			}

			//温度传感器信息
			CMvHResult _ValidateAndDisplayCardTemperature(OutSCardInfo & io_rsCardInfo)
			{
				CMvHResult oHr;

				// We only get the temperature sensor info once but it is a good practice
				// to register an IMvTemperatureNotificationCallback through the IMvTemperatureNotification
				// to be notified when there is an overheat or a fan malfunction.

				// X.mio2+ has three temperature sensors.
				SMvTemperatureInformation  asInfo[3] =
				{
					{ keTemperatureSensorIDInvalid, 0.0, 0.0, 0.0, keMvFanStatusNotAvailable },
					{ keTemperatureSensorIDInvalid, 0.0, 0.0, 0.0, keMvFanStatusNotAvailable },
					{ keTemperatureSensorIDInvalid, 0.0, 0.0, 0.0, keMvFanStatusNotAvailable }
				};

				io_rsCardInfo.pJCardConfig->GetTemperatureSensorInfo(asInfo, 3);

				CASPAR_LOG(info) << u16(io_rsCardInfo.sHwInfo.szVariationName);

				for (int i = 0; i < 3; ++i)
				{
					if (asInfo[i].eTemperatureID != keTemperatureSensorIDInvalid)
					{

						char asInfobuf[100] = { 0 };

						sprintf(asInfobuf, "SensorID: 0x%X, CurrentTemp: %.1f C, MaxTempThreshold: %.1f C, MaxRecordedTemp: %.1f C\n",
							asInfo[i].eTemperatureID,
							asInfo[i].dTemperature,
							asInfo[i].dTemperatureErrorThreshold,
							asInfo[i].dMaxRecordedTemperature);

						CASPAR_LOG(info) << u16(asInfobuf);

						if (asInfo[i].dTemperature >= asInfo[i].dTemperatureErrorThreshold)
						{
							CASPAR_LOG(warning) << L"OVER HEAT!";
							oHr = MV_E_FAIL;
						}

						if (asInfo[i].eFanStatus == keMvFanStatusTooSlowOrStopped)
						{
							CASPAR_LOG(warning) << L"Fan: ERROR: Too slow or stopped!";
							oHr = MV_E_FAIL;
						}
						else if (asInfo[i].eFanStatus == keMvFanStatusOk)
						{
							CASPAR_LOG(warning) << L"Fan: Ok";
						}
						// else { there is no fan so no fan message to output. }
					}
				}
				return oHr;
			}

			//-------------------------------------------------------------------------------------

			// creat topology
			CMvHResult _CreateSystemTopology()
			{
				CMvHResult oHr = MV_NOERROR;
				// 1. Destroy last topology 
				oHr = _CleanTopogy();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}
				//2. Create proper clock. In this sample, use Genlock clock 
				oHr = _SetGenlockClock();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}

				//3. Create system topology API
				oHr = _CreateTopology();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}
				//4. Build CG main topology
				oHr = _BuildMainTopology();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}
				return oHr;
			}

			CMvHResult _CleanTopogy()
			{
				CMvHResult oHr;
				//?????????????????s
				//清除卡上的元素所有的默认状态并且永久内存，这个接口如果不是清除所有的拓扑的话应该不需要调用吧
				/*oHr = m_CardConfigs[m_Card].pJCardConfig->ClearDefaultsAndPermanentMemory();

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, ClearDefaultsAndPermanentMemory";
					return oHr;
				}*/

				TMvSmartPtr<IMvTopologiesEnumerator>	pJTopologyEnumerator = NULL;
				TMvSmartPtr<IMvTopology>				pJTopology = NULL;

				std::wstring strTopologyName = L"MatroxConsumer" + boost::lexical_cast<std::wstring>(m_Sdi);

				oHr = m_CardConfigs[m_Card].pJCardConfig->CreateTopologiesEnumerator(&pJTopologyEnumerator);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, CreateTopologiesEnumerator";
					return oHr;
				}


				do
				{
					pJTopology = NULL;
					oHr = pJTopologyEnumerator->Next(&pJTopology);
					if (!oHr.DidSucceed())
					{
						break;
					}
					oHr = pJTopology->AcquireControl();
					if (!oHr.DidSucceed())
					{
						return oHr;
					}

					char szTopologyName[128];
					oHr = pJTopology->GetName(szTopologyName, 128);
					if (!oHr.DidSucceed())
					{
						return oHr;
					}

					if ((strcmp(u8(strTopologyName).c_str(), "") == 0 || strcmp(u8(strTopologyName).c_str(), szTopologyName) == 0))
					{
						oHr = pJTopology->DestroyTopology();
						if (!oHr.DidSucceed())
						{
							CASPAR_LOG(error) << L"in matrox consumer, DestroyTopology";
							return oHr;
						}
					}
				} while (oHr.DidSucceed());

				return MV_NOERROR;
			}
			CMvHResult _GetFlexEngine()
			{
				CMvHResult oHr = MV_NOERROR;
				if (!m_CardConfigs[m_Sdi].pJCardConfig)
				{
					CASPAR_LOG(error) << L"in matrox consumer, output index card Config is NULL";
					return MV_E_FAIL;
				}
				oHr = m_CardConfigs[m_Sdi].pJCardConfig->QueryInterface(IID_IMvFlexEngine, (void**)&m_pJFlexEngine);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,QueryInterface";
					return oHr;
				}
				return MV_NOERROR;
			}

			CMvHResult _CreateVideoAudioPoolManagers()
			{
				CMvHResult oHr = MV_NOERROR;
				uint32_t ui32PoolSize = 32;

				if (m_IMvSystemConfiguration_ == NULL)
				{
					CASPAR_LOG(error) << L"in matrox consumer ,_CreateVideoAudioPoolManagers,m_IMvSystemConfiguration_ NULL";
					return MV_E_FAIL;
				}

				_DefineUserBufferDescription();

				// User buffer surface pool for playback
				oHr = m_IMvSystemConfiguration_->CreateSurfaceUserBufferPool(L"m_pJVideoUserBufferSurfacePoolPlayback",
					ui32PoolSize,
					ui32PoolSize,
					m_Out_Resolution.eScanMode,
					&m_pJVideoUserBufferSurfacePoolForPlayback);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer,CreateSurfaceUserBufferPool";
					return oHr;
				}

				//队列报错信息注册
				m_pJVideoSurfaceAsynchErroCallback = new CErrorNotificationCallback(m_Out_Resolution);
				if (m_pJAudioSamplesAsynchErroCallback == nullptr)
				{
					CASPAR_LOG(error) << L"in matrox consumer,_CreateVideoAudioPoolManagers,m_IMvSystemConfiguration_ NULL";
					return MV_E_FAIL;
				}
				oHr = m_pJVideoUserBufferSurfacePoolForPlayback->AddCompletionObserver(m_pJVideoSurfaceAsynchErroCallback);

				//Create Audio samples pool
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer,AddCompletionObserver";
					return oHr;
				}
				SMvCreateAudioSamplesDescription sAudioSamplesDescription;

				_DefineAudioSamplesDescription(&sAudioSamplesDescription);

				oHr = m_IMvSystemConfiguration_->CreateAudioSamplesPool(L"m_pJAudioSamplesPoolForPlayback", ui32PoolSize, ui32PoolSize, sAudioSamplesDescription, &m_pJAudioSamplesPoolForPlayback);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, CreateAudioSamplesPool";
					return oHr;
				}

				m_pJAudioSamplesAsynchErroCallback = new CErrorNotificationCallback(m_Out_Resolution);

				oHr = m_pJAudioSamplesPoolForPlayback->AddCompletionObserver(m_pJAudioSamplesAsynchErroCallback);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, AddCompletionObserver";
					return oHr;
				}
				return MV_NOERROR;
			}

			void _DefineUserBufferDescription()
			{
				unsigned long ulUserBufferMaxSize = m_Out_Resolution.ulHeight*m_Out_Resolution.ulWidth * 2;   //YUV

				m_sUserBufferSurfaceDescription.size = sizeof(SMvUserBufferSurfaceDescription);
				m_sUserBufferSurfaceDescription.bIsVideoShaped = false;
				m_sUserBufferSurfaceDescription.bUseAlpha = false;

				if (m_Out_Resolution.ulWidth <= 720)
				{
					m_sUserBufferSurfaceDescription.eColorimetry = keMvColorimetryITUR_BT_601;
				}
				else
				{
					m_sUserBufferSurfaceDescription.eColorimetry = keMvColorimetryITUR_BT_709;
				}

				m_sUserBufferSurfaceDescription.eFormat = keMvSurfaceFormatYUYV422;
				m_sUserBufferSurfaceDescription.eImageOrigin = keMvImageOriginTopLeft;
				m_sUserBufferSurfaceDescription.ePolarity = m_Out_Resolution.eScanMode == keMvScanModeProgressive ? keMvPolarityProgressiveFrame : keMvPolarityFirstField;
				m_sUserBufferSurfaceDescription.eType = keMvSurfaceType2D;
				m_sUserBufferSurfaceDescription.ptDestinationPosition.fX = 0.0;
				m_sUserBufferSurfaceDescription.ptDestinationPosition.fY = 0.0;
				m_sUserBufferSurfaceDescription.ulBufferSizeInBytes = ulUserBufferMaxSize;

				m_sUserBufferSurfaceDescription.sTemporalCompressionInfo.size = sizeof(SMvTemporalCompressionInfo);
				m_sUserBufferSurfaceDescription.sTemporalCompressionInfo.bDependedOn = false;
				m_sUserBufferSurfaceDescription.sTemporalCompressionInfo.bDependedOnValid = false;
				m_sUserBufferSurfaceDescription.sTemporalCompressionInfo.bDependsOn = false;
				m_sUserBufferSurfaceDescription.sTemporalCompressionInfo.bDependsOnValid = false;
				m_sUserBufferSurfaceDescription.sTemporalCompressionInfo.bRandomAccess = false;
				m_sUserBufferSurfaceDescription.ulComponentBitCount = 8;
				m_sUserBufferSurfaceDescription.ulDepth = 1;
				m_sUserBufferSurfaceDescription.ulHeight = m_Out_Resolution.ulHeight;
				m_sUserBufferSurfaceDescription.ulWidth = m_Out_Resolution.ulWidth;
				m_sUserBufferSurfaceDescription.ulRowPitchInBytes = m_sUserBufferSurfaceDescription.ulWidth * 2;
				m_sUserBufferSurfaceDescription.ulSlicePitchInBytes = ulUserBufferMaxSize;

			}

			void _DefineAudioSamplesDescription(SMvCreateAudioSamplesDescription * io_psAudioSamplesDescription)
			{
				io_psAudioSamplesDescription->size = sizeof(SMvCreateAudioSamplesDescription);

				io_psAudioSamplesDescription->bHasFadeIn = false;
				io_psAudioSamplesDescription->bHasFadeOut = false;
				io_psAudioSamplesDescription->eMemoryLocation = keMvMemoryLocationHost;
				io_psAudioSamplesDescription->ePolarity = m_Out_Resolution.eScanMode == EMvScanMode::keMvScanModeFirstFieldTop ? keMvPolarityFirstField : keMvPolarityProgressiveFrame;
				EMvChannelType audiotype = keChannelTypeStereo;
				switch (m_preset_Channels)
				{
				case 1:
					audiotype = keChannelTypeMono;

					break;
				case 2:
					audiotype = keChannelTypeStereo;
					break;
				case 8:
					audiotype = keChannelType8Tracks;
					break;
				case 16:
					audiotype = keChannelType16Tracks;
					break;
				default:
					break;
				}


				io_psAudioSamplesDescription->ulMaxBufferSize = 2002 * audiotype * (keAudioBitsPerSample32 >> 3);
				io_psAudioSamplesDescription->sWaveFormat.size = sizeof(SMvaWaveFormatInfo);
				io_psAudioSamplesDescription->sWaveFormat.eChannelType = audiotype;
				io_psAudioSamplesDescription->sWaveFormat.eDataType = keAudioDataTypePCM;
				io_psAudioSamplesDescription->sWaveFormat.ulBitsPerSample = 32;
				io_psAudioSamplesDescription->sWaveFormat.ulValidBitsPerSample = 24;
				io_psAudioSamplesDescription->sWaveFormat.ulSamplesPerSec = 48000;
			}

			CMvHResult _SetGenlockClock()
			{
				CMvHResult oHr = MV_NOERROR;

				// Get the clock enumerator interface.
				TMvSmartPtr<IMvSystemClockEnumerator>	pJClockEnum;
				TMvSmartPtr<IMvSystemClock>				pJClock;

				oHr = m_CardConfigs[m_Sdi].pJCardConfig->CreateSystemClockEnumerator(&pJClockEnum);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, CreateSystemClockEnumerator";
					return oHr;
				}
				bool findout = false;
				// Enumerate all clocks in the system.
				while (pJClockEnum->Next(&pJClock) == MV_NOERROR)
				{
					// Search for a genlock clock
					if (pJClock->GetClockType() == keMvSystemClockTypeGenlock)
					{
						TMvSmartQPtr<IMvSystemClockGenlock, &IID_IMvSystemClockGenlock> pQGenlock(pJClock, &oHr);

						if (oHr.DidSucceed())
						{
							TMvSmartPtr<IMvCardConfiguration> pJTempCard;
							oHr = pQGenlock->GetCardConfig(&pJTempCard);

							if (m_CardConfigs[m_Sdi].pJCardConfig == pJTempCard)
							{
								m_pJClock = pJClock;		// This is the genlock clock corresponding to the used card.
								findout = true;
								break;
							}
						}
					}

					pJClock = NULL;  // Next clock
				}
				if (!findout)
				{
					CASPAR_LOG(error) << L"in matrox consumer ,clock enum not find genlock";
					return MV_E_FAIL;
				}
				return MV_NOERROR;
			}
			CMvHResult _CreateTopology()
			{
				CMvHResult oHr = MV_NOERROR;

				// Set genlock resolution
				oHr = _SetupGenlockResolution();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}

				std::wstring strTopologyName = L"MatroxConsumer" + boost::lexical_cast<std::wstring>(m_Sdi);
				oHr = m_IMvSystemConfiguration_->CreateSystemTopology(u8(strTopologyName).c_str(), m_pJClock, &m_pJSystemTopology);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, CreateSystemTopology";
					return oHr;
				}
				
				oHr = m_pJSystemTopology->RegisterCallbackForErrorNotification(m_pJErrorCallback);
			
				return oHr;
			}

			CMvHResult _BuildMainTopology()
			{
				CMvHResult oHr = MV_NOERROR;
				// Output stream
				int Count_connecters = 1;
				SMvOutputStreamSettings sOutputStreamSettings;

				//IMvVideoOutputConnector * apIVideoOutputConnetor[2];
				//apIVideoOutputConnetor[0] = m_sCardInfo.vecpJOutputConnectors[0];

				IMvConnector*   apIOutputConnetor[4];
				apIOutputConnetor[0] = m_CardConfigs[m_Card].OutputConnectors[0];
				if (m_Out_Resolution.ulWidth>=3840)
				{
					apIOutputConnetor[1] = m_CardConfigs[m_Card].OutputConnectors[1];
					apIOutputConnetor[2] = m_CardConfigs[m_Card].OutputConnectors[2];
					apIOutputConnetor[3] = m_CardConfigs[m_Card].OutputConnectors[3];
					Count_connecters = 4;
				}
				
				SMvNodeSettings      sOutputNodeSettings;
				SMvNodeSettingsVideo sOutputVideoSettings;
				SMvNodeSettingsAudio sOutputAudioSettings;
				SMvNodeSettingsVanc sOutputVancSettings;


				_SetOutputNodeDefaultSettings(sOutputNodeSettings, sOutputVideoSettings, sOutputAudioSettings, sOutputVancSettings);
				switch (m_preset_Channels)
				{
				case 1:
					sOutputAudioSettings.eChannelType = keChannelTypeMono;
					break;
				case 2:
					sOutputAudioSettings.eChannelType = keChannelTypeStereo;
					break;
				case 8:
					sOutputAudioSettings.eChannelType = keChannelType8Tracks;
					break;
				case 16:
					sOutputAudioSettings.eChannelType = keChannelType16Tracks;
					break;
				default:
					break;
				}
				std::wstring sname = L"OutputHostNode" + boost::lexical_cast<std::wstring>((m_Sdi));
				sprintf_s(sOutputNodeSettings.szName, _countof(sOutputNodeSettings.szName), u8(sname).c_str());

				// Create host node.
				oHr = m_pJSystemTopology->CreateHostNode(sOutputNodeSettings, &sOutputVideoSettings, &sOutputAudioSettings, &sOutputVancSettings, &m_pJIOHostNodeForPlayback);
				if (oHr.DidFail())
				{
					return oHr;
				}
				sname = L"OutputcardNode" + boost::lexical_cast<std::wstring>((m_Sdi));
				sprintf_s(sOutputNodeSettings.szName, _countof(sOutputNodeSettings.szName), u8(sname).c_str());
				oHr = m_pJSystemTopology->CreateCardNode(sOutputNodeSettings,
					&sOutputVideoSettings,
					&sOutputAudioSettings,
					&sOutputVancSettings,
					m_CardConfigs[m_Card].pJCardConfig,
					&m_pJIOCardNodeForPlayback);

				// By default, playback video on SDI output A
				_SetOutputStreamDefaultSettings(sOutputStreamSettings);


				TMvSmartPtr<IMvOutputStream>		m_pJOutputStream;

				oHr = m_pJSystemTopology->CreateOutputStreamSdi("MainOutput",
					m_pJIOCardNodeForPlayback,
					m_Out_Resolution,
					sOutputStreamSettings,
					apIOutputConnetor,
					NULL,
					Count_connecters,
					&m_pJOutputStream);


				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, CreateOutputStreamSdi";
					return oHr;
				}
				EMvAudioPair aeAudioPair[8] = { keAudioPair0, keAudioPair1, keAudioPair2, keAudioPair3,
					keAudioPair4, keAudioPair5, keAudioPair6, keAudioPair7 };

				// Fills in completely the SDI audio pairs
				oHr = m_CardConfigs[m_Card].OutputConnectors[0]->SetSourceOutputStreamAndAudioPairs(m_pJOutputStream, aeAudioPair, 1);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, SetSourceOutputStreamAndAudioPairs";
					return oHr;
				}


				if (m_IsVanc)
				{
					// Get vanc data packets interface from host node.
					oHr = m_pJIOHostNodeForPlayback->QueryInterface(IID_IMvVancDataPackets, (void**)&m_pJVancDataPackets);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox consumer, host node vanc QueryInterface";
						return oHr;
					}
					if (m_pJVancDataPackets == nullptr)
					{
						m_IsVanc = false;
						CASPAR_LOG(error) << L"in matrox consumer, m_pJVancDataPackets NULL";
						return MV_NOERROR;
					}
					oHr = m_pJVancDataPackets->EnableVancDataPackets();
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"m_pJHostNode enable vanc data packet failed";
					}
				}
				return oHr;

				return MV_NOERROR;
			}

			CMvHResult _SetupGenlockResolution()
			{
				CMvHResult oHr = MV_NOERROR;

				// Get genlock interface.         
				TMvSmartPtr<IMvGenlockConfiguration>	pJGenlockConfig;

				oHr = m_CardConfigs[m_Sdi].pJCardConfig->GetGenlockConfiguration(&pJGenlockConfig);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, GetGenlockConfiguration";
					return oHr;
				}

				// Get current genlock settings

				SMvGenlockSettings sCurrentGenlockSettings = { sizeof(sCurrentGenlockSettings) };
				oHr = pJGenlockConfig->GetGenlockSettings(sCurrentGenlockSettings);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, bGetGenlockSettings";
					return oHr;
				}
				// Set genlock source to external BB

				SMvGenlockSettings sNewGenlockSettings;
				sNewGenlockSettings = sCurrentGenlockSettings;
				//keGenlockSourceBlackBurst
				sNewGenlockSettings.eGenlockSource = keGenlockSourceInternal;
				sNewGenlockSettings.sResolution.eAspectRatio = m_Out_Resolution.eAspectRatio;
				sNewGenlockSettings.sResolution.ulComponentBitCount = 8;
				sNewGenlockSettings.sResolution.eFrameRate = m_Out_Resolution.eFrameRate;
				sNewGenlockSettings.bEnableTermination = true;
				sNewGenlockSettings.sResolution.ulWidth = m_Out_Resolution.ulWidth;
				sNewGenlockSettings.sResolution.ulHeight = m_Out_Resolution.ulHeight;
				sNewGenlockSettings.sResolution.eScanMode = m_Out_Resolution.eScanMode;
				oHr = pJGenlockConfig->SetGenlockSettings(sNewGenlockSettings);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, SetGenlockSettings";
					return oHr;
				}
				return MV_NOERROR;
			}
			void _SetInputStreamDefaultSettings(SMvInputStreamSettings & out_sInputStreamSettings)
			{
				EMvInputStreamMode        eTBCMode;

				eTBCMode = keMvInputStreamModeAudioVideoTBC;

				SMvInputStreamSettings sSettings =
				{
					sizeof(sSettings), // uint32_t ui32Size;
					{	// SMvVideoInputStreamSettings sVideoInputStreamSettings;
						1.0,	// double dBrightness;
						1.0,	// double dLumaGain;
						1.0,	// double dHue;
						1.0,	// double dSaturation;
						false,	// bool bAllowSuperBlack;
						false,	// bool bAllowSuperWhite;
						false,	// bool bEnableChromaClipping;
						false,	// bool bUpscaleKeyLuma;
						false,	// bool bInvertKeyLuma;
						false,	// bool bApplyKeyLumaOffset;
					},

					eTBCMode,

					{
						false,  //only have the first pair non-muted
						true,
						true,
						true,
						true,
						true,
						true,
						true,
					},
				};

				sSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
				sSettings.aeVideoConnectorPosition[1] = keMvQuadrantTopRight;
				sSettings.aeVideoConnectorPosition[2] = keMvQuadrantBottomLeft;
				sSettings.aeVideoConnectorPosition[3] = keMvQuadrantBottomRight;

				out_sInputStreamSettings = sSettings;
			}
			void _SetInputNodeDefaultSettings(SMvNodeSettings      &out_sNodeSettings,
				SMvNodeSettingsVideo &out_sNodeSettingsVideo,
				SMvNodeSettingsAudio &out_sNodeSettingsAudio,
				SMvNodeSettingsVanc	 &out_sNodeSettingsVanc)
			{
				// Create a node to attach to the output streams
				if (m_Out_Resolution.eScanMode == keMvScanModeProgressive || m_Out_Resolution.eScanMode == keMvScanModeProgressiveSegmented)
				{
					out_sNodeSettings.ui64WriteToReadDelayInNanoTime = MvGetNanoTimeForSample(m_ui32WriteToReadDelayInFrame * 1, m_Out_Resolution);
				}
				else
				{
					out_sNodeSettings.ui64WriteToReadDelayInNanoTime = MvGetNanoTimeForSample(m_ui32WriteToReadDelayInFrame * 2, m_Out_Resolution);
				}

				out_sNodeSettings.ui32Size = sizeof(SMvNodeSettings);
				out_sNodeSettings.ui32Depth = m_ui32DepthInFrame;
				out_sNodeSettings.eNodeContent = keMvNodeContentVideoAudio;

				out_sNodeSettingsVideo.ui32Size = sizeof(SMvNodeSettingsVideo);
				out_sNodeSettingsVideo.sResInfo = m_Out_Resolution;

				if (m_Out_Resolution.ulWidth <= 720)
				{
					out_sNodeSettingsVideo.eColorimetry = keMvColorimetryITUR_BT_601;
				}
				else
				{
					out_sNodeSettingsVideo.eColorimetry = keMvColorimetryITUR_BT_709;
				}

				out_sNodeSettingsVideo.eSurfaceFormat = keMvSurfaceFormatYUYV422;

				out_sNodeSettingsAudio.ui32Size = sizeof(SMvNodeSettingsAudio);
				out_sNodeSettingsAudio.eChannelType = keChannelTypeStereo;
				out_sNodeSettingsAudio.eDataType = keAudioDataTypePCM;
				out_sNodeSettingsAudio.ui32BitsPerSample = 32;
				out_sNodeSettingsAudio.ui32ValidBitsPerSample = 24;

				out_sNodeSettingsVanc.eVancFormat = keMvSurfaceFormatMatroxAncillaryData;
				out_sNodeSettingsVanc.ui32ComponentBitCount = 16;

			}

			void _SetOutputNodeDefaultSettings(SMvNodeSettings      &out_sNodeSettings,
				SMvNodeSettingsVideo &out_sNodeSettingsVideo,
				SMvNodeSettingsAudio &out_sNodeSettingsAudio,
				SMvNodeSettingsVanc	&out_sNodeSettingsVanc)
			{
				if (m_Out_Resolution.eScanMode == keMvScanModeProgressive || m_Out_Resolution.eScanMode == keMvScanModeProgressiveSegmented)
				{
					out_sNodeSettings.ui64WriteToReadDelayInNanoTime = MvGetNanoTimeForSample(m_ui32WriteToReadDelayInFrameOutputNode * 1, m_Out_Resolution);
				}
				else
				{
					out_sNodeSettings.ui64WriteToReadDelayInNanoTime = MvGetNanoTimeForSample(m_ui32WriteToReadDelayInFrameOutputNode * 2, m_Out_Resolution);
				}

				// Create a node to attach to the output streams
				out_sNodeSettings.ui32Size = sizeof(SMvNodeSettings);
				out_sNodeSettings.ui32Depth = m_ui32DepthInFrame;
				out_sNodeSettings.eNodeContent = keMvNodeContentVideoAudio;

				out_sNodeSettingsVideo.ui32Size = sizeof(SMvNodeSettingsVideo);
				out_sNodeSettingsVideo.sResInfo = m_Out_Resolution;
	            if (m_Out_Resolution.ulWidth <= 720)
				{
					out_sNodeSettingsVideo.eColorimetry = keMvColorimetryITUR_BT_601;
				}
				else
				{
					out_sNodeSettingsVideo.eColorimetry = keMvColorimetryITUR_BT_709;
				}
				out_sNodeSettingsVideo.eSurfaceFormat = keMvSurfaceFormatARGBGraphic;

				out_sNodeSettingsAudio.ui32Size = sizeof(SMvNodeSettingsAudio);
				out_sNodeSettingsAudio.eChannelType = keChannelTypeStereo;
				out_sNodeSettingsAudio.eDataType = keAudioDataTypePCM;
				out_sNodeSettingsAudio.ui32BitsPerSample = 32;
				out_sNodeSettingsAudio.ui32ValidBitsPerSample = 24;

				out_sNodeSettingsVanc.eVancFormat = keMvSurfaceFormatMatroxAncillaryData;
				out_sNodeSettingsVanc.ui32ComponentBitCount = 16;
			}

			virtual void __stdcall NotifyClock()
			{
				//同步时钟设置回调不知道有没有用暂时不实现

			}

			void _SetOutputStreamDefaultSettings(SMvOutputStreamSettings & out_sOutputStreamSettings)
			{
				SMvOutputStreamSettings sOutputStreamSettings =
				{
					sizeof(sOutputStreamSettings), // uint32_t ui32Size;
												   // SMvAudioOutputStreamSettings sAudioOutputStreamSettings;
					{
						false, // bool bEnableAudioMixer;
						false, // bool bAudioPhaseInvert;
						{ 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0 }, // double adAudioInputStreamVolume[16];
						{ 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0 }, // double adAudioOutputStreamVolume[16];
						1.0, // Audio inline mixer line master volume;
						1.0, // Audio inline mixer Aux. master volume;
						keMvAudioMixerSourceNode //Audio inline mixer Aux. source selected;
					},
					// SMvVideoOutputStreamSettings sVideoOutputStreamSettings;
					{
						true,  // bool bAllowSuperBlack;
						true,  // bool bAllowSuperWhite;
						false, // bool bEnableChromaClipping;
						false, // bool bDownscaleKeyLuma;
						false, // bool bInvertKeyLuma;
						false, // bool bApplyKeyLumaOffset;
						false, // bool bEnableEdgeSharpeningFilter;
					}
				};

				sOutputStreamSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
				sOutputStreamSettings.aeVideoConnectorPosition[1] = keMvQuadrantTopRight;
				sOutputStreamSettings.aeVideoConnectorPosition[2] = keMvQuadrantBottomLeft;
				sOutputStreamSettings.aeVideoConnectorPosition[3] = keMvQuadrantBottomRight;

				out_sOutputStreamSettings = sOutputStreamSettings;
			}
			CMvHResult _WaitForWriteCompletion(TMvSmartPtr<IMvSurface> out_pJVideoSurface)
			{
				CMvHResult hr;
				CMvHResult hr_Error;
				//DWORD dwResult = NMvs::WaitForWriteCompletion(out_pJVideoSurface, 5000);
				HANDLE   hEvent;
				DWORD dwResult;
				if (out_pJVideoSurface)
				{
					out_pJVideoSurface->GetWriteCompletionEvent(&hEvent);
					dwResult = m_pJFlexEngine->WaitForSingleObject(hEvent, 5000);
					//dwResult=WaitForSingleObject(hEvent, 5000);
				}
				if (dwResult == WAIT_TIMEOUT)
				{
					CASPAR_LOG(warning) << L"in matrox consumer, NMvs::WaitForWriteCompletion time out";
					return MV_NOERROR;
				}

				hr = out_pJVideoSurface->GetLastError(&hr_Error);
				if (!hr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, GetLastError";
					return hr;
				}
				if (!hr_Error.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox consumer, GetLastError";
					return hr_Error;
				}
				return MV_NOERROR;
			}

			
			CMvHResult QueueFieldOrFrame(void * pvideo, void * paudio, void*pvideo1, void *paudio1,
				SMvVancPacket* in_paVancPackets, uint32_t in_ui32PacketCount)
			{
				CMvHResult oHr;
				//寄场
				transferconfig sOutputBuffers;
				sOutputBuffers.pVideoBuffer = (uint8_t*)pvideo;
				sOutputBuffers.pAudioBuffer = (uint8_t*)paudio;
				sOutputBuffers.secondfiel = false;
				sOutputBuffers.RowPitchInbytes = m_Out_Resolution.ulWidth * 2;
				if (!_IsFieldBased(m_Out_Resolution))
				{
					in_paVancPackets[0].ui32LineNumber = 9;
					sOutputBuffers.in_paVancPackets = in_paVancPackets[0];
					sOutputBuffers.in_ui32PacketCount = in_ui32PacketCount;
					BuffersQueue.push(sOutputBuffers);

					return oHr;
				}
				//in_paVancPackets[0].ui32LineNumber = 13;
				sOutputBuffers.in_paVancPackets = in_paVancPackets[0];
				sOutputBuffers.in_ui32PacketCount = in_ui32PacketCount;


				BuffersQueue.push(sOutputBuffers);
				//偶场
				sOutputBuffers.secondfiel = true;
				//in_paVancPackets[0].ui32LineNumber = 9;
				sOutputBuffers.pVideoBuffer = (uint8_t*)pvideo1;
				sOutputBuffers.pAudioBuffer = (uint8_t*)paudio1;
				sOutputBuffers.in_paVancPackets = in_paVancPackets[0];
				sOutputBuffers.in_ui32PacketCount = in_ui32PacketCount;


				BuffersQueue.push(sOutputBuffers);

				return oHr;
			}
			uint64_t _GetNextClockTimeForPlayback()
			{
				uint64_t    ui64NanoTime, ui64SampleTime;

				// Get the current time 
				ui64NanoTime = m_pJClock->GetTime();
				ui64NanoTime = MvGetNextSampleNanoTime(ui64NanoTime, m_Out_Resolution);

				ui64SampleTime = MvGetSampleForNanoTime(ui64NanoTime, m_Out_Resolution);

				if (ui64SampleTime <= m_ui64LastPlaybackSampleTime)
				{
					ui64SampleTime = m_ui64LastPlaybackSampleTime + 1;
				}

				m_ui64LastPlaybackSampleTime = ui64SampleTime;

				// Return nanotime
				return MvGetNanoTimeForSample(ui64SampleTime, m_Out_Resolution);
			}
			CMvHResult _RenderingVideoSurface(TMvSmartPtr<IMvSurface> in_pJVideoSurface, TMvSmartPtr<IMvSurface> &io_pJRenderredVideoSurface)
			{
				CMvHResult  oHr = MV_NOERROR;
				uint64_t ui64RenderingNanoTime;

				oHr = in_pJVideoSurface->GetTimeStampInfo(&ui64RenderingNanoTime);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, GetTimeStampInfo";
					return oHr;
				}

				// OEM may perform rendering on incoming video, here we simply copy video/audio
				//Rendering video
				oHr = m_pJVideoUserBufferSurfacePoolForPlayback->WaitForSurface(1000, &io_pJRenderredVideoSurface);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, WaitForSurface";
					return oHr;
				}

				uint8_t *											m_pUserBufferForRawDataPlayback;
				//将视频指针申请空间
				if (m_Out_Resolution.eScanMode == keMvScanModeFirstFieldTop)
				{
					//半场数据高度是一半
					m_pUserBufferForRawDataPlayback = (uint8_t *)malloc(m_Out_Resolution.ulWidth * 2 * m_Out_Resolution.ulHeight / 2);
				}
				else
				{
					//逐行
					m_pUserBufferForRawDataPlayback = (uint8_t *)malloc(m_Out_Resolution.ulWidth * 2 * m_Out_Resolution.ulHeight);
				}

				m_sUserBufferSurfaceDescription.pBuffer = m_pUserBufferForRawDataPlayback;    //Be careful, overwritten here, apply multiple allocated memory

																							  // pointing to user buffer
				oHr = io_pJRenderredVideoSurface->AssignUserBufferReference(&m_sUserBufferSurfaceDescription);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, AssignUserBufferReference";
					return oHr;
				}
				// synchronize surface

				//NMvs::PrepareSynchronization(io_pJRenderredVideoSurface, ui64RenderingNanoTime);
				oHr = io_pJRenderredVideoSurface->SetTimeStampInfo(&ui64RenderingNanoTime);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, io_pJRenderredVideoSurface->setTimeStampInfo";
					return oHr;
				}
				oHr = io_pJRenderredVideoSurface->IncrementReadCount();                        // 增加读基数1
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, io_pJRenderredVideoSurface->IncrementReadCount";
					return oHr;
				}

				oHr = io_pJRenderredVideoSurface->IncrementWriteCount();                        // 增加写基数1
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, io_pJRenderredVideoSurface->IncrementWriteCount";
					return oHr;
				}

				oHr = m_pJFlexEngine->CopySurface(in_pJVideoSurface, NULL, io_pJRenderredVideoSurface, NULL, keMvFilterModeNormal, 0);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, CopySurface";
					return oHr;
				}


				return MV_NOERROR;
			}
			CMvHResult _RenderingAudioSamples(TMvSmartPtr<IMvAudioSamples> in_pJAudioSamples, TMvSmartPtr<IMvAudioSamples> &io_pJRenderredAudioSamples)
			{
				CMvHResult        oHr = MV_NOERROR;
				uint64_t       ui64RenderingNanoTime;
				uint64_t       ui64AudioSampleTime;
				unsigned long  ulAudioSampleCount;
				unsigned long  ulAudioSampleValidBufferLength;

				oHr = m_pJAudioSamplesPoolForPlayback->WaitForAudioSamples(1000, &io_pJRenderredAudioSamples);

				// Set Audio sample buffer size
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, WaitForAudioSamples";
					return oHr;
				}

				oHr = io_pJRenderredAudioSamples->GetTimeStampInfo(&ui64RenderingNanoTime);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, WaitForAudioSamples";
					return oHr;
				}

				ui64AudioSampleTime = MvGetSampleForNanoTime(ui64RenderingNanoTime, m_Out_Resolution);
				ulAudioSampleCount = (unsigned long)MvGetAudioSamplesFromReferencedVideoUnits(1, ui64AudioSampleTime, m_Out_Resolution);

				//ulAudioSampleValidBufferLength = ulAudioSampleCount* m_eAudioChannelType * (keAudioBitsPerSample32 >> 3);

				switch (m_preset_Channels)
				{
				case 1:
					ulAudioSampleValidBufferLength = ulAudioSampleCount* keChannelTypeMono * (keAudioBitsPerSample32 >> 3);
					break;
				case 2:
					ulAudioSampleValidBufferLength = ulAudioSampleCount* keChannelTypeStereo * (keAudioBitsPerSample32 >> 3);
					break;
				case 8:
					ulAudioSampleValidBufferLength = ulAudioSampleCount* keChannelType8Tracks * (keAudioBitsPerSample32 >> 3);
					break;
				case 16:
					ulAudioSampleValidBufferLength = ulAudioSampleCount* keChannelType16Tracks * (keAudioBitsPerSample32 >> 3);
					break;
				default:
					ulAudioSampleValidBufferLength = ulAudioSampleCount* keChannelTypeStereo * (keAudioBitsPerSample32 >> 3);
					break;
				}


				oHr = io_pJRenderredAudioSamples->SetLength(ulAudioSampleValidBufferLength);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, SetLength";
					return oHr;
				}
				//Prepare synchronization on audio samples
				//NMvs::PrepareSynchronization(io_pJRenderredAudioSamples, ui64RenderingNanoTime);
				oHr = io_pJRenderredAudioSamples->SetTimeStampInfo(&ui64RenderingNanoTime);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, io_pJRenderredAudioSamples->setTimeStampInfo";
					return oHr;
				}
				oHr = io_pJRenderredAudioSamples->IncrementReadCount();                        // 增加读基数1
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, io_pJRenderredAudioSamples->IncrementReadCount";
					return oHr;
				}

				oHr = io_pJRenderredAudioSamples->IncrementWriteCount();                        // 增加写基数1
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, io_pJRenderredAudioSamples->IncrementWriteCount";
					return oHr;
				}


				oHr = m_pJFlexEngine->CopyAudioSamples(in_pJAudioSamples, io_pJRenderredAudioSamples, 0);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox consumer, CopyAudioSamples";
					return oHr;
				}
				return MV_NOERROR;
			}
			void playback()
			{
				TMvSmartPtr<IMvSurface>       pJRenderredVideoSurface;
				TMvSmartPtr<IMvAudioSamples>  pJRenderredAudioSamples;
				CMvHResult oHr = MV_NOERROR;
				transferconfig lp;
				while (m_isRunning)
				{

					pJRenderredVideoSurface = NULL;
					pJRenderredAudioSamples = NULL;

					//拿到fms的frame，转换这部分先不做
					BuffersQueue.pop(lp);
					//大概是这样做
					SMvUserBufferSurfaceDescription MvsVideoBuf;
					MvsVideoBuf.pBuffer = lp.pVideoBuffer;
					pJRenderredVideoSurface->AssignUserBufferReference(&MvsVideoBuf);


					SMvUserBufferAudioSamplesDescription MvsAudioBuf;
					MvsAudioBuf.pBuffer = lp.pAudioBuffer;
					pJRenderredAudioSamples->AssignUserBufferReference(&MvsAudioBuf);

					//

					TMvSmartPtr<IMvSurface> out_pJVideoSurface;
					TMvSmartPtr<IMvAudioSamples> out_pJAudioSurface;

					oHr = _WaitForWriteCompletion(out_pJVideoSurface);

					if (!oHr.DidSucceed())
					{
						CASPAR_THROW_EXCEPTION(caspar_exception()
							<< msg_info(mvErrorToString(oHr))
							<< boost::errinfo_api_function("in matrox consumer, _WaitForWriteCompletion"));
					}
					oHr = _RenderingVideoSurface(out_pJVideoSurface, pJRenderredVideoSurface);
					if (!oHr.DidSucceed())
					{
						CASPAR_THROW_EXCEPTION(caspar_exception()
							<< msg_info(mvErrorToString(oHr))
							<< boost::errinfo_api_function("in matrox consumer, _RenderingVideoSurface"));
					}

					oHr = _RenderingAudioSamples(out_pJAudioSurface, pJRenderredAudioSamples);
					if (!oHr.DidSucceed())
					{
						CASPAR_THROW_EXCEPTION(caspar_exception()
							<< msg_info(mvErrorToString(oHr))
							<< boost::errinfo_api_function("in matrox consumer, _RenderingAudioSamples"));
					}

					//上面可能不需要
					uint64_t ui64PlaybackNanoTime;
					ui64PlaybackNanoTime = _GetNextClockTimeForPlayback();

					oHr = pJRenderredAudioSamples->SetTimeStampInfo(&ui64PlaybackNanoTime);
					if (!oHr.DidSucceed())
					{
						CASPAR_THROW_EXCEPTION(caspar_exception()
							<< msg_info(mvErrorToString(oHr))
							<< boost::errinfo_api_function("in matrox consumer, audio samples SetTimeStampInfo"));
					}

					oHr = pJRenderredVideoSurface->SetTimeStampInfo(&ui64PlaybackNanoTime);
					if (!oHr.DidSucceed())
					{
						CASPAR_THROW_EXCEPTION(caspar_exception()
							<< msg_info(mvErrorToString(oHr))
							<< boost::errinfo_api_function("in matrox consumer, pJVideoSurface SetTimeStampInfo"));
					}

					oHr = m_pJIOCardNodeForPlayback->SetNodeContentFrame(pJRenderredVideoSurface, pJRenderredAudioSamples, NULL);
					if (!oHr.DidSucceed())
					{
						CASPAR_THROW_EXCEPTION(caspar_exception()
							<< msg_info(mvErrorToString(oHr))
							<< boost::errinfo_api_function("in matrox consumer, SetNodeContentFrame"));
					}
					if (_IsFieldBased(m_Out_Resolution))
					{
						oHr = m_pJVancDataPackets->SetVancPacketsField(ui64PlaybackNanoTime, &lp.in_paVancPackets, lp.in_ui32PacketCount);
						if (!oHr.DidSucceed())
						{
							CASPAR_LOG(warning) << L"in matrox consumer, SetVancPacketsField:" << mvErrorToString(oHr);
						}
					}
					else
					{
						oHr = m_pJVancDataPackets->SetVancPacketsFrame(ui64PlaybackNanoTime, &lp.in_paVancPackets, lp.in_ui32PacketCount);
						if (!oHr.DidSucceed())
						{
							CASPAR_LOG(warning) << L"in matrox consumer, SetVancPacketsField:" << mvErrorToString(oHr);
						}
					}
					free(lp.pVideoBuffer);
					free(lp.pAudioBuffer);
				}
			}
			inline bool _IsFieldBased(SMvResolutionInfo &in_sResInfo)
			{
				return in_sResInfo.eScanMode == keMvScanModeFirstFieldTop || in_sResInfo.eScanMode == keMvScanModeSecondFieldTop;
			}
			inline bool _IsFieldBased()
			{
				
				return m_Out_Resolution.eScanMode == keMvScanModeFirstFieldTop || m_Out_Resolution.eScanMode == keMvScanModeSecondFieldTop;
			}
			CMvHResult _CleanUp()
			{
				CMvHResult oHr = MV_NOERROR;
				//1. remove clock event
				/*if (m_bSystemClockSet)
				{
				m_pJClock->UnRegisterForPeriodicNotification(this);
				m_bSystemClockSet = false;
				}*/
				

				m_pJClock = NULL;
				m_pJFlexEngine = NULL;

				// 2. unregister all callbacks
				if (m_pJErrorNotification && m_pJCardErrorCallback)
				{
					oHr = m_pJErrorNotification->UnregisterCallbackForNotification(m_pJCardErrorCallback);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox_interface, m_pJErrorNotification UnregisterCallback";
						return oHr;
					}
					m_pJCardErrorCallback = NULL;
					m_pJErrorNotification = NULL;
				}

				if (m_pJSystemTopologyErrorCallback)
				{
					oHr = m_pJSystemTopology->UnregisterCallbackForErrorNotification(m_pJSystemTopologyErrorCallback);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox_interface, Unregister SystemTopology Error";
						return oHr;
					}
					m_pJSystemTopologyErrorCallback = NULL;
				}

				//锁相状态获取和设置注册都没有做
				/*if (m_pJGenlcokStatusNotification)
				{
				hr = m_pJGenlcokStatusNotification->UnregisterCallbackForNotification(m_pJGenlockStatusCallback);
				ASSERT(SUCCEEDED(hr));

				m_pJGenlockStatusCallback = NULL;
				m_pJGenlcokStatusNotification = NULL;
				}*/

				// 3. Release allocated user buffer memory
				/*if (m_pUserBufferForRawDataCapture)
				{
				VirtualFree(m_pUserBufferForRawDataCapture, 0, MEM_RELEASE);
				m_pUserBufferForRawDataCapture = NULL;
				}

				if (m_pUserBufferForRawDataPlayback)
				{
				VirtualFree(m_pUserBufferForRawDataPlayback, 0, MEM_RELEASE);
				m_pUserBufferForRawDataPlayback = NULL;
				}*/

				// 4. Remove video surface/audio samples asynch error callback
				uint32_t ui32TotalManaged;    // Indicates the total number of video surfaces managed by the buffer pool.
				uint32_t ui32Outside;         // Indicates the number of video surfaces that are currently not in the buffer pool.
				uint32_t ui32Inside;          // Indicates the number of video surfaces that are currently in the buffer pool.

				if (m_pJVideoSurfaceAsynchErroCallback)
				{
					oHr = m_pJVideoUserBufferSurfacePoolForPlayback->RemoveCompletionObserver(m_pJVideoSurfaceAsynchErroCallback);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox consumer, m_pJVideoUserBufferSurfacePoolForCapture RemoveCompletionObserver";
						return oHr;
					}
					m_pJVideoUserBufferSurfacePoolForPlayback = NULL;
					/*hr = m_pJVideoUserBufferSurfacePoolForPlayback->RemoveCompletionObserver(m_pJVideoSurfaceAsynchErroCallback);
					ASSERT(SUCCEEDED(hr));*/

					m_pJVideoSurfaceAsynchErroCallback = NULL;

					oHr = m_pJVideoUserBufferSurfacePoolForPlayback->GetStatus(&ui32TotalManaged, &ui32Outside, &ui32Inside);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox consumer, m_pJVideoUserBufferSurfacePoolForCapture->GetStatus error";
						return oHr;
					}

					if (ui32Outside > 0)
					{
						oHr = MV_E_FAIL;
						if (!oHr.DidSucceed())
						{
							CASPAR_LOG(error) << L"in matrox consumer, m_pJVideoUserBufferSurfacePoolForCapture is not empty.";
						}
						return oHr;
					}

				}

				// 5. Remove audio samples asynch error callback
				if (m_pJAudioSamplesAsynchErroCallback)
				{
					oHr = m_pJAudioSamplesPoolForPlayback->RemoveCompletionObserver(m_pJAudioSamplesAsynchErroCallback);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox consumer, m_pJAudioSamplesPoolForCapture->RemoveCompletionObserver error";
						return oHr;
					}


					m_pJAudioSamplesAsynchErroCallback = NULL;

					//Check audio samples pool status
					oHr = m_pJAudioSamplesPoolForPlayback->GetStatus(&ui32TotalManaged, &ui32Outside, &ui32Inside);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox consumer, m_pJAudioSamplesPoolForCapture->GetStatus error";
						return oHr;
					}

					if (ui32Outside > 0)
					{

						oHr = MV_E_FAIL;
						if (!oHr.DidSucceed())
						{
							CASPAR_LOG(error) << L"in matrox consumer, m_pJAudioSamplesPoolForCapture->GetStatus ,out size not empty";
							return oHr;
						}
					}
				}
				if (m_IsVanc)
				{
					oHr = m_pJVancDataPackets->DisableVancDataPackets();
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox consumer, DisableVancDataPackets";
						return oHr;
					}
				}
				// Check if there is still video surface /audio sample outside

				// 6. clean up system topology
				//删除已经存在的拓扑
				if (m_pJSystemTopology)
				{
					oHr = m_pJSystemTopology->UnregisterCallbackForErrorNotification(m_pJErrorCallback);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"m_pJSystemTopology->UnregisterCallbackForErrorNotification error";
						return oHr;
					}
					oHr = m_pJSystemTopology->DestroyTopology();
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"m_pJSystemTopology->DestroyTopology error";
						return oHr;
					}
				}

				// 7. close handles
				/*for (int iIndex = 0; iIndex < keStreamingEventCount; iIndex++)
				{
				CloseHandle(m_ahStreamingThreadEventsToWatch[iIndex]);
				m_ahStreamingThreadEventsToWatch[iIndex] = NULL;
				}

				for (int iIndex = 0; iIndex < keDefaultStateWrittenCount; iIndex++)
				{
				CloseHandle(m_ahDefaultStateSignaling[iIndex]);
				m_ahDefaultStateSignaling[iIndex] = NULL;
				}

				m_pJSystemCardConfig = NULL;*/
				m_pJSystemTopology = NULL;
				return MV_NOERROR;
			}


		};
		matrox_interface_consumer::matrox_interface_consumer(consumer_need need, core::video_format format,int channels)
			:impl_(new impl(need, format,channels))
		{

		}

		/*bool matrox_interface::get_frame(MatroxFrame & frame) { return impl_->get_frame(frame); }
		int  matrox_interface::_GetChannels()
		{
			return impl_->_GetChannels();
		}*/
		void matrox_interface_consumer::_ProcessVanc(void * pvideo, void * paudio, void*pvideo1, void *paudio1,int nAR,int nCmd)
		{
			uint32_t in_ui32PacketCount = 1;
			SMvVancPacket in_paVancPackets;
			if (nAR==-1&&nCmd==-1)
			{
				in_ui32PacketCount = 0;//如果不存在AFD的话需要设置成0。
			}
			if (in_ui32PacketCount > 0)
			{

				SMvAFDAndBarDataVancPacket sAFDAndBarPacket;
				CMvHResult oHr = impl_->m_pJVancDataPackets->TransformVancPacketToAFDAndBarDataPacket(&in_paVancPackets, &sAFDAndBarPacket);
				sAFDAndBarPacket.sAFD.bIs16by9AspectRatio = nAR ? false : true;
				sAFDAndBarPacket.sAFD.ui8AFDCode = (uint8_t)nCmd;
				sAFDAndBarPacket.sBarData.bTopPresenceFlag = false;
				sAFDAndBarPacket.sBarData.bBottomPresenceFlag = false;
				sAFDAndBarPacket.sBarData.bLeftPresenceFlag = false;
				sAFDAndBarPacket.sBarData.bRightPresenceFlag = false;
				sAFDAndBarPacket.sBarData.uTopOrLeftBar.ui16LineNumberEndOfTopBar = 0;
				sAFDAndBarPacket.sBarData.uTopOrLeftBar.ui16PixelNumberEndOfLeftBar = 0;
				sAFDAndBarPacket.sBarData.uBottomOrRightBar.ui16LineNumberStartOfBottomBar = 0;
				sAFDAndBarPacket.sBarData.uBottomOrRightBar.ui16PixelNumberStartOfRightBar = 0;
				oHr = impl_->m_pJVancDataPackets->TransformAFDAndBarDataPacketToVancPacket(&sAFDAndBarPacket, 571, &in_paVancPackets);


			}
			impl_->QueueFieldOrFrame(pvideo, paudio, pvideo1, paudio1, &in_paVancPackets, in_ui32PacketCount);

		}
		bool matrox_interface_consumer::_IsFieldBased()
		{
			return impl_->_IsFieldBased();
		}
	}
}