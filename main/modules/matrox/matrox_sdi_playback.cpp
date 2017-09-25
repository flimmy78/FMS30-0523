#include "matrox_sdi_playback.h"

#include <MatroxDSXsdkGuids.h>
#include <MvFlexAPI.h>
#include <mvHelperFunctions.h>
#include "SfpSdiStatusCallback.h"
#include "ErrorNotificationCallback.h"
#include "MvErrorCallbackHandler.h"
#include <assert.h>

#include <assert.h>
#include <algorithm>

#include <boost/lexical_cast.hpp>
#include <tbb/atomic.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>

namespace caspar {
	namespace matrox {
///////////////////////////////////////////////////////
		matrox_sdi_playback::impl::impl(consumer_need need,core::video_format format, uint32_t channels, std::map<std::string, std::string>& ops)
			:CMvUnknown(L"ConsumerMvsNotificationCallback", NULL)
			,m_ui32WriteToReadDelayInFrame(4)
			,m_ui32DepthInFrame(12)
			,m_format_(format)
			,m_need_(need)
			,m_preset_channel_(channels)
			,args_options_(ops)
			,m_bOutput4K(false)
			,m_isplaying(false)
		{
                    
			CMvHResult oHr = MV_NOERROR;
			oHr = _SysConfiguration();
			if (oHr.DidFail())
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(mvErrorToString(oHr))
					<< boost::errinfo_api_function("in matrox_sdi_playback, _SysConfiguration"));
			}

