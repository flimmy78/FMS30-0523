#pragma once
#include <MatroxDSXsdk.h>
#include <mvBaseInterface.h>
#include <mvHelperFunctions.h>

#include "matrox_interface_producer.h"
#include <mvIODefinitions.h>
#include "SDIInConnectorStatusCallback.h"
#include "ErrorNotificationCallback.h"
#include <common/log.h>
#include <vector>

#include <tbb/concurrent_queue.h>

#include <boost/lexical_cast.hpp>


namespace caspar {
	namespace matrox {
		struct SCardInfo
		{
			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			SMvGeneralHardwareInformation     sHwInfo;
			std::vector<TMvSmartPtr<IMvSdiVideoInputConnector> >				vecpJInputConnectors;
			std::vector<TMvSmartPtr<IMvSdiEmbeddedAudioInputPairConnector>>		vecpJSDIEAAudioInputConnectors;
		};
		
		struct matrox_interface_producer::impl : public CMvUnknown, public IMvSystemClockNotificationCallback
		{
			MVDECLARE_IUNKNOWN;
			//COM的对象接口参数，记为系统对象
			TMvSmartPtr<IMvSystemConfiguration>				m_IMvSystemConfiguration_=NULL;
			//板卡数量记录
			std::vector<SCardInfo>							m_CardConfigs;
			producer_need									m_need;
			//预设声音channel 24位 48000  int存储 pcm音频格式 channel为可设置 
			//测试一下matrox卡是否能转换channel数，需要研究
			unsigned int									m_preset_channel_;
			//锁相
			TMvSmartPtr<IMvSystemClock>						m_pJClock = NULL;
			//拓扑对象
			TMvSmartPtr<IMvSystemTopology>					m_pJSystemTopology = NULL;
			//node
			TMvSmartPtr<IMvNode>							m_pJIOCardNodeForCapture = NULL;
			//获取队列接口
			TMvSmartPtr<IMvFlexEngine>						m_pJFlexEngine = NULL;
			//Asynch error notification
			TMvSmartPtr<IMvErrorNotification>				m_pJErrorNotification = NULL;
			TMvSmartPtr<IMvErrorNotificationCallback>		m_pJCardErrorCallback = NULL;

			TMvSmartPtr<IMvSystemTopologyErrorCallback>		m_pJSystemTopologyErrorCallback = NULL;

			//Video user buffer surface pool manager
			TMvSmartPtr<IMvSurfacePool>						m_pJVideoUserBufferSurfacePoolForCapture = NULL;
			TMvSmartPtr<IMvAudioSamplesPool>				m_pJAudioSamplesPoolForCapture = NULL;
			SMvUserBufferSurfaceDescription					m_sUserBufferSurfaceDescription;

			//Video surface/Auduo sample aynch error callback
			TMvSmartPtr<IMvSurfacePoolCallback>				m_pJVideoSurfaceAsynchErroCallback = NULL;
			TMvSmartPtr<IMvAudioSamplesPoolCallback>		m_pJAudioSamplesAsynchErroCallback;
	
			uint32_t										m_ui32WriteToReadDelayInFrame = 1;
			uint32_t										m_ui32WriteToReadDelayInFrameOutputNode = 0;
			uint32_t										m_ui32DepthInFrame = 12;
			
			TMvSmartPtr<CStatusCallbackSdiIn>				m_pJSDIInputConnectorCallback = NULL;
			TMvSmartPtr<IMvVideoConnectorNotification>		m_pJSDIInputConnectorNotification = NULL;
			CMvCriticalSection								m_oCaptureQueueCriticalSection;
			//FMS
			SMvResolutionInfo								m_Out_Resolution;

			//这个参数一般不需要，除非是没有指定的时候才有用
			std::wstring									m_ratio;
			core::video_format								m_format_;


			tbb::atomic<bool>								is_running_;
			boost::thread									thread_;
			tbb::concurrent_bounded_queue<FrameforProducer>		frame_buffer_;
			bool											m_bSystemClockSet = false;
			bool											m_IsRunning = false;
			impl(
				core::video_format format,
				int NeedAChannel,
				producer_need need)
				:m_preset_channel_(NeedAChannel)
				,m_format_(format)
				,m_need(need)
				,CMvUnknown(L"procudrMvsNotificationCallback", NULL)
			{
				CASPAR_LOG(info) << L" matrox producer creat";
				
				CMvHResult oHr = MV_NOERROR;

				// 1.Initialize system configuration
				oHr = _SysConfiguration();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, _SysConfiguration"));
				}

				// 2.Create system topology
				oHr = _CreateSystemTopology();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, _CreateSystemTopology"));
				}
					
				// 3. Create FlexEngine
				
