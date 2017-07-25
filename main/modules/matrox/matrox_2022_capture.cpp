#pragma once
#include <MatroxDSXsdk.h>
#include <mvBaseInterface.h>
#include <mvHelperFunctions.h>

#include "matrox_2022_capture.h"
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
			std::vector<TMvSmartPtr<IMvSfpIp> > vecpJSfpIp;
			std::vector<TMvSmartPtr<IMvSdiIpInputConnector> >  vecpJInputConnectors;
		};
		
		struct matrox_2022_capture::impl : public CMvUnknown, public IMvSystemClockNotificationCallback, public IMvNodeNotificationCallback
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
			TMvSmartPtr<IMvHostNode>						m_pJHostNode=NULL;
			TMvSmartPtr<IMvTransferStream>					m_pJTransferStream=NULL;
			TMvSmartPtr<IMvInputStream>						m_pJSdiIpInputStream;
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
			tbb::concurrent_bounded_queue<SMvNodeNotificationCallbackParameters>	m_oOutputBuffersQueue;
			tbb::concurrent_bounded_queue<SMvNodeNotificationCallbackParameters>	BuffersQueue;
			tbb::cache_aligned_allocator<uint8_t>  cc_memory_pool;
			uint32_t ui32AudioConnectorCount = 0;
			IMvSdiIpAudioInputPairConnector * apIAudioInputConnectors[32] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
				NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
				NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

			/*	tbb::atomic<bool>								is_running_;
				boost::thread									thread_;*/
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
			
				/*oHr = m_CardConfigs[m_need.card].pJCardConfig->GetErrorNotification(&m_pJErrorNotification);
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
				}*/
				
				/*m_pJCardErrorCallback = new CErrorNotificationCallback;
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
				}*/
				

				// 6. register for system topology asynch error call back
					
				/*m_pJSystemTopologyErrorCallback = new CErrorNotificationCallback(m_Out_Resolution);
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
				}*/
			
				//这个暂时先不弄
				// 7. create events used
			/*	if (!m_hClockEvent)
				{
					m_hClockEvent = ::CreateEvent(NULL, false, false, NULL);
				}*/
				
				BuffersQueue.set_capacity(1);
				m_oOutputBuffersQueue.set_capacity(8);
			}
			~impl()
			{
				
				//m_IsRunning = false;
				CMvHResult oHr= _CleanUp();	
				
				if (!oHr.DidSucceed())
				{
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(std::wstring(L"release matrox_interface error:") + mvErrorToString(oHr))
						<< boost::errinfo_api_function("in matrox_interface, _CleanUp"));
				}
			}
			inline bool _IsFieldBased(SMvResolutionInfo &in_sResInfo)
			{
				return in_sResInfo.eScanMode == keMvScanModeFirstFieldTop || in_sResInfo.eScanMode == keMvScanModeSecondFieldTop;
			}
			virtual HRESULT __stdcall NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters)
			{
				CMvHResult oHr = MV_NOERROR;
				SMvNodeNotificationCallbackParameters topdata;
				if (_IsFieldBased(m_Out_Resolution))
				{

					if (MvGetSampleForNanoTime(in_krsNotificationParameters.ui64Timestamp, m_Out_Resolution) % 2 == 1)//偶场
					{
						//m_oCriticalSection.Wait();

						if (BuffersQueue.size() == 0)
						{
							return oHr;
						}
						BuffersQueue.pop(topdata);
						m_oOutputBuffersQueue.push(topdata);

						SMvNodeNotificationCallbackParameters lpt = in_krsNotificationParameters;

						lpt.pVideoBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
						lpt.pAudioBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32AudioSize);
						memcpy(lpt.pVideoBuffer, in_krsNotificationParameters.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
						memcpy(lpt.pAudioBuffer, in_krsNotificationParameters.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
						m_oOutputBuffersQueue.push(lpt);
						//m_oCriticalSection.Release();

					}
					else
					{
						topdata = in_krsNotificationParameters;

						topdata.pVideoBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
						topdata.pAudioBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32AudioSize);

						memcpy(topdata.pVideoBuffer, in_krsNotificationParameters.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
						memcpy(topdata.pAudioBuffer, in_krsNotificationParameters.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
						BuffersQueue.push(topdata);
					}
				}
				return MV_NOERROR;
			}
			//---------------------------------------------------------------------------------
			//   system init

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
				if (m_CardConfigs.size()<m_need.card+1)
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
				
				////获取视频源分辨率
				//SMvSdiIpConnectorStatus  io_rsStatus;
				//oHr=m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi]->GetSdiIpConnectorStatus(io_rsStatus);
				//if (!oHr.DidSucceed())
				//{
				//	return oHr;
				//}
				//m_Out_Resolution = io_rsStatus.sDetectedResolution;
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
				}while (oHr.DidSucceed());
				return MV_NOERROR;
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
				TMvSmartPtr<IMvSdiIpInputConnectorsEnumerator> pJEnumInput;

				oHr = io_rsCardInfo.pJCardConfig->CreateSdiIpInputConnectorsEnumerator(&pJEnumInput);

				if (oHr.DidSucceed())
				{
					TMvSmartPtr<IMvSdiIpInputConnector> pJInputConnector;

					// Get first connector
					oHr.AssignNoAssert(pJEnumInput->Next(&pJInputConnector));

					while (oHr.DidSucceed())
					{
						io_rsCardInfo.vecpJInputConnectors.push_back(pJInputConnector);

						// Next card
						pJInputConnector = NULL;
						oHr.AssignNoAssert(pJEnumInput->Next(&pJInputConnector));
					}

					// Ignore the error from the NEXT of the enumerator.
					oHr = MV_NOERROR;
				}
				return oHr;
			}
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

				oHr = m_CardConfigs[m_need.card].pJCardConfig->CreateSystemClockEnumerator(&pJClockEnum);

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

							if (m_CardConfigs[m_need.card].pJCardConfig == pJTempCard)
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
				/*TMvSmartPtr<IMvSfpIp> pJInputSfpIp;
				m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi]->GetAssociatedSfpIp(&pJInputSfpIp);*/
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
				case 4:
					sInputAudioSettings.eChannelType = keChannelType4Tracks;
					break;
				case 6:
					sInputAudioSettings.eChannelType = keChannelType6Tracks;
					break;
				case 8:
					sInputAudioSettings.eChannelType = keChannelType8Tracks;
					break;
				case 10:
					sInputAudioSettings.eChannelType = keChannelType10Tracks;
					break;
				case 12:
					sInputAudioSettings.eChannelType = keChannelType12Tracks;
					break;
				case 14:
					sInputAudioSettings.eChannelType = keChannelType14Tracks;
					break;
				case 16:
					sInputAudioSettings.eChannelType = keChannelType16Tracks;
					break;
				case 32:
					sInputAudioSettings.eChannelType = keChannelType32Tracks;
					break;
				default:
					break;
				}
				uint32_t ui32DestIp = 0;
				
				bool sd = GetIpAddress(ui32DestIp);

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

				oHr = m_pJSystemTopology->CreateHostNode(sInputNodeSettings,
					&sInputVideoSettings,
					&sInputAudioSettings,
					&sInputVancSettings,
					&m_pJHostNode);

				if (!oHr.DidSucceed())
				{
					CASPAR_LOG(error) << L"in matrox_interface,CreateCardNode";
					return oHr;
				}
				sname = L"MyTransfer" + boost::lexical_cast<std::wstring>((m_need.sdi));
				if (oHr.DidSucceed())
				{
					SMvTransferStreamSettings sTransferSettings = { sizeof(sTransferSettings) };
					sTransferSettings.ui64AdvancedDelayInNanoTime = 0; // No need for advance delay here

					oHr = m_pJSystemTopology->CreateTransferStream(u8(sname).c_str(),
						m_pJIOCardNodeForCapture,
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

				// Create IP Input stream
				if (oHr.DidSucceed())
				{
					SMvInputStreamSettings sInStreamSettings;

					sInStreamSettings.ui32Size = sizeof(sInStreamSettings);

					// If your card supports it, you should use keMvInputStreamModeAudioResamplerVideoTBC
					sInStreamSettings.eInputStreamMode = keMvInputStreamModeAudioVideoTBC;
					sInStreamSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
					sInStreamSettings.aeVideoConnectorPosition[1] = keMvQuadrantTopRight;
					sInStreamSettings.aeVideoConnectorPosition[2] = keMvQuadrantBottomLeft;
					sInStreamSettings.aeVideoConnectorPosition[3] = keMvQuadrantBottomRight;
					sInStreamSettings.sVideoInputStreamSettings.dBrightness = 0.0f;
					sInStreamSettings.sVideoInputStreamSettings.dLumaGain = 1.0f;
					sInStreamSettings.sVideoInputStreamSettings.dHue = 0.0f;
					sInStreamSettings.sVideoInputStreamSettings.dSaturation = 1.0f;
					sInStreamSettings.sVideoInputStreamSettings.bAllowSuperBlack = false;
					sInStreamSettings.sVideoInputStreamSettings.bAllowSuperWhite = false;
					sInStreamSettings.sVideoInputStreamSettings.bEnableChromaClipping = false;
					sInStreamSettings.sVideoInputStreamSettings.bUpscaleKeyLuma = false;
					sInStreamSettings.sVideoInputStreamSettings.bInvertKeyLuma = false;
					sInStreamSettings.sVideoInputStreamSettings.bApplyKeyLumaOffset = false;
					sInStreamSettings.sVideoInputStreamSettings.bForceOpaqueKey = false;

					for (uint32_t i = 0; i < 8; i++)
					{
						sInStreamSettings.sAudioInputStreamSettings.abCapturePairMute[i] = false;
					}

					IMvSdiIpInputConnector * apISdiIpInputConnetor[1] = { m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi] };

				
					ui32AudioConnectorCount = 32;
					oHr = GetAudioInputConnectors(m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi], apIAudioInputConnectors, ui32AudioConnectorCount);
					if (oHr.DidFail())
					{
						printf("Error: Unable to get audio input connectors: %ls\n", mvErrorToString(oHr));
					}
					CASPAR_LOG(info) << L"audio connector " << ui32AudioConnectorCount << L" current preset " << m_preset_channel_;
					
					sname = L"MyInput" + boost::lexical_cast<std::wstring>((m_need.sdi));
					if (oHr.DidSucceed())
					{
						oHr = m_pJSystemTopology->CreateInputStreamSdiIp(u8(sname).c_str(),
							(IMvConnector**)apISdiIpInputConnetor,
							NULL, // alpha
							1,
							(IMvConnector**)apIAudioInputConnectors,
							ui32AudioConnectorCount,
							m_pJIOCardNodeForCapture,
							m_Out_Resolution,
							sInStreamSettings,
							&m_pJSdiIpInputStream);

						if (oHr.DidFail())
						{
							printf("Error: Unable to create IP input stream: %ls\n", mvErrorToString(oHr));
						}
					}
				}
				if (oHr.DidSucceed())
				{
					// Control input connector settings.
					SMvSdiIpInputConnectorSettings sConnectorSettings = { sizeof(sConnectorSettings) };
					oHr = m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi]->GetConnectorSettings(sConnectorSettings);
					if (oHr.DidFail())
					{
						printf("Error: Unable to Get Input SDI IP connector Settings: %ls\n", mvErrorToString(oHr));
					}

					if (oHr.DidSucceed())
					{
						sConnectorSettings.ui32MulticastFilterIPv4Address = ui32DestIp;
						sConnectorSettings.ui16LocalUDPPort = m_need.port;
						sConnectorSettings.ui16DistantUDPport = 0; //Don't care since Multicast
						sConnectorSettings.ui32DistantIPv4Address = 0; //Don't care since Multicast

						oHr = m_CardConfigs[m_need.card].vecpJInputConnectors[m_need.sdi]->SetConnectorSettings(sConnectorSettings);
						if (oHr.DidFail())
						{
							printf("Error: Unable to Set Input SDI IP connector Settings: %ls\n", mvErrorToString(oHr));
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
			bool GetIpAddress(uint32_t & out_rui32Ipv4)
			{
				bool bFoundParam = false;
				bool bFoundValidAddress = true;
				std::string strAddress =u8( m_need.addr);

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
					if	(
							bFoundValidAddress &&(
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

				oHr = m_CardConfigs[m_need.card].pJCardConfig->GetGenlockConfiguration(&pJGenlockConfig);
			
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
				if (!m_CardConfigs[m_need.card].pJCardConfig)
				{
					CASPAR_LOG(error) << L"in matrox_interface,m_CardConfigs[m_need.card].pJCardConfig is NULL";
					return MV_E_FAIL;
				}
				oHr = m_CardConfigs[m_need.card].pJCardConfig->QueryInterface(IID_IMvFlexEngine, (void**)&m_pJFlexEngine);
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
				oHr = m_pJHostNode->UnregisterReadCallback(this);
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
				SMvNodeNotificationCallbackParameters lpT;
				SMvNodeNotificationCallbackParameters lpB;
				if (_IsFieldBased(m_Out_Resolution))
				{
					//m_oCriticalSection.Wait();
					if (m_oOutputBuffersQueue.size() < 2)
					{
						//m_oCriticalSection.Release();
						return false;
					}
					m_oOutputBuffersQueue.pop(lpT);
					m_oOutputBuffersQueue.pop(lpB);
				}
				else
				{
					if (m_oOutputBuffersQueue.size() < 1)
					{
						return false;
					}
					m_oOutputBuffersQueue.pop(lpT);
				}

				if (_IsFieldBased(m_Out_Resolution))
				{

					uint8_t * p1 = (uint8_t *)lpT.pVideoBuffer;//寄场指针
					uint8_t *p2 = (uint8_t *)lpB.pVideoBuffer;//偶场指针
					if (m_Out_Resolution.ulWidth == 720 && (m_Out_Resolution.ulHeight == 288 * 2 || m_Out_Resolution.ulHeight == 243 * 2))
					{
						uint8_t* pdest = (uint8_t*)cc_memory_pool.allocate(720 * 2 * 576);
						frame.pvideo = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, 720 * 2 * 576); });

						/*tbb::parallel_for<size_t>(0, m_Out_Resolution.ulHeight, [&](size_t y)
						{
							if (y % 2)
							{

								fast_memcpy(frame.pvideo.get() + y * 720 * 2, p2 + (y / 2)*lpB.ui32VideoRowPitchInBytes, 720 * 2);
							}
							else
							{

								fast_memcpy(frame.pvideo.get() + y * 720 * 2, p1 + (y / 2)*lpT.ui32VideoRowPitchInBytes, 720 * 2);
							}
						});*/
						for (int y=0;y<m_Out_Resolution.ulHeight;y++)
						{
							if (y % 2)
							{

								memcpy(frame.pvideo.get() + y * 720 * 2, p2 + (y / 2)*lpB.ui32VideoRowPitchInBytes, 720 * 2);
							}
							else
							{

								memcpy(frame.pvideo.get() + y * 720 * 2, p1 + (y / 2)*lpT.ui32VideoRowPitchInBytes, 720 * 2);
							}
						}
					}
					else
					{
						uint8_t* pdest = (uint8_t*)cc_memory_pool.allocate(lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight * 2);
						frame.pvideo = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight * 2); });

						/*tbb::parallel_for<size_t>(0, lpT.ui32VideoHeight * 2, [&](size_t y)
						{
							if (y % 2)
							{
								fast_memcpy(frame.pvideo.get() + y * lpB.ui32VideoRowPitchInBytes, p2 + (y / 2)*lpB.ui32VideoRowPitchInBytes, lpB.ui32VideoRowPitchInBytes);
							}
							else
							{
								fast_memcpy(frame.pvideo.get() + y *  lpT.ui32VideoRowPitchInBytes, p1 + (y / 2)*lpT.ui32VideoRowPitchInBytes, lpT.ui32VideoRowPitchInBytes);
							}
						});*/
						for (int y = 0;y < m_Out_Resolution.ulHeight;y++)
						{
							if (y % 2)
							{
								memcpy(frame.pvideo.get() + y * lpB.ui32VideoRowPitchInBytes, p2 + (y / 2)*lpB.ui32VideoRowPitchInBytes, lpB.ui32VideoRowPitchInBytes);
							}
							else
							{
								memcpy(frame.pvideo.get() + y *  lpT.ui32VideoRowPitchInBytes, p1 + (y / 2)*lpT.ui32VideoRowPitchInBytes, lpT.ui32VideoRowPitchInBytes);
							}
						}
					}
					uint8_t* pdest = (uint8_t*)cc_memory_pool.allocate(lpT.ui32AudioSize * 2);
					frame.paudio = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32AudioSize * 2); });
					memcpy(frame.paudio.get(), lpT.pAudioBuffer, lpT.ui32AudioSize);
					memcpy(frame.paudio.get() + lpT.ui32AudioSize, lpB.pAudioBuffer, lpB.ui32AudioSize);
					frame.videolen = lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight * 2;
					frame.audiolen = lpT.ui32AudioSize * 2;
					frame.width = lpT.ui32Width == 768 ? 720 : lpT.ui32Width;
					frame.height = lpT.ui32VideoHeight * 2;
					frame.interlaced_frame = 1;
					frame.top_field_first = 1;
					frame.afd_aspect_ratio_ = -1;
					frame.afd_command_ = -1;

					switch (m_Out_Resolution.eFrameRate)
					{
					case keMvFrameRate25:
						frame.usample = (48000 / 25);
					case keMvFrameRate30:
						frame.usample = (48000 / 30);
					case keMvFrameRate50:
						frame.usample = (48000 / 50);
					case keMvFrameRate60:
						frame.usample = (48000 / 60);
					default:
						frame.usample = (48000 / 25);
						break;
					}
				}
				else
				{
					uint8_t* pdest = (uint8_t*)cc_memory_pool.allocate(lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight);
					frame.pvideo = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight); });

					pdest = (uint8_t*)cc_memory_pool.allocate(lpT.ui32AudioSize);
					frame.pvideo = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32AudioSize); });

					memcpy(frame.pvideo.get(), lpT.pVideoBuffer, lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight);
					memcpy(frame.paudio.get(), lpT.pAudioBuffer, lpT.ui32AudioSize);
					frame.videolen = lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight;
					frame.audiolen = lpT.ui32AudioSize;
					frame.width = lpT.ui32Width;
					frame.height = lpT.ui32VideoHeight;
					frame.interlaced_frame = 0;
					frame.top_field_first = 0;
					frame.afd_aspect_ratio_ = -1;
					frame.afd_command_ = -1;
					switch (m_Out_Resolution.eFrameRate)
					{
					case keMvFrameRate25:
						frame.usample = (48000 / 25);
					case keMvFrameRate30:
						frame.usample = (48000 / 30);
					case keMvFrameRate50:
						frame.usample = (48000 / 50);
					case keMvFrameRate60:
						frame.usample = (48000 / 60);
					default:
						frame.usample = (48000 / 25);
						break;
					}
				}
				if (lpT.pVideoBuffer)
					free(lpT.pVideoBuffer);
				if (lpT.pAudioBuffer)
					free(lpT.pAudioBuffer);
				if (lpB.pVideoBuffer)
					free(lpB.pVideoBuffer);
				if (lpB.pAudioBuffer)
					free(lpB.pAudioBuffer);
				return true;
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
				return ui32AudioConnectorCount;
			}

		};
			
		
		matrox_2022_capture::matrox_2022_capture(core::video_format format,int NeedAChannel,producer_need need)
			:impl_(new impl(format, NeedAChannel,need))
		{
		}
		
		bool matrox_2022_capture::get_frame(FrameforProducer & frame) {return impl_->get_frame(frame);}
		int  matrox_2022_capture::_GetChannels()
		{
			return impl_->_GetChannels();
		}
	}
}