			oHr = _BuildTopology();
			if (!oHr.DidSucceed())
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(mvErrorToString(oHr))
					<< boost::errinfo_api_function("in matrox_sdi_playback, _BuildTopology"));
			}
			bufferqueue.set_capacity(50);
		}
		
		matrox_sdi_playback::impl::~impl()
		{
		}

		CMvHResult matrox_sdi_playback::impl::Stop()
		{
			CMvHResult oHr = MV_NOERROR;
			oHr = m_pJHostNode->UnregisterWriteCallback(this);
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

		void matrox_sdi_playback::impl::Play()
		{
			CMvHResult oHr;
			oHr = m_pJHostNode->RegisterCallbackForWrite(this);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"matrox_sdi_playback::impl::Play Failure";
			}
		}

		void matrox_sdi_playback::impl::send(void *pvideo, void * pvideo1, void * paudio, void * paudio1)
		{
			if (_IsFieldBased())
			{
				FrameForConsumer frame;
				frame.pvideo.reset((uint8_t*)pvideo);
				frame.paudio.reset((uint8_t*)paudio);
				frame.IsTop = true;
				//bufferqueue.push(frame2022);
				if (!bufferqueue.try_push(frame))
					CASPAR_LOG(warning) << L"matrox_sdi_playback::impl::send try push top field failure!";
				frame.pvideo.reset((uint8_t*)pvideo1);
				frame.paudio.reset((uint8_t*)paudio1);
				frame.IsTop = false;
				//bufferqueue.push(frame2022);
				if (!bufferqueue.try_push(frame))
					CASPAR_LOG(warning) << L"matrox_sdi_playback::impl::send try push bottom field failure!";
			}
			else
			{
				FrameForConsumer frame;
				frame.pvideo.reset((uint8_t*)pvideo);
				frame.paudio.reset((uint8_t*)paudio);
				//bufferqueue.push(frame2022);
				if (!bufferqueue.try_push(frame))
					CASPAR_LOG(warning) << L"matrox_sdi_playback::impl::send try push frame failure!";
			}
			if (!m_isplaying)
			{
				m_isplaying = true;
				this->Play();
			}
		}

		HRESULT __stdcall matrox_sdi_playback::impl::NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters)
		{
			CMvHResult oHr = MV_NOERROR;
			FrameForConsumer data;
			if (!bufferqueue.try_pop(data))
			{
				//CASPAR_LOG(warning) << L"NotifyForBufferAccess bufferqueue no data";
				return oHr;
			}
			if (_IsFieldBased())
			{

				if (MvGetSampleForNanoTime(in_krsNotificationParameters.ui64Timestamp, m_Out_Resolution) % 2 == 1)//偶场
				{
					if (data.IsTop)
					{
						bufferqueue.pop(data);
						return oHr;
					}
				}
				else
				{
					if (!data.IsTop)
					{
						bufferqueue.pop(data);
						return oHr;
					}
				}
			}
// 			//按行拷贝，因为有场消隐的存在
// 			for (int y = 0; y < in_krsNotificationParameters.ui32VideoHeight; y++)
// 			{
// 				std::memcpy(in_krsNotificationParameters.pVideoBuffer + y*in_krsNotificationParameters.ui32AncRowPitchInBytes,
// 					data.pvideo.get() + y*in_krsNotificationParameters.ui32Width*in_krsNotificationParameters.ui32AncHeight * 2,
// 					in_krsNotificationParameters.ui32Width*in_krsNotificationParameters.ui32AncHeight * 2);
// 			}
			//video
			std::memcpy(in_krsNotificationParameters.pVideoBuffer, data.pvideo.get(), in_krsNotificationParameters.ui32Width * in_krsNotificationParameters.ui32VideoHeight * 2 /*4*/);
			//audio
			std::memcpy(in_krsNotificationParameters.pAudioBuffer, data.paudio.get(), in_krsNotificationParameters.ui32AudioSize);
			return MV_NOERROR;
		}

		CMvHResult matrox_sdi_playback::impl::_SysConfiguration()
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

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback, CoCreateInstance Failure : " << mvErrorToString(oHr);
				return oHr;
			}

			//获取板卡信息
			oHr = _EnumerateCards();
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback, _EnumerateCards Failure : " << mvErrorToString(oHr);
				return oHr;
			}
			if (m_CardConfigs.size() < m_need_.card + 1)
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback, card count less than deviceIndex";
				return MV_E_INVALID_PARAMETER;
			}
			//检测输出通道数量
			if (m_Out_Resolution.ulWidth >= 3840)
			{
				m_bOutput4K = true;//4k需要4个输出
			}
			if (m_bOutput4K)
			{
				if (m_CardConfigs[m_need_.card].vecpJSdiVideoOutputConnectors.size() == 0 ||
					m_CardConfigs[m_need_.card].vecpJSdiVideoOutputConnectors.size() < (m_need_.sdi + 4))
				{
					CASPAR_LOG(error) << L"in matrox_sdi_playback,the number of output connectors must be more than or equal the specified connector index + 4";
					return MV_E_INVALID_PARAMETER;
				}
			}
			else
			{
				if (m_CardConfigs[m_need_.card].vecpJSdiVideoOutputConnectors.size() == 0 ||
					m_CardConfigs[m_need_.card].vecpJSdiVideoOutputConnectors.size() < (m_need_.sdi + 1))
				{
					CASPAR_LOG(error) << L"in matrox_sdi_playback, the number of output connectors must be more than the specified connector index";
					return MV_E_INVALID_PARAMETER;
				}
			}

			return MV_NOERROR;
		}

		void matrox_sdi_playback::impl::_GetResolution(SMvResolutionInfo *out_pResInfo)
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
			case caspar::core::video_format::x1080p5000:
				szResolution = "1920x1080p@50";
				break;
			case caspar::core::video_format::x2160p2500:
				szResolution = "3840x2160p@25";//单路不支持
				break;
			case caspar::core::video_format::x2160p5000:
				szResolution = "3840x2160p@50";//单路不支持
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
						std::string szSubStr = szResolution.substr(0, posX); // Width
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
			CASPAR_LOG(error) << L"in matrox_sdi_playback, Unspecified or invalid resolution format";
		}

		CMvHResult matrox_sdi_playback::impl::_EnumerateCards()
		{
			CMvHResult oHr = MV_NOERROR;
			// Get the cards enumerator
			TMvSmartPtr<IMvSystemConfigurationCardEnumerator> pJEnum;
			oHr = m_IMvSystemConfiguration_->CreateCardEnumerator(&pJEnum);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback, _EnumerateCards CreateCardEnumerator Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			oHr.AssignNoAssert(pJEnum->Next(&pJCardConfig));
			while (oHr.DidSucceed())
			{
				SdiCardInfo	CardInfo;
				CardInfo.sHwInfo.size = sizeof(CardInfo.sHwInfo);
				CardInfo.pJCardConfig = pJCardConfig;
				CardInfo.sHwInfo.sConnectorsDescription.size = sizeof(CardInfo.sHwInfo.sConnectorsDescription);
				oHr = pJCardConfig->GetCardInformation(&CardInfo.sHwInfo, 0);

				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_sdi_playback, GetCardInformation Failure:" << mvErrorToString(oHr);
					return oHr;
				}

				oHr = _FillConnectors(CardInfo);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_sdi_playback, _FillConnectors Failure:" << mvErrorToString(oHr);
					return oHr;
				}

				m_CardConfigs.push_back(CardInfo);
				oHr = _ValidateAndDisplayCardTemperature(CardInfo);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_sdi_playback, _ValidateAndDisplayCardTemperature Failure:" << mvErrorToString(oHr);
					return oHr;
				}
				// Next card
				pJCardConfig = NULL;
				oHr.AssignNoAssert(pJEnum->Next(&pJCardConfig));
			}			
			return MV_NOERROR;
		}

		CMvHResult matrox_sdi_playback::impl::_FillConnectors(SdiCardInfo & io_rsCardInfo)
		{
			CMvHResult oHr;
			TMvSmartPtr<IMvSdiVideoOutputConnectorsEnumerator> pJEnumOutput;

			oHr = io_rsCardInfo.pJCardConfig->CreateSdiVideoOutputConnectorsEnumerator(&pJEnumOutput);

			if (oHr.DidSucceed())
			{
				TMvSmartPtr<IMvSdiVideoOutputConnector> pJOutputConnector;

				// Get first connector
				oHr.AssignNoAssert(pJEnumOutput->Next(&pJOutputConnector));

				while (oHr.DidSucceed())
				{
					io_rsCardInfo.vecpJSdiVideoOutputConnectors.push_back(pJOutputConnector);

					// Next card
					pJOutputConnector = NULL;
					oHr.AssignNoAssert(pJEnumOutput->Next(&pJOutputConnector));
				}

				// Ignore the error from the NEXT of the enumerator.
				oHr = MV_NOERROR;
			}
			return oHr;
		}

		CMvHResult matrox_sdi_playback::impl::_ValidateAndDisplayCardTemperature(SdiCardInfo & in_krsCardInfo)
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
						CASPAR_LOG(warning) << L"in matrox_sdi_playback,WARNING: OVERHEAT!";
						oHr = MV_E_FAIL;
					}

					if (asInfo[i].eFanStatus == keMvFanStatusTooSlowOrStopped)
					{
						CASPAR_LOG(warning) << L"in matrox_sdi_playback,Fan: ERROR: Too slow or stopped!";
						oHr = MV_E_FAIL;
					}
					else if (asInfo[i].eFanStatus == keMvFanStatusOk)
					{
						//printf("Fan: Ok.\n");
					}
					// else { there is no fan so no fan message to output. }
				}
			}
			return oHr;
		}

		CMvHResult matrox_sdi_playback::impl::_BuildTopology()
		{
			CMvHResult oHr = MV_NOERROR;
			oHr = _CleanTopology();
			if (oHr.DidFail())
			{
				return oHr;
			}

			oHr = _RetrieveGenlockClock();
			if (oHr.DidFail())
			{
				return oHr;
			}
			oHr = _SetupGenlock();
			if (oHr.DidFail())
			{
				return oHr;
			}

			oHr = _BuildMainTopology();
			if (oHr.DidFail())
			{
				return oHr;
			}
			return oHr;
		}
	
		CMvHResult matrox_sdi_playback::impl::_CleanTopology() 
		{
			CMvHResult oHr;
			//清除卡上的元素所有的默认状态并且永久内存，这个接口如果不是清除所有的拓扑的话应该不需要调用吧
			oHr = m_CardConfigs[m_need_.card].pJCardConfig->ClearDefaultsAndPermanentMemory();
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback, ClearDefaultsAndPermanentMemory Failure: " <<mvErrorToString(oHr);
				return oHr;
			}

			std::wstring strTopologyName = L"MatroxConsumer_"+ boost::lexical_cast<std::wstring>(m_need_.card) + L"_" + boost::lexical_cast<std::wstring>(m_need_.sdi);
			TMvSmartPtr<IMvTopologiesEnumerator>	pJTopologyEnumerator;
			oHr = m_CardConfigs[m_need_.card].pJCardConfig->CreateTopologiesEnumerator(&pJTopologyEnumerator);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,CreateTopologiesEnumerator";
				return oHr;
			}

			TMvSmartPtr<IMvTopology>				pJTopology;
			// Get the first topology
			oHr.AssignNoAssert(pJTopologyEnumerator->Next(&pJTopology));
			if (oHr.DidFail())
			{
				CASPAR_LOG(info) << L"No topology to destroy.";
				return MV_NOERROR;
			}

			while (oHr.DidSucceed())
			{
				char szTopologyName[128];
				oHr = pJTopology->GetName(szTopologyName, 128);
				if ((strcmp(u8(strTopologyName).c_str(), "") == 0 || strcmp(u8(strTopologyName).c_str(), szTopologyName) == 0))
				{
					oHr = pJTopology->AcquireControl();
					if (oHr.DidSucceed())
					{
						oHr = pJTopology->DestroyTopology();
						if (oHr.DidFail())
						{
							CASPAR_LOG(error) << L"in matrox_sdi_playback,DestroyTopology Failure:" <<mvErrorToString(oHr);
							return oHr;
						}
					}
					break;
				}
				pJTopology = NULL;
				oHr.AssignNoAssert(pJTopologyEnumerator->Next(&pJTopology));
			}
			return MV_NOERROR;
		}
		
		CMvHResult matrox_sdi_playback::impl::_RetrieveGenlockClock()
		{
			CMvHResult oHr;

			// Get the clock enumerator interface.
			TMvSmartPtr<IMvSystemClockEnumerator>	pJClockEnum;
			TMvSmartPtr<IMvSystemClock>				pJClock;
			oHr = m_CardConfigs[m_need_.card].pJCardConfig->CreateSystemClockEnumerator(&pJClockEnum);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,CreateSystemClockEnumerator Failure: " << mvErrorToString(oHr);
				return oHr;
			}

			// Enumerate all clocks in the system.
			while (pJClockEnum->Next(&pJClock) == MV_NOERROR)
			{
				// Search for a genlock clock
				if (pJClock->GetClockType() == keMvSystemClockTypeGenlock)
				{
					m_pJClock = pJClock;		// This is the genlock clock corresponding to the used card.
					break;
				}

				pJClock = NULL;  // Next clock
			}
			if (m_pJClock == NULL)
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,clock enum not find genlock";
				return MV_E_NOT_FOUND;
			}
			return MV_NOERROR;
		}

		CMvHResult matrox_sdi_playback::impl::_SetupGenlock()
		{
			CMvHResult oHr = MV_NOERROR;

			// Get genlock interface.         
			TMvSmartPtr<IMvGenlockConfiguration>	pJGenlockConfig;
			oHr = m_CardConfigs[m_need_.card].pJCardConfig->GetGenlockConfiguration(&pJGenlockConfig);

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,GetGenlockConfiguration Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			// Get current genlock settings
			SMvGenlockSettings sCurrentGenlockSettings = { sizeof(sCurrentGenlockSettings) };
			oHr = pJGenlockConfig->GetGenlockSettings(sCurrentGenlockSettings);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,GetGenlockSettings Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			SMvGenlockSettings sNewGenlockSettings = sCurrentGenlockSettings;	
			sNewGenlockSettings.sResolution = m_Out_Resolution;
			sNewGenlockSettings.eGenlockSource = keGenlockSourceInternal;//keGenlockSourceBlackBurst
			if (m_Out_Resolution.ulWidth > 1920)
			{
				// Bigger than HD resolution means UHD resolution. Since the card does not support genlock to these 
				// resolutions, use the HD equivalent.
				sNewGenlockSettings.sResolution.ulWidth = 1920;
				sNewGenlockSettings.sResolution.ulHeight = 1080;
			}
			oHr = pJGenlockConfig->SetGenlockSettings(sNewGenlockSettings);
			if (!oHr.DidSucceed())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,SetGenlockSettings";
				return oHr;
			}
			// Wait 2 seconds to be sure the hardware is stable enough to start playback.
			boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
			return MV_NOERROR;
		}

		
		CMvHResult matrox_sdi_playback::impl::_BuildMainTopology()
		{
			CMvHResult oHr;

			//Create the topology
			std::wstring strTopologyName = L"MatroxConsumer_" + boost::lexical_cast<std::wstring>(m_need_.card) + L"_" + boost::lexical_cast<std::wstring>(m_need_.sdi);
			oHr = m_IMvSystemConfiguration_->CreateSystemTopology(u8(strTopologyName).c_str(), m_pJClock, &m_pJSystemTopology);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,CreateSystemTopology Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			// Settings for the nodes
			SMvNodeSettings      sNodeSettings;
			SMvNodeSettingsVideo sVideoSettings;
			SMvNodeSettingsAudio sAudioSettings;
			SMvNodeSettingsVanc  sVancSettings;
			_InitNodeSettings(sNodeSettings, sVideoSettings, sAudioSettings, sVancSettings);

			//Create the card node
			std::wstring sname = L"OutNode" + boost::lexical_cast<std::wstring>((m_need_.sdi));
			strcpy_s(sNodeSettings.szName, _countof(sNodeSettings.szName), u8(sname).c_str());
			oHr = m_pJSystemTopology->CreateCardNode(sNodeSettings,
				&sVideoSettings,
				&sAudioSettings,
				&sVancSettings,
				NULL,//m_CardConfigs[m_need_.card].pJCardConfig,
				&m_pJIOCardNodeForPlayback);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,CreateCardNode Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			//Create the host node
			sname = L"HostNode" + boost::lexical_cast<std::wstring>((m_need_.sdi));
			strcpy_s(sNodeSettings.szName, _countof(sNodeSettings.szName), u8(sname).c_str());
			oHr = m_pJSystemTopology->CreateHostNode(sNodeSettings,
				&sVideoSettings,
				&sAudioSettings,
				&sVancSettings,
				&m_pJHostNode);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,CreateHostNode Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			//Create the transfer stream;
			SMvTransferStreamSettings sTransferSettings = { sizeof(sTransferSettings) };
			sTransferSettings.ui64AdvancedDelayInNanoTime = 0; // No need for advance delay here
			sname = L"Transfer" + boost::lexical_cast<std::wstring>((m_need_.sdi));
			oHr = m_pJSystemTopology->CreateTransferStream(u8(sname).c_str(),
				m_pJHostNode,
				m_pJIOCardNodeForPlayback,
				keMvTransferDirectionHostToCard,
				sTransferSettings,
				&m_pJTransferStream);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,CreateTransferStream Failure: " << mvErrorToString(oHr);
				return oHr;
			}
		

			// Create the output stream.
			SMvOutputStreamSettings sOutStreamSettings;
			_InitOutputStreamSettings(sOutStreamSettings);

			IMvVideoOutputConnector * apIOutputConnetor[4];
			uint32_t    connectors_count = 1;
			apIOutputConnetor[0] = m_CardConfigs[m_need_.card].vecpJSdiVideoOutputConnectors[m_need_.sdi];
			if (m_bOutput4K)
			{
				apIOutputConnetor[1] = m_CardConfigs[m_need_.card].vecpJSdiVideoOutputConnectors[m_need_.sdi+1];
				apIOutputConnetor[2] = m_CardConfigs[m_need_.card].vecpJSdiVideoOutputConnectors[m_need_.sdi+2];
				apIOutputConnetor[3] = m_CardConfigs[m_need_.card].vecpJSdiVideoOutputConnectors[m_need_.sdi+3];
				connectors_count = 4;
			}
			sname = L"Output" + boost::lexical_cast<std::wstring>((m_need_.sdi));
			oHr = m_pJSystemTopology->CreateOutputStream(u8(sname).c_str(),
				m_pJIOCardNodeForPlayback,
				m_Out_Resolution,
				sOutStreamSettings,
				apIOutputConnetor,
				connectors_count,
				&m_pJSdiOutputStream);

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_playback,CreateOutputStream Failure: " << mvErrorToString(oHr);
				return oHr;
			}

			return oHr;
		}
	

		void matrox_sdi_playback::impl::_InitNodeSettings(SMvNodeSettings  &out_sNodeSettings,
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
			if (m_need_.vanc)
			{
				out_sNodeSettings.eNodeContent = (EMvNodeContent)(out_sNodeSettings.eNodeContent | keMvNodeContentVanc);
			}

			out_sNodeSettingsVideo.ui32Size = sizeof(SMvNodeSettingsVideo);
			memcpy(&out_sNodeSettingsVideo.sResInfo, &m_Out_Resolution, sizeof(m_Out_Resolution));
			out_sNodeSettingsVideo.eColorimetry = NMvHelper::GetColorimetryFromResolution(m_Out_Resolution);
			out_sNodeSettingsVideo.eSurfaceFormat = keMvSurfaceFormatYUYV422; 

			out_sNodeSettingsAudio.ui32Size = sizeof(SMvNodeSettingsAudio);
			out_sNodeSettingsAudio.eDataType = keAudioDataTypePCM;
			out_sNodeSettingsAudio.ui32BitsPerSample = 32;
			out_sNodeSettingsAudio.ui32ValidBitsPerSample = 24;
			switch (m_preset_channel_)
			{
			case 1:
				out_sNodeSettingsAudio.eChannelType = keChannelTypeMono;
				break;
			case 2:
				out_sNodeSettingsAudio.eChannelType = keChannelTypeStereo;
				break;
			case 4:
				out_sNodeSettingsAudio.eChannelType = keChannelType4Tracks;
				break;
			case 6:
				out_sNodeSettingsAudio.eChannelType = keChannelType6Tracks;
				break;
			case 8:
				out_sNodeSettingsAudio.eChannelType = keChannelType8Tracks;
				break;
			case 10:
				out_sNodeSettingsAudio.eChannelType = keChannelType10Tracks;
				break;
			case 12:
				out_sNodeSettingsAudio.eChannelType = keChannelType12Tracks;
				break;
			case 14:
				out_sNodeSettingsAudio.eChannelType = keChannelType14Tracks;
				break;
			case 16:
				out_sNodeSettingsAudio.eChannelType = keChannelType16Tracks;
				break;
			case 32:
				out_sNodeSettingsAudio.eChannelType = keChannelType32Tracks;
				break;
			default:
				out_sNodeSettingsAudio.eChannelType = keChannelTypeStereo;
				break;
			}

			out_sNodeSettingsVanc.eVancFormat = keMvSurfaceFormatMatroxAncillaryData;
			out_sNodeSettingsVanc.ui32ComponentBitCount = 16;

		}

		void matrox_sdi_playback::impl::_InitOutputStreamSettings(SMvOutputStreamSettings & out_rsStreamSettings)
		{
			out_rsStreamSettings.ui32Size = sizeof(out_rsStreamSettings);
			out_rsStreamSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
			out_rsStreamSettings.aeVideoConnectorPosition[1] = keMvQuadrantTopRight;
			out_rsStreamSettings.aeVideoConnectorPosition[2] = keMvQuadrantBottomLeft;
			out_rsStreamSettings.aeVideoConnectorPosition[3] = keMvQuadrantBottomRight;
			out_rsStreamSettings.sVideoOutputStreamSettings.bAllowSuperBlack = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bAllowSuperWhite = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bDownscaleKeyLuma = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableChromaClipping = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableARGBChromaFiltering = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableEdgeSharpeningFilter = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableVideoMixer = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bInvertKeyLuma = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bApplyKeyLumaOffset = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bIsVideoShaped = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.eVideoMixerVancSource = keVideoMixerVancSourceNode;
			out_rsStreamSettings.sVideoOutputStreamSettings.eVideoMixerAudioAndHancSource = keVideoMixerAudioAndHancSourceMixerOrNode;
			out_rsStreamSettings.sVideoOutputStreamSettings.ui64AdvancedDelayInNanoTime = 0;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableMechanicalBypass = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.dVideoMixerNodeTransparency = 1.0;
			out_rsStreamSettings.sAudioOutputStreamSettings.bEnableAudioMixer = false;
			out_rsStreamSettings.sAudioOutputStreamSettings.bAuxPhaseInvert = false;
			out_rsStreamSettings.sAudioOutputStreamSettings.dAuxMasterVolume = 1.0;
			out_rsStreamSettings.sAudioOutputStreamSettings.dLineMasterVolume = 1.0;
			out_rsStreamSettings.sAudioOutputStreamSettings.eAuxSourceSelection = keMvAudioMixerSourceNode;

			for (uint32_t i = 0; i < _countof(out_rsStreamSettings.sAudioOutputStreamSettings.adAuxVolume); i++)
			{
				out_rsStreamSettings.sAudioOutputStreamSettings.adAuxVolume[i] = 1.0;
				out_rsStreamSettings.sAudioOutputStreamSettings.adLineVolume[i] = 1.0;
			}
		}


/////////////////////////////////////			
		matrox_sdi_playback::matrox_sdi_playback(consumer_need need, core::video_format format, int channels, std::map<std::string, std::string>& ops)
		:impl_(new impl(need, format, channels,ops))
		{
		}
		matrox_sdi_playback::~matrox_sdi_playback()
		{
			impl_->Stop();
			impl_ = NULL;
		}
		bool matrox_sdi_playback::_IsFieldBased()
		{
			return impl_->_IsFieldBased();
		}
		void matrox_sdi_playback::send(void *pvideo, void * pvideo1, void * paudio, void * paudio1)
		{
			return impl_->send(pvideo,pvideo1,paudio,paudio1);
		}
	}
}