				oHr = _GetFlexEngine();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, _GetFlexEngine"));
				}
				// 4. Creating video/audio pool
				oHr =_CreateVideoAudioPoolManagers();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, _CreateVideoAudioPoolManagers"));
				}

				// 5. Set card asynch error callback
				
				oHr = m_CardConfigs[m_need.sdi].pJCardConfig->GetErrorNotification(&m_pJErrorNotification);
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, card GetErrorNotification"));
				}
				if (m_pJErrorNotification==NULL)
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info("m_pJErrorNotification NULL")
						<< boost::errinfo_api_function("in matrox_interface, GetErrorNotification"));
				}
				
				m_pJCardErrorCallback = new CErrorNotificationCallback;
				if (m_pJCardErrorCallback==nullptr)
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info("m_pJCardErrorCallback NULL"));
				}
				oHr = m_pJErrorNotification->RegisterCallbackForNotification(m_pJCardErrorCallback);
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface,  card RegisterCallback"));
				}
				

				// 6. register for system topology asynch error call back
					
				m_pJSystemTopologyErrorCallback = new CErrorNotificationCallback(m_Out_Resolution);
				if (m_pJSystemTopologyErrorCallback==nullptr)
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info("in matrox_interface,new m_pJSystemTopologyErrorCallback"));
				}
				oHr = m_pJSystemTopology->RegisterCallbackForErrorNotification(m_pJSystemTopologyErrorCallback);
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, topology RegisterCallback"));
				}
			
				//这个暂时先不弄
				// 7. create events used
			/*	if (!m_hClockEvent)
				{
					m_hClockEvent = ::CreateEvent(NULL, false, false, NULL);
				}*/
				is_running_ = true;
				thread_ = boost::thread([this] {run(); });
			}
			~impl()
			{
				m_IsRunning = false;
				CMvHResult oHr= _CleanUp();	
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
				CMvHResult oHr;
				//获取matrox系统配置
				oHr = CoCreateInstance(CLSID_MvSystemConfiguration,
					NULL,
					CLSCTX_INPROC_SERVER,
					IID_IMvSystemConfiguration,
					(void**)&m_IMvSystemConfiguration_);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface, CoCreateInstance";
					return oHr;
				}
				else
				{
					if (m_IMvSystemConfiguration_==NULL)
					{
						CASPAR_LOG(error) << L"in matrox_interface, m_IMvSystemConfiguration_ NULL";
						return oHr;
					}
				}
				//获取板卡信息
				oHr = _EnumerateCards();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}
				//检测板卡参数是否符合启动条件：是否有音视频信号，与给定的参数是否一致，
				//板卡系统是否已经初始化完成
				//板卡温度检测，以及是否有提供一些判断机器时候可以启动的条件参数接口
				//开机注意事项

				//板卡数量判断
				
				if (m_CardConfigs.size()<m_need.card)
				{
					CASPAR_LOG(error) << L"in matrox_interface, card count less than deviceIndex";
					return MV_E_INVALID_PARAMETER;
				}
				//检测输入通道数量
				if (m_CardConfigs[m_need.card].vecpJInputConnectors.size() == 0 || 
					m_CardConfigs[m_need.card].vecpJInputConnectors.size() < (m_need.sdi+1))
				{
					CASPAR_LOG(error) << L"in matrox_interface,input connectors empty or less than connector index";
					return MV_E_INVALID_PARAMETER;
				}

				//检测视频和音频
				oHr = _AVCheck();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}
				//检测开机温度是否合适，配置温度设置
				oHr = _SGTemperature();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}
				return MV_NOERROR;
			}

			CMvHResult _AVCheck()
			{
				//检测视频信号
				//sdi视频信号参数
				SMvVideoConnectorStatus io_rsVideoStatus;
				//预设参数
				CMvHResult oHr = MV_NOERROR;
				oHr = m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi]->GetVideoConnectorStatus(io_rsVideoStatus);
				//注意这个地方，无信号这个地方返回什么
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface, GetVideoConnectorStatus";
					return oHr;
				}
				//对比信号源 当视频的预设与源不一致的时候，以预设分辨率作为matrox给定的源。
				//注意，io_rsVideoStatus的宽高是否是有效值，如果没有效，是不是就是没有信号，需要测试一下
				if (m_Out_Resolution.ulHeight != io_rsVideoStatus.sDetectedResolution.ulHeight || m_Out_Resolution.ulWidth != io_rsVideoStatus.sDetectedResolution.ulWidth)
				{
					CASPAR_LOG(warning) << L"in matrox_interface, preinstall Resolution not fit,Source Resolution : "
						<< io_rsVideoStatus.sDetectedResolution.ulWidth
						<< "*"
						<< io_rsVideoStatus.sDetectedResolution.ulHeight;
					return MV_E_INVALID_PARAMETER;
				}
				//autio 参数对比，不一致返回false
				//声音接口还没弄明白是怎么处理的
				//声道参数支持最多为32声道，需要判断声音声道参数是否一致，不一致说明是多音轨的
				SMvAudioPairStatus AudioPair[32];
				uint32_t in_ui32ArrayCount = 32;
				oHr = m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi]->GetSdiEmbeddedAudioInputPairConnectorsStatuses(AudioPair, in_ui32ArrayCount);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(warning) << L"in matrox_interface,GetAudioInputPairConnectors";
					return oHr;
				}
				/////////////////////
				//    声音部分需要做测试才能正确处理，原则是：能够自适应，如果预设与源不一致，预设为主，matrox需要支持转换
				////////

				//简单处理，只要是有效的channel就认为一个音轨
				//需要调试
				int ChannelNums = 0;
				int AudioPerSampleBits = 8;
				int AudioRates = 48000;//默认是48000采样
				for (int i = 0;i < in_ui32ArrayCount;i++)
				{
					if (AudioPair[0].bIsPairPresent)
					{
						ChannelNums++;
						AudioPerSampleBits = AudioPair->eBitsPerSample;
						//AudioRates = AudioPair->eStatusInfo.keEAChannelStatusInfoInvalid
					}
				}
				//判断 channel 不一致需要返回错误，或者测试matrox是否能够转换channel数
				if (ChannelNums != m_preset_channel_)
				{
					CASPAR_LOG(warning) << L"in matrox_interface,preinstall audio channels not fit";
					return MV_E_INVALID_PARAMETER;
				}
				return MV_NOERROR;
			}
			
			CMvHResult _SGTemperature()
			{
				//这个函数接口需要实现
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
				CASPAR_LOG(error) << L"in matrox_interface, Unspecified or invalid resolution format";
			}
			
			CMvHResult _ValidateAndDisplayCardTemperature(SCardInfo & in_krsCardInfo)
			{
				CMvHResult oHr = MV_NOERROR;

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

				in_krsCardInfo.pJCardConfig->GetTemperatureSensorInfo(asInfo, 3);

				for (int i = 0; i < 3; ++i)
				{
					if (asInfo[i].eTemperatureID != keTemperatureSensorIDInvalid)
					{
						if (asInfo[i].dTemperature >= asInfo[i].dTemperatureErrorThreshold)
						{
							CASPAR_LOG(warning) << L"in matrox_interface,WARNING: OVERHEAT!";
							oHr = MV_E_FAIL;
						}

						if (asInfo[i].eFanStatus == keMvFanStatusTooSlowOrStopped)
						{
							CASPAR_LOG(warning) << L"in matrox_interface,Fan: ERROR: Too slow or stopped!";
							oHr = MV_E_FAIL;
						}
						else if (asInfo[i].eFanStatus == keMvFanStatusOk)
						{
							//printf("Fan: Ok.\n");
						}
						// else { there is no fan so no fan message to output. }
					}
				}
				return NOERROR;
			}
			CMvHResult _EnumerateCards()
			{
				CMvHResult oHr = MV_NOERROR;
				if (m_IMvSystemConfiguration_ == NULL)
				{
					CASPAR_LOG(error) << L"in matrox_interface, m_IMvSystemConfiguration_ NULL";
					return MV_E_FAIL;
				}

				// Get the cards enumerator
				TMvSmartPtr<IMvSystemConfigurationCardEnumerator> pJEnum;
				oHr = m_IMvSystemConfiguration_->CreateCardEnumerator(&pJEnum);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface, _EnumerateCards CreateCardEnumerator";
					return oHr;
				}

				TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
				if (pJEnum==nullptr)
				{
					CASPAR_LOG(error) << L"in matrox_interface, get cards pJEnum NULL";
					return MV_E_FAIL;
				}
				do{
					pJCardConfig = NULL;
					oHr = pJEnum->Next(&pJCardConfig);
					if (!oHr.DidSucceed())
					{
						break;
					}
					if (pJCardConfig == nullptr)
					{
						CASPAR_LOG(error) << L"in matrox_interface, pJCardConfig NULL";
						return MV_E_FAIL;
					}
					SCardInfo	CardInfo;
					CardInfo.sHwInfo.size = sizeof(CardInfo.sHwInfo);
					CardInfo.sHwInfo.sConnectorsDescription.size = sizeof(CardInfo.sHwInfo.sConnectorsDescription);
					
					oHr = pJCardConfig->GetCardInformation(&CardInfo.sHwInfo, 0);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox_interface, GetCardInformation";
						return oHr;
					}

					TMvSmartPtr<IMvSdiVideoOutputConnectorsEnumerator>	pJOutputEnum;
					TMvSmartPtr<IMvSdiVideoInputConnectorsEnumerator>	pJInputEnum;

					// Check if there is at least one input connector
					oHr = pJCardConfig->CreateSdiVideoInputConnectorsEnumerator(&pJInputEnum);

					// Enumerate all connectors
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox_interface, CreateSdiVideoInputConnectorsEnumerator";
						return oHr;
					}
					TMvSmartPtr<IMvSdiVideoInputConnector> pJInputConnector;

					// Get first connector						
					do
					{
						pJInputConnector = NULL;
						oHr = pJInputEnum->Next(&pJInputConnector);
						CardInfo.vecpJInputConnectors.push_back(pJInputConnector);
					} while (oHr.DidSucceed());
					// Ignore the error from the NEXT of the enumerator.
					// We get audio from SDI Embedded audio connector 0 by default
					TMvSmartPtr<IMvSdiEmbeddedAudioInputPairConnector> pJSdiEmbeddedAudioInputConnector;
					TMvSmartPtr<IMvSdiEmbeddedAudioInputPairConnectorsEnumerator> pJEnumerator;
					uint32_t ui32AudioConnectorCount = 0;

					if (CardInfo.vecpJInputConnectors.size()<(m_need.sdi+1))
					{
						CASPAR_LOG(error) << L"in matrox_interface, Input Connectors counts less than index";
						return MV_E_INVALID_PARAMETER;
					}
					oHr = CardInfo.vecpJInputConnectors[m_need.sdi]->CreateSdiEmbeddedAudioInputPairConnectorsEnumerator(&pJEnumerator);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox_interface, Create Audio Input Pair Connectors Enumerator error";
						return oHr;
					}
					while (pJEnumerator->Next(&pJSdiEmbeddedAudioInputConnector) == MV_NOERROR && ui32AudioConnectorCount < 8)
					{
						CardInfo.vecpJSDIEAAudioInputConnectors.push_back(pJSdiEmbeddedAudioInputConnector);
						pJSdiEmbeddedAudioInputConnector = NULL;
						ui32AudioConnectorCount++;
					}

					if (ui32AudioConnectorCount == 0)
					{
						CASPAR_LOG(error) << L"in matrox_interface, audio connectors count is 0";
						return MV_E_NOT_FOUND;
					}					
					m_CardConfigs.push_back(CardInfo);

				}while (oHr.DidSucceed());
				return MV_NOERROR;
			}
			

			//---------------------------------------------------------------------------------

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
				oHr =_BuildMainTopology();
				if (!oHr.DidSucceed())
				{
					return oHr;
				}
				return oHr;
			}

			CMvHResult _CleanTopogy()
			{
				CMvHResult oHr;
				
				
				//
				//清除卡上的元素所有的默认状态并且永久内存，这个接口如果不是清除所有的拓扑的话应该不需要调用吧
				oHr = m_CardConfigs[m_need.card].pJCardConfig->ClearDefaultsAndPermanentMemory();

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,ClearDefaultsAndPermanentMemory";
					return oHr;
				}

				TMvSmartPtr<IMvTopologiesEnumerator>	pJTopologyEnumerator = NULL;
				TMvSmartPtr<IMvTopology>				pJTopology = NULL;

				std::wstring strTopologyName = L"MatroxProducer" + boost::lexical_cast<std::wstring>(m_need.sdi);

				oHr = m_CardConfigs[m_need.card].pJCardConfig->CreateTopologiesEnumerator(&pJTopologyEnumerator);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,CreateTopologiesEnumerator";
					return oHr;
				}
				if (pJTopologyEnumerator==nullptr)
				{
					CASPAR_LOG(error) << L"in matrox_interface,pJTopologyEnumerator NULL";
					return MV_E_FAIL;
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
							CASPAR_LOG(error) << L"in matrox_interface,DestroyTopology";
							return oHr;
						}
					}
				} while (oHr.DidSucceed());

				return MV_NOERROR;
			}
			CMvHResult _SetGenlockClock()
			{
				CMvHResult oHr = MV_NOERROR;

				// Get the clock enumerator interface.
				TMvSmartPtr<IMvSystemClockEnumerator>	pJClockEnum;
				TMvSmartPtr<IMvSystemClock>				pJClock;

				oHr = m_CardConfigs[m_need.sdi].pJCardConfig->CreateSystemClockEnumerator(&pJClockEnum);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,CreateSystemClockEnumerator";
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

							if (m_CardConfigs[m_need.sdi].pJCardConfig == pJTempCard)
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
					CASPAR_LOG(error) << L"in matrox_interface,clock enum not find genlock";
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

				std::wstring strTopologyName = L"MatroxProducer" + boost::lexical_cast<std::wstring>(m_need.sdi);
				oHr = m_IMvSystemConfiguration_->CreateSystemTopology(u8(strTopologyName).c_str(), m_pJClock, &m_pJSystemTopology);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,CreateSystemTopology";
					return oHr;
				}
				return oHr;
			}
			CMvHResult _BuildMainTopology()
			{
				CMvHResult oHr = MV_NOERROR;

				// A/V Input node on IO
				SMvNodeSettings      sInputNodeSettings;
				SMvNodeSettingsVideo sInputVideoSettings;
				SMvNodeSettingsAudio sInputAudioSettings;
				SMvNodeSettingsVanc  sInputVancSettings;

				_SetInputNodeDefaultSettings(sInputNodeSettings, sInputVideoSettings, sInputAudioSettings,sInputVancSettings);
				switch (m_preset_channel_)
				{
				case 1:
					sInputAudioSettings.eChannelType = keChannelTypeMono;
					break;
				case 2:
					sInputAudioSettings.eChannelType = keChannelTypeStereo;
					break;
				case 8:
					sInputAudioSettings.eChannelType = keChannelType8Tracks;
					break;
				case 16:
					sInputAudioSettings.eChannelType = keChannelType16Tracks;
					break;
				default:
					break;
				}
				std::wstring sname = L"InputCardNode" + boost::lexical_cast<std::wstring>((m_need.sdi));
				sprintf_s(sInputNodeSettings.szName, _countof(sInputNodeSettings.szName), u8(sname).c_str());
				
				oHr = m_pJSystemTopology->CreateCardNode(sInputNodeSettings,
					&sInputVideoSettings,
					&sInputAudioSettings,
					&sInputVancSettings,
					m_CardConfigs[m_need.card].pJCardConfig,
					&m_pJIOCardNodeForCapture);

				// Input Stream 
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,CreateCardNode";
					return oHr;
				}

			
				SMvInputStreamSettings sInputStreamSettings;
				uint32_t	ui32AudioInputConnectorCount = 1;
				uint32_t	ui32VideoInputConnectorCount = 1;

				_SetInputStreamDefaultSettings(sInputStreamSettings);

				IMvConnector * apIInputConnetorForVideo[4];
				IMvConnector * apIInputConnetorForAudio[8];//最多到8声道

				for (int i = 0; i < m_CardConfigs[m_need.card].vecpJInputConnectors.size(); i++)
				{
					apIInputConnetorForVideo[i] = m_CardConfigs[m_need.card].vecpJInputConnectors[i];
				}

				for (int i = 0; i<m_CardConfigs[m_need.card].vecpJSDIEAAudioInputConnectors.size(); i++)
				{
					apIInputConnetorForAudio[i] = m_CardConfigs[m_need.card].vecpJSDIEAAudioInputConnectors[i];
				}

				//input stream

				TMvSmartPtr<IMvInputStream>		m_pJInputStream;
				sname = L"InputStream" + boost::lexical_cast<std::wstring>((int)m_need.sdi);

				oHr = m_pJSystemTopology->CreateInputStreamSdi(u8(sname).c_str(),
					apIInputConnetorForVideo,
					NULL,
					ui32VideoInputConnectorCount,
					apIInputConnetorForAudio,
					ui32AudioInputConnectorCount,
					m_pJIOCardNodeForCapture,
					m_Out_Resolution,
					sInputStreamSettings,
					&m_pJInputStream);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,CreateInputStreamSdi";
					return oHr;
				}
				return MV_NOERROR;
			}

			CMvHResult _SetupGenlockResolution()
			{
				CMvHResult oHr = MV_NOERROR;

				// Get genlock interface.         
				TMvSmartPtr<IMvGenlockConfiguration>	pJGenlockConfig;

				oHr = m_CardConfigs[m_need.sdi].pJCardConfig->GetGenlockConfiguration(&pJGenlockConfig);
			
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,GetGenlockConfiguration";
					return oHr;
				}

				// Get current genlock settings

				SMvGenlockSettings sCurrentGenlockSettings = { sizeof(sCurrentGenlockSettings) };
				oHr = pJGenlockConfig->GetGenlockSettings(sCurrentGenlockSettings);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,GetGenlockSettings";
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
					CASPAR_LOG(error) << L"in matrox_interface,SetGenlockSettings";
					return oHr;
				}
				return MV_NOERROR;
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
				out_sNodeSettingsVideo.eColorimetry = NMvHelper::GetColorimetryFromResolution(m_Out_Resolution);
				out_sNodeSettingsVideo.eSurfaceFormat = keMvSurfaceFormatYUYV422;

				out_sNodeSettingsAudio.ui32Size = sizeof(SMvNodeSettingsAudio);
				out_sNodeSettingsAudio.eChannelType = keChannelTypeStereo;
				out_sNodeSettingsAudio.eDataType = keAudioDataTypePCM;
				out_sNodeSettingsAudio.ui32BitsPerSample = 32;
				out_sNodeSettingsAudio.ui32ValidBitsPerSample = 24;

				out_sNodeSettingsVanc.eVancFormat = keMvSurfaceFormatMatroxAncillaryData;
				out_sNodeSettingsVanc.ui32ComponentBitCount = 16;

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

			//---------------------------------------------------------------------------------

			CMvHResult _GetFlexEngine()
			{
				CMvHResult oHr = MV_NOERROR;
				if (!m_CardConfigs[m_need.sdi].pJCardConfig)
				{
					CASPAR_LOG(error) << L"in matrox_interface,m_CardConfigs[m_need.sdi].pJCardConfig is NULL";
					return MV_E_FAIL;
				}
				oHr = m_CardConfigs[m_need.sdi].pJCardConfig->QueryInterface(IID_IMvFlexEngine, (void**)&m_pJFlexEngine);
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
				int      nBufferType;

				if (m_IMvSystemConfiguration_ == NULL)
				{
					CASPAR_LOG(error) << L"in matrox_interface,_CreateVideoAudioPoolManagers,m_IMvSystemConfiguration_ NULL";
					return MV_E_FAIL;
				}

				_DefineUserBufferDescription();

				// User buffer surface pool for capture
				oHr = m_IMvSystemConfiguration_->CreateSurfaceUserBufferPool(L"m_pJVideoUserBufferSurfacePoolCapture",
					ui32PoolSize,
					ui32PoolSize,
					m_Out_Resolution.eScanMode,
					&m_pJVideoUserBufferSurfacePoolForCapture);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,CreateSurfaceUserBufferPool";
					return oHr;
				}
				
				


				//队列报错信息注册
				m_pJVideoSurfaceAsynchErroCallback = new CErrorNotificationCallback(m_Out_Resolution);
				if (m_pJAudioSamplesAsynchErroCallback==nullptr)
				{
					CASPAR_LOG(error)<< L"in matrox_interface,m_pJAudioSamplesAsynchErroCallback NULL";
					return MV_E_FAIL;
				}
				oHr = m_pJVideoUserBufferSurfacePoolForCapture->AddCompletionObserver(m_pJVideoSurfaceAsynchErroCallback);

				//Create Audio samples pool
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,AddCompletionObserver";
					return oHr;
				}
				SMvCreateAudioSamplesDescription sAudioSamplesDescription;

				_DefineAudioSamplesDescription(&sAudioSamplesDescription);

				oHr = m_IMvSystemConfiguration_->CreateAudioSamplesPool(L"m_pJAudioSamplesPoolForCapture", ui32PoolSize, ui32PoolSize, sAudioSamplesDescription, &m_pJAudioSamplesPoolForCapture);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,CreateAudioSamplesPool";
					return oHr;
				}
				
				m_pJAudioSamplesAsynchErroCallback = new CErrorNotificationCallback(m_Out_Resolution);
				
				oHr = m_pJAudioSamplesPoolForCapture->AddCompletionObserver(m_pJAudioSamplesAsynchErroCallback);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,AddCompletionObserver";
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
				m_sUserBufferSurfaceDescription.ePolarity = m_Out_Resolution.eScanMode== keMvScanModeProgressive ?keMvPolarityProgressiveFrame:keMvPolarityFirstField;
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
				io_psAudioSamplesDescription->ePolarity = m_Out_Resolution.eScanMode==EMvScanMode::keMvScanModeFirstFieldTop? keMvPolarityFirstField : keMvPolarityProgressiveFrame;
				EMvChannelType audiotype = keChannelTypeStereo;
				switch (m_preset_channel_)
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
//------------------------------
			//设置分辨率回调函数
			CMvHResult _set_callbakc()
			{
				CMvHResult oHr = MV_NOERROR;

				//自适应分辨率回调设置
				m_pJSDIInputConnectorCallback = new CStatusCallbackSdiIn(m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi], m_format_);
				if (m_pJSDIInputConnectorCallback==NULL)
				{
					CASPAR_LOG(error) << L"in matrox_interface,m_pJSDIInputConnectorCallback NULL";
					return MV_E_FAIL;
				}
				
				oHr = m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi]->GetVideoConnectorNotification(&m_pJSDIInputConnectorNotification);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface, GetVideoConnectorNotification";
					return oHr;
				}
				oHr = m_pJSDIInputConnectorNotification->RegisterCallbackForNotification(m_pJSDIInputConnectorCallback);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface, InputConnector RegisterCallback";
				}
				return MV_NOERROR;
			}
			
			//将所有的队列清空，将回调注销，并且消除系统拓扑
			//考虑一下是否将拓扑也放到这里面来，好像不方便先不放了
			CMvHResult _CleanUp()
			{
				CMvHResult oHr = MV_NOERROR;
				//1. remove clock event
				/*if (m_bSystemClockSet)
				{
					m_pJClock->UnRegisterForPeriodicNotification(this);
					m_bSystemClockSet = false;
				}*/
				//队列创建
				if (frame_buffer_.size())
				{
					frame_buffer_.clear();
				}

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
						CASPAR_LOG(error) << L"in matrox_interface, Unregister SystemTopology Error" ;
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

				oHr = m_pJSDIInputConnectorNotification->UnregisterCallbackForNotification(m_pJSDIInputConnectorCallback);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface, m_pJSDIInputConnectorNotification UnregisterCallback";
					return oHr;
				}
				m_pJSDIInputConnectorCallback = NULL;
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
					oHr = m_pJVideoUserBufferSurfacePoolForCapture->RemoveCompletionObserver(m_pJVideoSurfaceAsynchErroCallback);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"m_pJVideoUserBufferSurfacePoolForCapture RemoveCompletionObserver error";
						return oHr;
					}
					m_pJVideoUserBufferSurfacePoolForCapture = NULL;
					/*hr = m_pJVideoUserBufferSurfacePoolForPlayback->RemoveCompletionObserver(m_pJVideoSurfaceAsynchErroCallback);
					ASSERT(SUCCEEDED(hr));*/

					m_pJVideoSurfaceAsynchErroCallback = NULL;

					oHr = m_pJVideoUserBufferSurfacePoolForCapture->GetStatus(&ui32TotalManaged, &ui32Outside, &ui32Inside);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"m_pJVideoUserBufferSurfacePoolForCapture->GetStatus error";
						return oHr;
					}

					if (ui32Outside > 0)
					{
						oHr = MV_E_FAIL;
						if (!oHr.DidSucceed())
						{
							CASPAR_LOG(error) << L"m_pJVideoUserBufferSurfacePoolForCapture is not empty.";
						}
						return oHr;
					}
					
				}

				// 5. Remove audio samples asynch error callback
				if (m_pJAudioSamplesAsynchErroCallback)
				{
					oHr = m_pJAudioSamplesPoolForCapture->RemoveCompletionObserver(m_pJAudioSamplesAsynchErroCallback);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"m_pJAudioSamplesPoolForCapture->RemoveCompletionObserver error";
						return oHr;
					}
					

					m_pJAudioSamplesAsynchErroCallback = NULL;

					//Check audio samples pool status
					oHr = m_pJAudioSamplesPoolForCapture->GetStatus(&ui32TotalManaged, &ui32Outside, &ui32Inside);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"m_pJAudioSamplesPoolForCapture->GetStatus error";
						return oHr;
					}

					if (ui32Outside > 0)
					{

						oHr = MV_E_FAIL;
						if (!oHr.DidSucceed())
						{
							CASPAR_LOG(error) << L"m_pJAudioSamplesPoolForCapture->GetStatus ,out size not empty";
							return oHr;
						}
					}
				}

				// Check if there is still video surface /audio sample outside
				
				// 6. clean up system topology
				//删除已经存在的拓扑
				if (m_pJSystemTopology)
				{
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

			//---------------------------------------------------------------------------------
			bool _IsCardUHDWithBuffers(IMvCardConfiguration * in_pICardConfiguration)
			{
				// Check if this is an X.mio2plus or a DSX LE3 card
				bool bOldCard = false;
				SMvGeneralHardwareInformation sCardInfo = { sizeof(sCardInfo) };
				sCardInfo.sConnectorsDescription.size = sizeof(sCardInfo.sConnectorsDescription);

				CMvHResult oHr = in_pICardConfiguration->GetCardInformation(&sCardInfo, 0);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"Error: Unable to get the matrox card information";
				}

				switch (sCardInfo.eHardwareSerieDetected)
				{
				case kEMvHardwareSerieDSXmio2plus5000:
				case kEMvHardwareSerieDSXmio2plus6000:
				case kEMvHardwareSerieDSXmio2plus8000:
				case kEMvHardwareSerieDSXmio2plus8500:
				case kEMvHardwareSerieDSXLE3_100:
				case kEMvHardwareSerieDSXLE3_110:
				case kEMvHardwareSerieDSXLE3_200:
				case kEMvHardwareSerieDSXLE3_500:
				case kEMvHardwareSerieDSXLE3_550:
					bOldCard = true;
					break;

				default:
					break;
				}

				return bOldCard;
			}

			//需要重新实现方法
			bool get_frame(FrameforProducer& frame)
			{
				if (m_pJSDIInputConnectorCallback->change())
				{
					
					SMvVideoConnectorStatus io_rsVideoStatus;
					SMvAudioPairStatus out_asAudioStatus[16];
					m_pJSDIInputConnectorCallback->GetStatus(io_rsVideoStatus, out_asAudioStatus);
					uint32_t  ulWidth = io_rsVideoStatus.sDetectedResolution.ulWidth;
					uint32_t  ulHeight = io_rsVideoStatus.sDetectedResolution.ulHeight;
					switch (ulWidth)
					{
					case 720:
					{
						if (ulHeight==576)
						{
							if (io_rsVideoStatus.sDetectedResolution.eScanMode == keMvScanModeProgressive)
							{
								m_format_ = core::video_format::x576p2500;
							}
							else
							{
								m_format_ = core::video_format::pal;
							}
						}
						if (ulHeight == 480)
						{
							m_format_ = core::video_format::ntsc;
						}
					}
					break;
					case 1920:
					{
						if (io_rsVideoStatus.sDetectedResolution.eScanMode == keMvScanModeFirstFieldTop || io_rsVideoStatus.sDetectedResolution.eScanMode == keMvScanModeSecondFieldTop)
						{
							m_format_ = core::video_format::x1080i5000;
						}
						else
						{
							m_format_ = core::video_format::x1080p2500;
						}
					}
					break;
					case 3840:
					{
						m_format_ = core::video_format::x2160p2500;
					}
					break;
					case 1280:
					{
						m_format_ = core::video_format::x720p2500;
					}
					break;
					default:
						m_format_ = core::video_format::invalid;
						break;
					}
					m_IsRunning = false;
					//这个位置一定不能用线程执行，会崩溃，原因是有来到这个函数
					restart();
					return false;
				}
				if (!m_IsRunning)
					return false;
				//return pJInputTopology->get_frame(frame);
				return false;
			}
			void restart()
			{
				CMvHResult oHr = m_pJSDIInputConnectorNotification->RegisterCallbackForNotification(m_pJSDIInputConnectorCallback);
				m_pJSDIInputConnectorNotification = NULL;
				m_pJSDIInputConnectorNotification = NULL;

				
				boost::this_thread::sleep_for(boost::chrono::milliseconds(800));
			}
			void run()
			{
				boost::this_thread::sleep_for(boost::chrono::milliseconds(800));
				CMvHResult oHr = MV_NOERROR;
				TMvSmartPtr<IMvSurface>			pJCaptureVideoSurfaceUser = NULL;
				TMvSmartPtr<IMvAudioSamples> 	pJCaptureAudioSamplesHost = NULL;

				uint64_t       ui64CaptureNanoTime;
				uint64_t       ui64SampleTime;
				unsigned long  ulAudioSampleCount;
				unsigned long  ulAudioSampleValidBufferLength;

				uint8_t *											m_pUserBufferForRawDataCapture;
				//将视频指针申请空间
				if (m_Out_Resolution.eScanMode == keMvScanModeFirstFieldTop)
				{
					//半场数据高度是一半
					m_pUserBufferForRawDataCapture = (uint8_t *)malloc(m_Out_Resolution.ulWidth * 2 * m_Out_Resolution.ulHeight / 2);
				}
				else
				{
					//逐行
					m_pUserBufferForRawDataCapture = (uint8_t *)malloc(m_Out_Resolution.ulWidth * 2 * m_Out_Resolution.ulHeight);
				}

				while (m_IsRunning)
				{
					if (!m_bSystemClockSet)
					{
						oHr = _SetSystemClockCallback();
						if (!oHr.DidSucceed())
						{
							//异常
							CASPAR_THROW_EXCEPTION(caspar_exception()
								<< msg_info(mvErrorToString(oHr))
								<< boost::errinfo_api_function("in matrox_interface, _SetSystemClockCallback"));
						}
						ui64CaptureNanoTime = _GetNextClockTimeForCapture();
						oHr = m_pJVideoUserBufferSurfacePoolForCapture->WaitForSurface(1000, &pJCaptureVideoSurfaceUser);
						if (!oHr.DidSucceed())
						{
							//异常
							CASPAR_THROW_EXCEPTION(caspar_exception()
								<< msg_info(mvErrorToString(oHr))
								<< boost::errinfo_api_function("in matrox_interface, WaitForSurface"));
						}

						m_sUserBufferSurfaceDescription.pBuffer = m_pUserBufferForRawDataCapture;    //Be careful, overwritten here, apply multiple allocated memory

																									 // pointing to user buffer
						oHr = pJCaptureVideoSurfaceUser->AssignUserBufferReference(&m_sUserBufferSurfaceDescription);

						// synchronize surface
						if (!oHr.DidSucceed())
						{
							CASPAR_THROW_EXCEPTION(caspar_exception()
								<< msg_info(mvErrorToString(oHr))
								<< boost::errinfo_api_function("in matrox_interface,AssignUserBufferReference"));
						}
						
						//NMvs::PrepareSynchronization(pJCaptureVideoSurfaceUser, ui64CaptureNanoTime);
						
						
						//音频
						oHr = m_pJAudioSamplesPoolForCapture->WaitForAudioSamples(1000, &pJCaptureAudioSamplesHost);
						if (!oHr.DidSucceed())
						{
							CASPAR_THROW_EXCEPTION(caspar_exception()
								<< msg_info(mvErrorToString(oHr))
								<< boost::errinfo_api_function("in matrox_interface,WaitForAudioSamples"));
						}

						// Set Audio sample buffer size
						
						ui64SampleTime = MvGetSampleForNanoTime(ui64CaptureNanoTime, m_Out_Resolution);
						ulAudioSampleCount = (unsigned long)MvGetAudioSamplesFromReferencedVideoUnits(1, ui64SampleTime, m_Out_Resolution);
						switch (m_preset_channel_)
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
					
						oHr = pJCaptureAudioSamplesHost->SetLength(ulAudioSampleValidBufferLength);
						if (!oHr.DidSucceed())
						{
							CASPAR_THROW_EXCEPTION(caspar_exception()
								<< msg_info(mvErrorToString(oHr))
								<< boost::errinfo_api_function("in matrox_interface,SetLength"));
						}
						
						//Prepare synchronization on audio samples
						//NMvs::PrepareSynchronization(pJCaptureAudioSamplesHost, ui64CaptureNanoTime);
						//Capture video/audio
						oHr = m_pJIOCardNodeForCapture->GetNodeContentFrame(pJCaptureVideoSurfaceUser, pJCaptureAudioSamplesHost, NULL);
						if (!oHr.DidSucceed())
						{
							CASPAR_THROW_EXCEPTION(caspar_exception()
								<< msg_info(mvErrorToString(oHr))
								<< boost::errinfo_api_function("in matrox_interface,GetNodeContentFrame"));
						}
							
						//get audio buffer;
						void *out_ppBuffer = nullptr;
						unsigned long  out_pulLength = 0;
						

						oHr = pJCaptureAudioSamplesHost->GetBufferAndLength(&out_ppBuffer, &out_pulLength);
						if (!oHr.DidSucceed())
						{
							CASPAR_THROW_EXCEPTION(caspar_exception()
								<< msg_info(mvErrorToString(oHr))
								<< boost::errinfo_api_function("in matrox_interface,GetBufferAndLength"));
						}
						uint8_t * audiobuffer = (uint8_t*)malloc(out_pulLength);
						memcpy(audiobuffer, out_ppBuffer, out_pulLength);


						FrameforProducer mvframe;
						mvframe.height = m_Out_Resolution.ulHeight;
						mvframe.width = m_Out_Resolution.ulWidth == 768 ? 720 : m_Out_Resolution.ulWidth;
						mvframe.interlaced_frame = m_Out_Resolution.eScanMode == EMvScanMode::keMvScanModeInvalid ? 1 : 0;
						mvframe.top_field_first = m_Out_Resolution.eScanMode == EMvScanMode::keMvScanModeFirstFieldTop ? 1 : 0;
						mvframe.pvideo = std::shared_ptr<uint8_t>(m_pUserBufferForRawDataCapture, [&](uint8_t* p) {free(p); });
						mvframe.paudio = std::shared_ptr<uint8_t>(audiobuffer, [&](uint8_t* p) {free(p); });
						mvframe.afd_aspect_ratio_ = m_Out_Resolution.eAspectRatio;
						mvframe.afd_aspect_ratio_ = -1;
						mvframe.afd_command_ = -1;
						switch (m_Out_Resolution.eFrameRate)
						{
						case keMvFrameRate25:
							mvframe.usample = (48000 / 25);
						case keMvFrameRate30:
							mvframe.usample = (48000 / 30);
						case keMvFrameRate50:
							mvframe.usample = (48000 / 50);
						case keMvFrameRate60:
							mvframe.usample = (48000 / 60);
						default:
							mvframe.usample = (48000 / 25);
							break;
						}
						
						//Pass captured video/audio to queue for rendering process
						CMvAutoLock oLock(&m_oCaptureQueueCriticalSection);
						frame_buffer_.push(mvframe);	
					}
				}
				//free(m_pUserBufferForRawDataCapture);
			}
			virtual void __stdcall NotifyClock()
			{
				//同步时钟设置回调不知道有没有用暂时不实现
				
			}
			CMvHResult _SetSystemClockCallback()
			{
				CMvHResult		oHr = MV_E_FAIL;
				uint64_t	   ui64ClockStartTime;

				// Need frame event 
				SMvResolutionInfo sResolutionForFrame;

				sResolutionForFrame.size = sizeof(SMvResolutionInfo);
				//sResolutionForFrame = m_sResolution;
				sResolutionForFrame.eScanMode = keMvScanModeProgressive;

				ui64ClockStartTime = _GetNextClockTimeForCapture();
				//oHr = m_pJClock->RegisterForPeriodicNotification(ui64ClockStartTime, sResolutionForFrame,this);

				if (oHr.DidSucceed())
				{
					m_bSystemClockSet = true;
				}

				return oHr;
			}

			uint64_t _GetNextClockTimeForCapture()
			{
				uint64_t    ui64NanoTime, ui64SampleTime;

				// Get the current time 
				ui64NanoTime = m_pJClock->GetTime();
				ui64NanoTime = MvGetNextSampleNanoTime(ui64NanoTime, m_Out_Resolution);

				ui64SampleTime = MvGetSampleForNanoTime(ui64NanoTime, m_Out_Resolution);

				/*	if (ui64SampleTime <= m_ui64LastCaptureSampleTime)
					{
						ui64SampleTime = m_ui64LastCaptureSampleTime + 1;
					}

					m_ui64LastCaptureSampleTime = ui64SampleTime;*/

				// Return nanotime
				return MvGetNanoTimeForSample(ui64SampleTime, m_Out_Resolution);
			}
			int  _GetChannels()
			{
				return m_CardConfigs[m_need.card].vecpJSDIEAAudioInputConnectors.size();
			}

		};
			
		
		matrox_interface_producer::matrox_interface_producer(core::video_format format,int NeedAChannel,producer_need need)
			:impl_(new impl(format, NeedAChannel,need))
		{
		}
		
		bool matrox_interface_producer::get_frame(FrameforProducer & frame) {return impl_->get_frame(frame);}
		int  matrox_interface_producer::_GetChannels()
		{
			return impl_->_GetChannels();
		}
	}
}