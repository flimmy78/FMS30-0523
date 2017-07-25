#include "matrox_2022_playback.h"

#include <MatroxDSXsdk.h>
#include <MatroxDSXsdkGuids.h>
#include <MvFlexAPI.h>
#include <mvHelperFunctions.h>
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
		struct SCardInfo
		{
			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			SMvGeneralHardwareInformation     sHwInfo;
			std::vector<TMvSmartPtr<IMvSfpIp> > vecpJSfpIp;
			std::vector<TMvSmartPtr<IMvSdiIpOutputConnector> > vecpJOutputConnectors;
		};
		
		struct matrox_2022_playback::impl : public CMvUnknown,  public IMvNodeNotificationCallback
		{
			MVDECLARE_IUNKNOWN
			//matrox  分辨率需要的参数
			SMvResolutionInfo								m_Out_Resolution;
			//COM的对象接口参数，记为系统对象
			TMvSmartPtr<IMvSystemConfiguration>				m_IMvSystemConfiguration_ = NULL;
			//锁相
			TMvSmartPtr<IMvSystemClock>						m_pJClock = NULL;
			//拓扑对象
			TMvSmartPtr<IMvSystemTopology>					m_pJSystemTopology = NULL;

			//node
			TMvSmartPtr<IMvNode>							m_pJIOCardNodeForPlayback = NULL;
			TMvSmartPtr<IMvHostNode>						m_pJHostNode = NULL;
			TMvSmartPtr<IMvTransferStream>					m_pJTransferStream = NULL;
			TMvSmartPtr<IMvOutputStream>					m_pJSdiIpOutputStream;
			//node 参数
			uint32_t										m_ui32WriteToReadDelayInFrame = 1;
			uint32_t										m_ui32WriteToReadDelayInFrameOutputNode = 0;
			uint32_t										m_ui32DepthInFrame = 12;

			//板卡参数集合接口
			std::vector<SCardInfo>							m_CardConfigs;
			
			//fms
			core::video_format								m_format_;


			//外来参数
			consumer_need									m_need_;
			int												m_preset_channel_;

			//给matrox准备的奇偶场
			tbb::concurrent_bounded_queue<SMvNodeNotificationCallbackParameters>	firstbufferqueue;
			tbb::concurrent_bounded_queue<SMvNodeNotificationCallbackParameters>	secondbufferqueue;
			tbb::concurrent_bounded_queue<Frame2022ForConsumer>	bufferqueue;

			impl(consumer_need need,core::video_format format,int channels)
				:CMvUnknown(L"ConsumerMvsNotificationCallback", NULL)
				,m_format_(format)
				,m_need_(need)
				, m_preset_channel_(channels)
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

				oHr = _CreateSystemTopology();
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, _CreateSystemTopology"));
				}
				firstbufferqueue.set_capacity(4);
				secondbufferqueue.set_capacity(4);
				bufferqueue.set_capacity(8);
			}
			
			CMvHResult _SysConfiguration()
			{
				//获取设定分辨率
				_GetResolution(&m_Out_Resolution);//

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
					if (m_IMvSystemConfiguration_ == NULL)
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
				if (m_CardConfigs.size() < m_need_.card + 1)
				{
					CASPAR_LOG(error) << L"in matrox_interface, card count less than deviceIndex";
					return MV_E_INVALID_PARAMETER;
				}
				//检测输入通道数量
				if (m_CardConfigs[m_need_.card].vecpJOutputConnectors.size() == 0 ||
					m_CardConfigs[m_need_.card].vecpJOutputConnectors.size() < (m_need_.sdi + 1))
				{
					CASPAR_LOG(error) << L"in matrox_interface,input connectors empty or less than connector index";
					return MV_E_INVALID_PARAMETER;
				}

				////获取视频源分辨率 不用获取这个参数
				//SMvSdiIpConnectorStatus  io_rsStatus;
				//oHr = m_CardConfigs[m_need_.card].vecpJInputConnectors[m_need_.sdi]->GetSdiIpConnectorStatus(io_rsStatus);
				//if (!oHr.DidSucceed())
				//{
				//	return oHr;
				//}
				//m_Out_Resolution = io_rsStatus.sDetectedResolution;
				return MV_NOERROR;
			}
			inline bool _IsFieldBased()
			{
				return m_Out_Resolution.eScanMode == keMvScanModeFirstFieldTop || m_Out_Resolution.eScanMode == keMvScanModeSecondFieldTop;
			}
			virtual HRESULT __stdcall NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters)
			{
				CMvHResult oHr = MV_NOERROR;
				Frame2022ForConsumer data;
				if (!bufferqueue.try_pop(data))
				{
					return oHr;
				}
				if (_IsFieldBased())
				{

					if (MvGetSampleForNanoTime(in_krsNotificationParameters.ui64Timestamp, m_Out_Resolution) % 2 == 1)//偶场
					{
						if (data.IsTop)//寄场数据，需要再扔掉一场
						{
							bufferqueue.pop(data);
							return oHr;
						}
					}
					else
					{
						if (!data.IsTop)//偶场数据，需要再扔掉一场
						{
							bufferqueue.pop(data);
							return oHr;
						}
					}
				}
				//按行拷贝，因为有场消隐的存在
				for (int y = 0;y<in_krsNotificationParameters.ui32VideoHeight;y++)
				{
					std::memcpy(in_krsNotificationParameters.pVideoBuffer+y*in_krsNotificationParameters.ui32AncRowPitchInBytes,
									data.pvideo.get()+y*in_krsNotificationParameters.ui32Width*in_krsNotificationParameters.ui32AncHeight * 2,
								in_krsNotificationParameters.ui32Width*in_krsNotificationParameters.ui32AncHeight*2);
				}
				//audio
				std::memcpy(in_krsNotificationParameters.pAudioBuffer, data.paudio.get(), in_krsNotificationParameters.ui32AudioSize);
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
							if (m_need_.ratio == L"16:9")
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
				if (pJEnum == nullptr)
				{
					CASPAR_LOG(error) << L"in matrox_interface, get cards pJEnum NULL";
					return MV_E_FAIL;
				}
				do {
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
					CardInfo.pJCardConfig = pJCardConfig;
					CardInfo.sHwInfo.sConnectorsDescription.size = sizeof(CardInfo.sHwInfo.sConnectorsDescription);

					oHr = pJCardConfig->GetCardInformation(&CardInfo.sHwInfo, 0);
					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox_interface, GetCardInformation";
						return oHr;
					}

					if (oHr.DidSucceed())
					{
						oHr = _FillSfps(CardInfo);
					}

					if (oHr.DidSucceed())
					{
						oHr = _FillConnectors(CardInfo);
					}
					m_CardConfigs.push_back(CardInfo);
					oHr = _ValidateAndDisplayCardTemperature(CardInfo);
					if (oHr.DidFail())
					{
						CoUninitialize();
						return -1;
					}
				} while (oHr.DidSucceed());
				return MV_NOERROR;
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
			//---------------------------------------------------------------------------------
			CMvHResult _FillSfps(SCardInfo & io_rsCardInfo)
			{
				CMvHResult oHr;

				//
				// Enumerate all Sfps
				//
				TMvSmartPtr<IMvSfpIpEnumerator> pJSfpIpEnum;

				oHr = io_rsCardInfo.pJCardConfig->CreateSfpIpEnumerator(&pJSfpIpEnum);

				if (oHr.DidSucceed())
				{
					TMvSmartPtr<IMvSfpIp> pJSfpIp;

					// Get first Sfp
					oHr.AssignNoAssert(pJSfpIpEnum->Next(&pJSfpIp));

					while (oHr.DidSucceed())
					{
						io_rsCardInfo.vecpJSfpIp.push_back(pJSfpIp);

						// Next card
						pJSfpIp = NULL;
						oHr.AssignNoAssert(pJSfpIpEnum->Next(&pJSfpIp));
					}

					// Ignore the error from the NEXT of the enumerator.
					oHr = MV_NOERROR;
				}

				return oHr;
			}
			// ----------------------------------------------------------------------------
			CMvHResult _FillConnectors(SCardInfo & io_rsCardInfo)
			{
				CMvHResult oHr;

				//
				// Enumerate Input connectors
				//
				TMvSmartPtr<IMvSdiIpOutputConnectorsEnumerator> pJEnumOutput;

				oHr = io_rsCardInfo.pJCardConfig->CreateSdiIpOutputConnectorsEnumerator(&pJEnumOutput);

				if (oHr.DidSucceed())
				{
					TMvSmartPtr<IMvSdiIpOutputConnector> pJOutputConnector;

					// Get first connector
					oHr.AssignNoAssert(pJEnumOutput->Next(&pJOutputConnector));

					while (oHr.DidSucceed())
					{
						io_rsCardInfo.vecpJOutputConnectors.push_back(pJOutputConnector);

						// Next card
						pJOutputConnector = NULL;
						oHr.AssignNoAssert(pJEnumOutput->Next(&pJOutputConnector));
					}

					// Ignore the error from the NEXT of the enumerator.
					oHr = MV_NOERROR;
				}
				return oHr;
			}
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


				//
				//清除卡上的元素所有的默认状态并且永久内存，这个接口如果不是清除所有的拓扑的话应该不需要调用吧
				oHr = m_CardConfigs[m_need_.card].pJCardConfig->ClearDefaultsAndPermanentMemory();

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback,ClearDefaultsAndPermanentMemory";
					return oHr;
				}

				TMvSmartPtr<IMvTopologiesEnumerator>	pJTopologyEnumerator = NULL;
				TMvSmartPtr<IMvTopology>				pJTopology = NULL;

				std::wstring strTopologyName = L"MatroxConsumer" + boost::lexical_cast<std::wstring>(m_need_.sdi);

				oHr = m_CardConfigs[m_need_.card].pJCardConfig->CreateTopologiesEnumerator(&pJTopologyEnumerator);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback,CreateTopologiesEnumerator";
					return oHr;
				}
				if (pJTopologyEnumerator == nullptr)
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback,pJTopologyEnumerator NULL";
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
							CASPAR_LOG(error) << L"in matrox_2022_playback,DestroyTopology";
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

				oHr = m_CardConfigs[m_need_.card].pJCardConfig->CreateSystemClockEnumerator(&pJClockEnum);

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

							if (m_CardConfigs[m_need_.card].pJCardConfig == pJTempCard)
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

				std::wstring strTopologyName = L"MatroxConsumer" + boost::lexical_cast<std::wstring>(m_need_.sdi);
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
				//这个回调暂时不用，检测光卡通道的
				TMvSmartPtr<IMvSfpIp> pJOutputSfpIp;
				m_CardConfigs[m_need_.card].vecpJOutputConnectors[m_need_.sdi]->GetAssociatedSfpIp(&pJOutputSfpIp);
				
				//先忽略这段
				//if (oHr.DidSucceed())
				//{
				//	// SDI IP Video Input notifications.
				//	m_pJSdiIpVideoInputStatusCallback = new CSdiIpVideoInputStatusCallback();

				//	m_pISdiIpInputConnector = in_pISdiIpInputConnector;
				//	oHr = m_pISdiIpInputConnector->RegisterVideoCallbackForNotification(m_pJSdiIpVideoInputStatusCallback);

				//	if (oHr.DidFail())
				//	{
				//		m_pJSdiIpVideoInputStatusCallback = NULL;
				//		printf("Error: Unable to register for SdiIp Video Input notification: %ls\n", mvErrorToString(oHr));
				//	}
				//}
				//if (oHr.DidSucceed())
				//{
				//	// SDI IP Audio Input notifications.
				//	m_pJSdiIpAudioInputStatusCallback = new CSdiIpAudioInputStatusCallback();

				//	oHr = m_pISdiIpInputConnector->RegisterAudioCallbackForNotification(m_pJSdiIpAudioInputStatusCallback);

				//	if (oHr.DidFail())
				//	{
				//		m_pJSdiIpAudioInputStatusCallback = NULL;
				//		printf("Error: Unable to register for SdiIp Audio Input notification: %ls\n", mvErrorToString(oHr));
				//	}
				//}




				// A/V Input node on IO
				SMvNodeSettings      sOutputNodeSettings;
				SMvNodeSettingsVideo sOutputVideoSettings;
				SMvNodeSettingsAudio sOutputAudioSettings;
				SMvNodeSettingsVanc  sOutputVancSettings;

				_SetInputNodeDefaultSettings(sOutputNodeSettings, sOutputVideoSettings, sOutputAudioSettings, sOutputVancSettings);
				switch (m_preset_channel_)
				{
				case 1:
					sOutputAudioSettings.eChannelType = keChannelTypeMono;
					break;
				case 2:
					sOutputAudioSettings.eChannelType = keChannelTypeStereo;
					break;
				case 4:
					sOutputAudioSettings.eChannelType = keChannelType4Tracks;
					break;
				case 6:
					sOutputAudioSettings.eChannelType = keChannelType6Tracks;
					break;
				case 8:
					sOutputAudioSettings.eChannelType = keChannelType8Tracks;
					break;
				case 10:
					sOutputAudioSettings.eChannelType = keChannelType10Tracks;
					break;
				case 12:
					sOutputAudioSettings.eChannelType = keChannelType12Tracks;
					break;
				case 14:
					sOutputAudioSettings.eChannelType = keChannelType14Tracks;
					break;
				case 16:
					sOutputAudioSettings.eChannelType = keChannelType16Tracks;
					break;
				case 32:
					sOutputAudioSettings.eChannelType = keChannelType32Tracks;
					break;
				default:
					break;
				}

				std::wstring sname = L"OutputCardNode" + boost::lexical_cast<std::wstring>((m_need_.sdi));
				sprintf_s(sOutputNodeSettings.szName, _countof(sOutputNodeSettings.szName), u8(sname).c_str());

				oHr = m_pJSystemTopology->CreateCardNode(sOutputNodeSettings,
					&sOutputVideoSettings,
					&sOutputAudioSettings,
					&sOutputVancSettings,
					m_CardConfigs[m_need_.card].pJCardConfig,
					&m_pJIOCardNodeForPlayback);

				// Output Stream 
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback,CreateCardNode";
					return oHr;
				}

				oHr = m_pJSystemTopology->CreateHostNode(sOutputNodeSettings,
					&sOutputVideoSettings,
					&sOutputAudioSettings,
					&sOutputVancSettings,
					&m_pJHostNode);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback,CreateCardNode";
					return oHr;
				}
				sname = L"MyTransfer" + boost::lexical_cast<std::wstring>((m_need_.sdi));
				if (oHr.DidSucceed())
				{
					SMvTransferStreamSettings sTransferSettings = { sizeof(sTransferSettings) };
					sTransferSettings.ui64AdvancedDelayInNanoTime = 0; // No need for advance delay here

					oHr = m_pJSystemTopology->CreateTransferStream(u8(sname).c_str(),
						m_pJIOCardNodeForPlayback,
						m_pJHostNode,
						keMvTransferDirectionCardToHost,
						sTransferSettings,
						&m_pJTransferStream);

					if (!oHr.DidSucceed())
					{
						CASPAR_LOG(error) << L"in matrox_interface,CreateCardNode";
						return oHr;
					}
				}

				// Create the output stream.
				if (oHr.DidSucceed())
				{
					SMvOutputStreamSettings sOutStreamSettings = { sizeof(sOutStreamSettings) };
					sOutStreamSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
					sOutStreamSettings.sVideoOutputStreamSettings.bAllowSuperBlack = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bAllowSuperWhite = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bDownscaleKeyLuma = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bEnableChromaClipping = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bEnableARGBChromaFiltering = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bEnableEdgeSharpeningFilter = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bEnableVideoMixer = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bInvertKeyLuma = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bApplyKeyLumaOffset = false;
					sOutStreamSettings.sVideoOutputStreamSettings.bIsVideoShaped = false;
					sOutStreamSettings.sVideoOutputStreamSettings.eVideoMixerVancSource = keVideoMixerVancSourceNode;
					sOutStreamSettings.sVideoOutputStreamSettings.eVideoMixerAudioAndHancSource = keVideoMixerAudioAndHancSourceMixerOrNode;
					sOutStreamSettings.sVideoOutputStreamSettings.ui64AdvancedDelayInNanoTime = 0;
					sOutStreamSettings.sVideoOutputStreamSettings.bEnableMechanicalBypass = false;
					sOutStreamSettings.sVideoOutputStreamSettings.dVideoMixerNodeTransparency = 1.0;
					sOutStreamSettings.sAudioOutputStreamSettings.bEnableAudioMixer = false;
					sOutStreamSettings.sAudioOutputStreamSettings.bAuxPhaseInvert = false;
					sOutStreamSettings.sAudioOutputStreamSettings.dAuxMasterVolume = 1.0;
					sOutStreamSettings.sAudioOutputStreamSettings.dLineMasterVolume = 1.0;
					sOutStreamSettings.sAudioOutputStreamSettings.eAuxSourceSelection = keMvAudioMixerSourceNode;

					for (uint32_t i = 0; i < _countof(sOutStreamSettings.sAudioOutputStreamSettings.adAuxVolume); i++)
					{
						sOutStreamSettings.sAudioOutputStreamSettings.adAuxVolume[i] = 1.0;
						sOutStreamSettings.sAudioOutputStreamSettings.adLineVolume[i] = 1.0;
					}
				

					IMvSdiIpOutputConnector * apIVideoConnetor[1] = { m_CardConfigs[m_need_.card].vecpJOutputConnectors[m_need_.sdi] };
					sname = L"MyOutput" + boost::lexical_cast<std::wstring>((m_need_.sdi));
					if (oHr.DidSucceed())
					{
						oHr = m_pJSystemTopology->CreateOutputStreamSdiIp(u8(sname).c_str(),
							m_pJIOCardNodeForPlayback,
							m_Out_Resolution,
							sOutStreamSettings,
							(IMvConnector**)apIVideoConnetor,
							NULL,
							1,
							&m_pJSdiIpOutputStream);

						if (oHr.DidFail())
						{
							printf("Error: Unable to create output stream: %ls\n", mvErrorToString(oHr));
						}
					}
				}
			
				// Control Sfp IP settings.
				if (oHr.DidSucceed())
				{
					SMvSfpIpSettings sSettings = { sizeof(sSettings) };
					oHr = pJOutputSfpIp->GetSettings(sSettings);
					if (oHr.DidFail())
					{
						printf("Error: Unable to Get Sfp IP Settings: %ls\n", mvErrorToString(oHr));
					}

					if (oHr.DidSucceed())
					{
						unsigned int ipint;
						GetIpAddress(m_need_.localhost, ipint);
						sSettings.ui32IPv4Address = ipint;

						oHr = pJOutputSfpIp->SetSettings(sSettings);
						if (oHr.DidFail())
						{
							printf("Error: Unable to Set Sfp IP Settings: %ls\n", mvErrorToString(oHr));
						}
					}

				}

				// Control SDI IP settings.

				if (oHr.DidSucceed())
				{
					// Control input connector settings.
					SMvSdiIpOutputConnectorSettings sConnectorSettings = { sizeof(sConnectorSettings) };
					oHr = m_CardConfigs[m_need_.card].vecpJOutputConnectors[m_need_.sdi]->GetConnectorSettings(sConnectorSettings);
					if (oHr.DidFail())
					{
						CASPAR_LOG(error)<<L"Error: Unable to Get Input SDI IP connector Settings:"<<mvErrorToString(oHr);
					}

					if (oHr.DidSucceed())
					{
						sConnectorSettings.ui16LocalUDPPort = m_need_.port;
						unsigned int adipv4;
						GetIpAddress(m_need_.addr, adipv4);
						sConnectorSettings.ui16DistantUDPport = (unsigned short)adipv4;
						sConnectorSettings.ui32DistantIPv4Address = m_need_.port;

						oHr = m_CardConfigs[m_need_.card].vecpJOutputConnectors[m_need_.sdi]->SetConnectorSettings(sConnectorSettings);
						if (oHr.DidFail())
						{
							CASPAR_LOG(error) << L"Error: Unable to Set Input SDI IP connector Settings: "<< mvErrorToString(oHr);
						}
					}
				}
				oHr = m_pJHostNode->RegisterCallbackForRead(this);

				return oHr;
			}
			//检测声音输入的通道数量，应该在初始化的时候做这个步骤
			CMvHResult GetAudioInputConnectors(IMvSdiIpInputConnector             * in_pISdiIpVideoInputConnector,
				IMvSdiIpAudioInputPairConnector   ** out_apIAudioInputConnectors,
				uint32_t                           & io_rui32Count)
			{
				CMvHResult oHr;
				uint32_t   ui32AudioConnectorCount = 0;
				IMvSdiIpAudioInputPairConnector * pISdiAudioInputPairConnector;

				TMvSmartPtr<IMvSdiIpAudioInputPairConnectorsEnumerator> pJEnumerator;
				oHr = in_pISdiIpVideoInputConnector->CreateAudioConnectorsEnumerator(&pJEnumerator);

				while (pJEnumerator->Next(&pISdiAudioInputPairConnector) == MV_NOERROR && ui32AudioConnectorCount < io_rui32Count)
				{
					out_apIAudioInputConnectors[ui32AudioConnectorCount] = pISdiAudioInputPairConnector;
					ui32AudioConnectorCount++;
				}

				io_rui32Count = ui32AudioConnectorCount;

				return oHr;
			}
			bool GetIpAddress(std::wstring addr,uint32_t & out_rui32Ipv4)
			{
				bool bFoundParam = false;
				bool bFoundValidAddress = true;
				std::string strAddress = u8(addr);

				if (!strAddress.empty())
				{
					// Format is 999.999.999.999:99999
					bFoundParam = true;

					// Search for the first "."
					size_t posOne = strAddress.find('.');
					std::string strOne;

					if (posOne != std::string::npos)
					{
						strOne = strAddress.substr(0, posOne);
					}
					else
					{
						printf("Bad format of IP address. Cannot find first number.\n");
						bFoundValidAddress = false;
					}

					// Search for the second "."
					size_t posTwo = strAddress.find('.', posOne + 1);
					std::string strTwo;
					if (bFoundValidAddress)
					{
						if (posTwo != std::string::npos)
						{
							strTwo = strAddress.substr(posOne + 1, posTwo - posOne - 1);
						}
						else
						{
							printf("Bad format of IP address. Cannot find second number.\n");
							bFoundValidAddress = false;
						}
					}

					// Search for the third "."
					size_t posThree = strAddress.find('.', posTwo + 1);
					std::string strThree;
					if (bFoundValidAddress)
					{
						if (posThree != std::string::npos)
						{
							strThree = strAddress.substr(posTwo + 1, posThree - posTwo - 1);
						}
						else
						{
							printf("Bad format of IP address. Cannot find third number.\n");
							bFoundValidAddress = false;
						}
					}
					// Search for the ":"
					size_t posFour;
					std::string strFour;
					if (bFoundValidAddress)
					{
						strFour = strAddress.substr(posThree + 1);
					}
					// Make sure string are not empty
					if (bFoundValidAddress && (strOne.empty() || strTwo.empty() || strThree.empty() || strFour.empty()))
					{
						printf("Bad format of IP address. Cannot find numbers.\n");
						bFoundValidAddress = false;
					}

					// Make sure everything is only numbers
					if (
						bFoundValidAddress && (
						(strOne.find_first_not_of("0123456789") != std::string::npos) ||
							(strTwo.find_first_not_of("0123456789") != std::string::npos) ||
							(strThree.find_first_not_of("0123456789") != std::string::npos) ||
							(strFour.find_first_not_of("0123456789") != std::string::npos)
							)
						)
					{
						printf("Bad format of IP address. Found something else then digits\n");
						bFoundValidAddress = false;
					}

					// Convert to INT.
					if (bFoundValidAddress)
					{
						out_rui32Ipv4 = 12;

						unsigned u1 = atoi(strOne.c_str());
						unsigned u2 = atoi(strTwo.c_str());
						unsigned u3 = atoi(strThree.c_str());
						unsigned u4 = atoi(strFour.c_str());

						if (u1 > 255 || u2 > 255 || u3 > 255 || u4 > 255)
						{
							printf("Address number must be in the range [0..255].\n");
							bFoundValidAddress = false;
						}

						if (bFoundValidAddress)
						{
							out_rui32Ipv4 = (u1 << 24) | (u2 << 16) | (u3 << 8) | u4;
						}
					}
				}

				if (!bFoundValidAddress || !bFoundParam)
				{
					// Return "0" address if any problem found OR not parameter specified
					out_rui32Ipv4 = 0;
				}
				return bFoundParam;
			}
			CMvHResult _SetupGenlockResolution()
			{
				CMvHResult oHr = MV_NOERROR;

				// Get genlock interface.         
				TMvSmartPtr<IMvGenlockConfiguration>	pJGenlockConfig;

				oHr = m_CardConfigs[m_need_.card].pJCardConfig->GetGenlockConfiguration(&pJGenlockConfig);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback,GetGenlockConfiguration";
					return oHr;
				}

				// Get current genlock settings

				SMvGenlockSettings sCurrentGenlockSettings = { sizeof(sCurrentGenlockSettings) };
				oHr = pJGenlockConfig->GetGenlockSettings(sCurrentGenlockSettings);
				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback,GetGenlockSettings";
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
					CASPAR_LOG(error) << L"in matrox_2022_playback,SetGenlockSettings";
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

			CMvHResult _CleanUp()
			{
				CMvHResult oHr = MV_NOERROR;
				oHr = m_pJHostNode->UnregisterReadCallback(this);
				m_pJClock = NULL;
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
				m_pJSystemTopology = NULL;
				return MV_NOERROR;
			}

			void send(void *pvideo, void * pvideo1, void * paudio, void * paudio1)
			{
				if (_IsFieldBased())
				{
					Frame2022ForConsumer frame2022;
					frame2022.pvideo.reset((uint8_t*)pvideo);
					frame2022.paudio.reset((uint8_t*)paudio);
					bufferqueue.push(frame2022);
					frame2022.pvideo.reset((uint8_t*)pvideo1);
					frame2022.paudio.reset((uint8_t*)paudio1);
					bufferqueue.push(frame2022);
				}
				else
				{
					Frame2022ForConsumer frame2022;
					frame2022.pvideo.reset((uint8_t*)pvideo);
					frame2022.paudio.reset((uint8_t*)paudio);
					bufferqueue.push(frame2022);
				}
			}

			~impl() {

				CMvHResult oHr = _CleanUp();

				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(std::wstring(L"release matrox_interface error:") + mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, _CleanUp"));
				}
			}
		};
		matrox_2022_playback::matrox_2022_playback(consumer_need need,core::video_format format ,int channels)
			:impl_(new impl(need,format,channels))
		{

		}
		bool matrox_2022_playback::_IsFieldBased()
		{
			return impl_->_IsFieldBased();
		}
		void matrox_2022_playback::send(void *pvideo, void * pvideo1, void * paudio, void * paudio1)
		{
			return impl_->send(pvideo,pvideo1,paudio,paudio1);
		}
	}
}