#pragma once
#include <mvHelperFunctions.h>
#include "matrox_sdi_capture.h"
#include <boost/lexical_cast.hpp>
namespace caspar {
	namespace matrox {
		matrox_sdi_capture::impl::impl(core::video_format format,int NeedAChannel,producer_need need)
			:m_preset_channel_(NeedAChannel)
			,m_ui32WriteToReadDelayInFrame(4)
			,m_ui32DepthInFrame(12)
			,m_format_(format)
			,m_need(need)
			,m_ui32AudioConnectorCount(16)
			,m_bInput4K(false)
			,CMvUnknown(L"producerMvsNotificationCallback", NULL)
		{
			CMvHResult oHr = MV_NOERROR;
			oHr = _SysConfiguration();
			if (oHr.DidFail())
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(mvErrorToString(oHr))
					<< boost::errinfo_api_function("in matrox_sdi_capture, _SysConfiguration"));
			}

			oHr = _BuildTopology();
			if (oHr.DidFail())
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(mvErrorToString(oHr))
					<< boost::errinfo_api_function("in matrox_sdi_capture, _BuildTopology"));
			}
			
			BuffersQueue.set_capacity(1);
			m_oOutputBuffersQueue.set_capacity(8);
		}
		matrox_sdi_capture::impl::~impl()
		{
		}

		CMvHResult matrox_sdi_capture::impl::Stop()
		{
			CMvHResult oHr = MV_NOERROR;
			oHr = m_pJHostNode->UnregisterReadCallback(this);
			m_pJClock = NULL;

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

		bool matrox_sdi_capture::impl::get_frame(FrameforProducer& frame)
		{
			if (_IsFieldBased(m_in_Resolution))
			{
				return get_interlace_frame(frame);
			}
			else
			{
				return get_progressive_frame(frame);
			}
			return false;
		}

		int  matrox_sdi_capture::impl::_GetChannels()
		{
			return m_ui32AudioConnectorCount;
		}

		HRESULT __stdcall  matrox_sdi_capture::impl::NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters)
		{
			CMvHResult oHr = MV_NOERROR;
			if (_IsFieldBased(m_in_Resolution))//Field
			{
				SMvNodeNotificationCallbackParameters lpFirst;
				if (MvGetSampleForNanoTime(in_krsNotificationParameters.ui64Timestamp, m_in_Resolution) % 2 == 1)//偶场
				{
					if (BuffersQueue.size() == 0)
					{
						return oHr;
					}
					BuffersQueue.pop(lpFirst);
					m_oOutputBuffersQueue.push(lpFirst);

					SMvNodeNotificationCallbackParameters lpSecond = in_krsNotificationParameters;
					lpSecond.pVideoBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					lpSecond.pAudioBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32AudioSize);
					memcpy(lpSecond.pVideoBuffer, in_krsNotificationParameters.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					memcpy(lpSecond.pAudioBuffer, in_krsNotificationParameters.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
					m_oOutputBuffersQueue.push(lpSecond);
				}
				else
				{
					lpFirst = in_krsNotificationParameters;
					lpFirst.pVideoBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					lpFirst.pAudioBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32AudioSize);
					memcpy(lpFirst.pVideoBuffer, in_krsNotificationParameters.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					memcpy(lpFirst.pAudioBuffer, in_krsNotificationParameters.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
					BuffersQueue.push(lpFirst);
				}
			}
			else//progressive
			{
				SMvNodeNotificationCallbackParameters lpFrame;
				lpFrame = in_krsNotificationParameters;
				lpFrame.pVideoBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
				lpFrame.pAudioBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32AudioSize);
				memcpy(lpFrame.pVideoBuffer, in_krsNotificationParameters.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
				memcpy(lpFrame.pAudioBuffer, in_krsNotificationParameters.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
				m_oOutputBuffersQueue.push(lpFrame);
			}
			return MV_NOERROR;
		}

		CMvHResult matrox_sdi_capture::impl::_SysConfiguration()
		{
			//获取设定分辨率
			_GetResolution(&m_in_Resolution);//
			
			CMvHResult oHr;
			//获取matrox系统配置
			oHr = CoCreateInstance(CLSID_MvSystemConfiguration,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_IMvSystemConfiguration,
				(void**)&m_IMvSystemConfiguration_);

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture, CoCreateInstance Failure : " << mvErrorToString(oHr);
				return oHr;
			}

			//获取板卡信息
			oHr = _EnumerateCards();
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture, _EnumerateCards Failure : " << mvErrorToString(oHr);
				return oHr;
			}
			if (m_CardConfigs.size()<m_need.card+1)
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture, card count less than deviceIndex";
				return MV_E_INVALID_PARAMETER;
			}
 			//检测输入通道数量
			if (m_in_Resolution.ulWidth >= 3840)
			{
				m_bInput4K = true;//4k需要4个输入
			}
			if (m_bInput4K)
			{
				if (m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors.size() == 0 ||
					m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors.size() < (m_need.sdi + 4))
				{
					CASPAR_LOG(error) << L"in matrox_sdi_playback,the number of input connectors must be more than or equal the specified connector index + 4";
					return MV_E_INVALID_PARAMETER;
				}
			}
			else
			{
				if (m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors.size() == 0 ||
					m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors.size() < (m_need.sdi + 1))
				{
					CASPAR_LOG(error) << L"in matrox_sdi_playback, the number of input connectors must be more than the specified connector index";
					return MV_E_INVALID_PARAMETER;
				}
			}

			//检测视频和音频(4K-SDI不做检测)
			if (!m_bInput4K)
			{
				oHr = _AVCheck();
				if (oHr.DidFail())
				{
					return oHr;
				}			
			}

			return MV_NOERROR;
		}
				
		void matrox_sdi_capture::impl::_GetResolution(SMvResolutionInfo *in_pResInfo)
		{
			in_pResInfo->size = sizeof(*in_pResInfo);
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
					in_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
					in_pResInfo->eFrameRate = keMvFrameRate30M;
					in_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
					in_pResInfo->ulComponentBitCount = 8;
					in_pResInfo->ulWidth = 720;
					in_pResInfo->ulHeight = 486;
					return;
				}
				else if (m_format_ == core::video_format::pal)
				{
					in_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
					in_pResInfo->eFrameRate = keMvFrameRate25;
					in_pResInfo->eScanMode = keMvScanModeFirstFieldTop;
					in_pResInfo->ulComponentBitCount = 8;
					in_pResInfo->ulWidth = 720;
					in_pResInfo->ulHeight = 576;
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
						in_pResInfo->ulWidth = atoi(szSubStr.c_str());
						szSubStr = szResolution.substr(posX + 1, (posAt - 1) - (posX + 1)); // Height
						in_pResInfo->ulHeight = atoi(szSubStr.c_str());

						szSubStr = szResolution.substr(posAt - 1, 1); // i or p
						if (szSubStr == "i" || szSubStr == "I")
						{
							if (in_pResInfo->ulHeight == 486)
							{
								in_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
							}
							else
							{
								in_pResInfo->eScanMode = keMvScanModeFirstFieldTop;
							}
						}
						else if (szSubStr == "p" || szSubStr == "P")
						{
							in_pResInfo->eScanMode = keMvScanModeProgressive;
						}
						else
						{
							bSucceeded = false;
						}

						szSubStr = szResolution.substr(posAt + 1, std::string::npos);
						if (szSubStr == "24")
						{
							in_pResInfo->eFrameRate = keMvFrameRate24;
						}
						else if (szSubStr == "24M" || szSubStr == "23.98" || szSubStr == "24m")
						{
							in_pResInfo->eFrameRate = keMvFrameRate24M;
						}
						else if (szSubStr == "25")
						{
							in_pResInfo->eFrameRate = keMvFrameRate25;
						}
						else if (szSubStr == "30")
						{
							in_pResInfo->eFrameRate = keMvFrameRate30;
						}
						else if (szSubStr == "30M" || szSubStr == "29.97" || szSubStr == "30m")
						{
							in_pResInfo->eFrameRate = keMvFrameRate30M;
						}
						else if (szSubStr == "50")
						{
							in_pResInfo->eFrameRate = keMvFrameRate50;
						}
						else if (szSubStr == "60")
						{
							in_pResInfo->eFrameRate = keMvFrameRate60;
						}
						else if (szSubStr == "60M" || szSubStr == "59.94" || szSubStr == "60m")
						{
							in_pResInfo->eFrameRate = keMvFrameRate60M;
						}
						else
						{
							bSucceeded = false;
						}

						in_pResInfo->ulComponentBitCount = 8;
						in_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
						if (m_need.ratio == L"16:9")
						{
							in_pResInfo->eAspectRatio = keMvAspectRatio_16_9;
						}
						if (bSucceeded)
						{
							return;
						}
					}
				}
			}

			in_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
			in_pResInfo->eFrameRate = keMvFrameRate30M;
			in_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
			in_pResInfo->ulComponentBitCount = 8;
			in_pResInfo->ulWidth = 720;
			in_pResInfo->ulHeight = 486;
			CASPAR_LOG(error) << L"in matrox_sdi_capture, Unspecified or invalid resolution format";
		}
			
		CMvHResult matrox_sdi_capture::impl::_EnumerateCards()
		{
			CMvHResult oHr = MV_NOERROR;
			// Get the cards enumerator
			TMvSmartPtr<IMvSystemConfigurationCardEnumerator> pJEnum;
			oHr = m_IMvSystemConfiguration_->CreateCardEnumerator(&pJEnum);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture, _EnumerateCards CreateCardEnumerator Failure:" << mvErrorToString(oHr);
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
					CASPAR_LOG(error) << L"in matrox_sdi_capture, GetCardInformation Failure:" << mvErrorToString(oHr);
					return oHr;
				}

				oHr = _FillConnectors(CardInfo);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_sdi_capture, _FillConnectors Failure:" << mvErrorToString(oHr);
					return oHr;
				}

				m_CardConfigs.push_back(CardInfo);
				oHr = _ValidateAndDisplayCardTemperature(CardInfo);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_sdi_capture, _ValidateAndDisplayCardTemperature Failure:" << mvErrorToString(oHr);
					return oHr;
				}
				// Next card
				pJCardConfig = NULL;
				oHr.AssignNoAssert(pJEnum->Next(&pJCardConfig));
			}

			return MV_NOERROR;
		}

		CMvHResult matrox_sdi_capture::impl::_FillConnectors(SdiCardInfo & io_rsCardInfo)
		{
			CMvHResult oHr;

			//
			// Enumerate Input connectors
			//
			TMvSmartPtr<IMvSdiVideoInputConnectorsEnumerator> pJEnumInput;

			oHr = io_rsCardInfo.pJCardConfig->CreateSdiVideoInputConnectorsEnumerator(&pJEnumInput);

			if (oHr.DidSucceed())
			{
				TMvSmartPtr<IMvSdiVideoInputConnector> pJInputConnector;

				// Get first connector
				oHr.AssignNoAssert(pJEnumInput->Next(&pJInputConnector));

				while (oHr.DidSucceed())
				{
					io_rsCardInfo.vecpJSdiVideoInputConnectors.push_back(pJInputConnector);

					// Next card
					pJInputConnector = NULL;
					oHr.AssignNoAssert(pJEnumInput->Next(&pJInputConnector));
				}

				// Ignore the error from the NEXT of the enumerator.
				oHr = MV_NOERROR;
			}
			return oHr;
		}

		CMvHResult matrox_sdi_capture::impl::_ValidateAndDisplayCardTemperature(SdiCardInfo & in_krsCardInfo)
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
						CASPAR_LOG(warning) << L"in matrox_sdi_capture,WARNING: OVERHEAT!";
						oHr = MV_E_FAIL;
					}

					if (asInfo[i].eFanStatus == keMvFanStatusTooSlowOrStopped)
					{
						CASPAR_LOG(warning) << L"in matrox_sdi_capture,Fan: ERROR: Too slow or stopped!";
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

		CMvHResult matrox_sdi_capture::impl::_AVCheck()
		{
			//检测视频信号
			SMvVideoConnectorStatus io_rsVideoStatus;
			io_rsVideoStatus.ui32Size = sizeof(SMvVideoConnectorStatus);

			CMvHResult oHr = MV_NOERROR;
			oHr = m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors[m_need.sdi]->GetVideoConnectorStatus(io_rsVideoStatus);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture, GetVideoConnectorStatus Fail:" << mvErrorToString(oHr);
				return oHr;
			}
			if (m_in_Resolution.ulHeight != io_rsVideoStatus.sDetectedResolution.ulHeight || m_in_Resolution.ulWidth != io_rsVideoStatus.sDetectedResolution.ulWidth)
			{
				CASPAR_LOG(warning) << L"in matrox_sdi_capture, Specified Resolution is not matched with Source Resolution or source signal is not exist. ";
				return MV_E_INVALID_PARAMETER;
			}

			//检测音频信号
			SMvAudioPairStatus AudioPair[8];
			uint32_t in_ui32ArrayCount = 8;
			for (uint32_t i = 0; i < in_ui32ArrayCount; i++)
			{
				AudioPair[i].ui32Size = sizeof(SMvAudioPairStatus);
			}
			oHr = m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors[m_need.sdi]->GetSdiEmbeddedAudioInputPairConnectorsStatuses(AudioPair, in_ui32ArrayCount);
			if (!oHr.DidSucceed())
			{
				CASPAR_LOG(warning) << L"in matrox_sdi_capture,GetAudioInputPairConnectors Fail:" << mvErrorToString(oHr);
				return oHr;
			}
			int ChannelNums = 0;
			for (int i = 0; i < in_ui32ArrayCount; i++)
			{
				if (AudioPair[i].bIsPairPresent)
				{
					ChannelNums++;
				}
			}
			if (ChannelNums != m_preset_channel_)
			{
				CASPAR_LOG(warning) << L"in matrox_sdi_capture,specified audio channels is not matched with source.";
				return MV_E_INVALID_PARAMETER;
			}
			return MV_NOERROR;
		}

		CMvHResult matrox_sdi_capture::impl::_BuildTopology()
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

			oHr =_BuildMainTopology();
			if (!oHr.DidSucceed())
			{
				return oHr;
			}
			return oHr;
		}

		CMvHResult matrox_sdi_capture::impl::_CleanTopology()
		{
			CMvHResult oHr;
			//清除卡上的元素所有的默认状态并且永久内存，这个接口如果不是清除所有的拓扑的话应该不需要调用吧
			oHr = m_CardConfigs[m_need.card].pJCardConfig->ClearDefaultsAndPermanentMemory();
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture, ClearDefaultsAndPermanentMemory Failure: " << mvErrorToString(oHr);
				return oHr;
			}

			std::wstring strTopologyName = L"MatroxProducer_" + boost::lexical_cast<std::wstring>(m_need.card) + L"_" + boost::lexical_cast<std::wstring>(m_need.sdi);
			TMvSmartPtr<IMvTopologiesEnumerator>	pJTopologyEnumerator;
			oHr = m_CardConfigs[m_need.card].pJCardConfig->CreateTopologiesEnumerator(&pJTopologyEnumerator);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,CreateTopologiesEnumerator";
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
							CASPAR_LOG(error) << L"in matrox_sdi_capture,DestroyTopology Failure:" << mvErrorToString(oHr);
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

		CMvHResult matrox_sdi_capture::impl::_RetrieveGenlockClock()
		{
			CMvHResult oHr;

			// Get the clock enumerator interface.
			TMvSmartPtr<IMvSystemClockEnumerator>	pJClockEnum;
			TMvSmartPtr<IMvSystemClock>				pJClock;
			oHr = m_CardConfigs[m_need.card].pJCardConfig->CreateSystemClockEnumerator(&pJClockEnum);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,CreateSystemClockEnumerator Failure: " << mvErrorToString(oHr);
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
				CASPAR_LOG(error) << L"in matrox_sdi_capture,clock enum not find genlock";
				return MV_E_NOT_FOUND;
			}
			return MV_NOERROR;
		}
			
		CMvHResult matrox_sdi_capture::impl::_SetupGenlock()
		{
			CMvHResult oHr = MV_NOERROR;

			// Get genlock interface.         
			TMvSmartPtr<IMvGenlockConfiguration>	pJGenlockConfig;
			oHr = m_CardConfigs[m_need.card].pJCardConfig->GetGenlockConfiguration(&pJGenlockConfig);

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,GetGenlockConfiguration Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			// Get current genlock settings
			SMvGenlockSettings sCurrentGenlockSettings = { sizeof(sCurrentGenlockSettings) };
			oHr = pJGenlockConfig->GetGenlockSettings(sCurrentGenlockSettings);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,GetGenlockSettings Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			SMvGenlockSettings sNewGenlockSettings = sCurrentGenlockSettings;
			sNewGenlockSettings.sResolution = m_in_Resolution;
			sNewGenlockSettings.eGenlockSource = keGenlockSourceInternal;//keGenlockSourceBlackBurst
			if (m_in_Resolution.ulWidth > 1920)
			{
				// Bigger than HD resolution means UHD resolution. Since the card does not support genlock to these 
				// resolutions, use the HD equivalent.
				sNewGenlockSettings.sResolution.ulWidth = 1920;
				sNewGenlockSettings.sResolution.ulHeight = 1080;
			}
			oHr = pJGenlockConfig->SetGenlockSettings(sNewGenlockSettings);
			if (!oHr.DidSucceed())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,SetGenlockSettings";
				return oHr;
			}
			// Wait 2 seconds to be sure the hardware is stable enough to start playback.
			boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
			return MV_NOERROR;
		}

		CMvHResult matrox_sdi_capture::impl::_BuildMainTopology()
		{
			CMvHResult oHr;
			//Create the topology
			std::wstring strTopologyName = L"MatroxProducer_" + boost::lexical_cast<std::wstring>(m_need.card) + L"_" + boost::lexical_cast<std::wstring>(m_need.sdi);
			oHr = m_IMvSystemConfiguration_->CreateSystemTopology(u8(strTopologyName).c_str(), m_pJClock, &m_pJSystemTopology);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,CreateSystemTopology Failure:" << mvErrorToString(oHr);
				return oHr;
			}
				
			// Settings for the nodes
			SMvNodeSettings      sNodeSettings;
			SMvNodeSettingsVideo sVideoSettings;
			SMvNodeSettingsAudio sAudioSettings;
			_InitNodeSettings(sNodeSettings, sVideoSettings, sAudioSettings);

			//Create the card node
			std::wstring sname = L"CardNode" + boost::lexical_cast<std::wstring>((m_need.sdi));
			strcpy_s(sNodeSettings.szName, _countof(sNodeSettings.szName), u8(sname).c_str());				
			oHr = m_pJSystemTopology->CreateCardNode(sNodeSettings,
				&sVideoSettings,
				&sAudioSettings,
				NULL,
				NULL,//m_CardConfigs[m_need.card].pJCardConfig,
				&m_pJIOCardNodeForCapture);

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,CreateCardNode Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			//Create the host node
			sname = L"HostNode" + boost::lexical_cast<std::wstring>((m_need.sdi));
			strcpy_s(sNodeSettings.szName, _countof(sNodeSettings.szName), u8(sname).c_str());
			oHr = m_pJSystemTopology->CreateHostNode(sNodeSettings,
				&sVideoSettings,
				&sAudioSettings,
				NULL,
				&m_pJHostNode);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,CreateHostNode Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			//Create the transfer stream;
			SMvTransferStreamSettings sTransferSettings = { sizeof(sTransferSettings) };
			sTransferSettings.ui64AdvancedDelayInNanoTime = 0; // No need for advance delay here
			sname = L"Transfer" + boost::lexical_cast<std::wstring>((m_need.sdi));
			oHr = m_pJSystemTopology->CreateTransferStream(u8(sname).c_str(),
				m_pJIOCardNodeForCapture,
				m_pJHostNode,
				keMvTransferDirectionCardToHost,
				sTransferSettings,
				&m_pJTransferStream);

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_sdi_capture,CreateTransferStream Failure: " << mvErrorToString(oHr);
				return oHr;
			}

			// Create Input stream
			SMvInputStreamSettings sInStreamSettings;
			_InitInputStreamSettings(sInStreamSettings);

			oHr = _GetEmbeddedAudioInputConnectors(m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors[m_need.sdi], apIAudioInputConnectors, m_ui32AudioConnectorCount);
			if (oHr.DidFail())
			{
				CASPAR_LOG(info) << L"in matrox_sdi_capture, unable to get audio input connectors: " << mvErrorToString(oHr);
			}

			IMvVideoInputConnector * apISdiVideoInputConnetor[4];
			uint32_t    connectors_count = 1;
			apISdiVideoInputConnetor[0] = m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors[m_need.sdi];
			if (m_bInput4K)
			{
				apISdiVideoInputConnetor[1] = m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors[m_need.sdi + 1];
				apISdiVideoInputConnetor[2] = m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors[m_need.sdi + 2];
				apISdiVideoInputConnetor[3] = m_CardConfigs[m_need.card].vecpJSdiVideoInputConnectors[m_need.sdi + 3];
				connectors_count = 4;
			}
			sname = L"Input" + boost::lexical_cast<std::wstring>((m_need.sdi));
			oHr = m_pJSystemTopology->CreateInputStream(u8(sname).c_str(),
				apISdiVideoInputConnetor,
				connectors_count,
				apIAudioInputConnectors,
				m_ui32AudioConnectorCount,
				m_pJIOCardNodeForCapture,
				m_in_Resolution,
				sInStreamSettings,
				&m_pJSdiVideoInputStream);

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback,CreateInputStream Failure: " << mvErrorToString(oHr);
				return oHr;
			}
				
			oHr = m_pJHostNode->RegisterCallbackForRead(this);

			return oHr;
		}

		void matrox_sdi_capture::impl::_InitNodeSettings(SMvNodeSettings      &out_sNodeSettings,
			SMvNodeSettingsVideo &out_sNodeSettingsVideo,
			SMvNodeSettingsAudio &out_sNodeSettingsAudio)
		{
			// Create a node to attach to the output streams
			if (m_in_Resolution.eScanMode == keMvScanModeProgressive || m_in_Resolution.eScanMode == keMvScanModeProgressiveSegmented)
			{
				out_sNodeSettings.ui64WriteToReadDelayInNanoTime = MvGetNanoTimeForSample(m_ui32WriteToReadDelayInFrame * 1, m_in_Resolution);
			}
			else
			{
				out_sNodeSettings.ui64WriteToReadDelayInNanoTime = MvGetNanoTimeForSample(m_ui32WriteToReadDelayInFrame * 2, m_in_Resolution);
			}

			out_sNodeSettings.ui32Size = sizeof(SMvNodeSettings);
			out_sNodeSettings.ui32Depth = m_ui32DepthInFrame;
			out_sNodeSettings.eNodeContent = keMvNodeContentVideoAudio;

			out_sNodeSettingsVideo.ui32Size = sizeof(SMvNodeSettingsVideo);
			memcpy(&out_sNodeSettingsVideo.sResInfo, &m_in_Resolution, sizeof(m_in_Resolution));
			out_sNodeSettingsVideo.eColorimetry = NMvHelper::GetColorimetryFromResolution(m_in_Resolution);
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
		}

		void matrox_sdi_capture::impl::_InitInputStreamSettings(SMvInputStreamSettings& sInStreamSettings)
		{
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
		}

		HRESULT matrox_sdi_capture::impl::_GetEmbeddedAudioInputConnectors(IMvSdiVideoInputConnector * in_pISdivideoInputConnector,
			IMvAudioInputConnector   ** out_apIAudioInputConnectors,
			uint32_t                  & io_rui32Count)
		{
			CMvHResult oHr;
			uint32_t   ui32AudioConnectorCount = 0;
			IMvSdiEmbeddedAudioInputPairConnector * pISdiEmbeddedAudioInputConnector;

			TMvSmartPtr<IMvSdiEmbeddedAudioInputPairConnectorsEnumerator> pJEnumerator;
			oHr = in_pISdivideoInputConnector->CreateSdiEmbeddedAudioInputPairConnectorsEnumerator(&pJEnumerator);

			while (pJEnumerator->Next(&pISdiEmbeddedAudioInputConnector) == MV_NOERROR && ui32AudioConnectorCount < io_rui32Count)
			{
				out_apIAudioInputConnectors[ui32AudioConnectorCount] = pISdiEmbeddedAudioInputConnector;
				ui32AudioConnectorCount++;
			}

			io_rui32Count = ui32AudioConnectorCount;

			return oHr;
		}

		bool matrox_sdi_capture::impl::get_interlace_frame(FrameforProducer& frame)
		{
			SMvNodeNotificationCallbackParameters lpT;
			SMvNodeNotificationCallbackParameters lpB;
			if (m_oOutputBuffersQueue.size() < 2)
			{
				return false;
			}
			m_oOutputBuffersQueue.pop(lpT);
			m_oOutputBuffersQueue.pop(lpB);

			uint8_t *pTop = (uint8_t*)lpT.pVideoBuffer;
			uint8_t *pBottom = (uint8_t*)lpB.pVideoBuffer;
			uint8_t *pVideo = (uint8_t*)cc_memory_pool.allocate(lpT.ui32VideoRowPitchInBytes * lpT.ui32VideoHeight * 2);
			frame.pvideo = std::shared_ptr<uint8_t>(pVideo, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32VideoRowPitchInBytes * lpT.ui32VideoHeight * 2); });
			for (int y = 0; y<m_in_Resolution.ulHeight; y++)
			{
				if (y % 2)
				{
					memcpy(frame.pvideo.get() + y * lpB.ui32VideoRowPitchInBytes, pBottom + (y / 2)*lpB.ui32VideoRowPitchInBytes, lpB.ui32VideoRowPitchInBytes);
				}
				else
				{
					memcpy(frame.pvideo.get() + y * lpT.ui32VideoRowPitchInBytes, pTop + (y / 2)*lpT.ui32VideoRowPitchInBytes, lpT.ui32VideoRowPitchInBytes);
				}
			}
			uint8_t* pAudio = (uint8_t*)cc_memory_pool.allocate(lpT.ui32AudioSize * 2);
			frame.paudio = std::shared_ptr<uint8_t>(pAudio, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32AudioSize * 2); });

			memcpy(frame.paudio.get(), lpT.pAudioBuffer, lpT.ui32AudioSize);
			memcpy(frame.paudio.get() + lpT.ui32AudioSize, lpB.pAudioBuffer, lpB.ui32AudioSize);

			frame.videolen = lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight * 2;
			frame.audiolen = lpT.ui32AudioSize * 2;
			frame.width = lpT.ui32Width;
			frame.height = lpT.ui32VideoHeight * 2;
			frame.interlaced_frame = 1;
			frame.top_field_first = 1;
			frame.afd_aspect_ratio_ = -1;
			frame.afd_command_ = -1;

			switch (m_in_Resolution.eFrameRate)
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

		bool matrox_sdi_capture::impl::get_progressive_frame(FrameforProducer& frame)
		{
			SMvNodeNotificationCallbackParameters lpFrame;
			if (m_oOutputBuffersQueue.size() < 1)
			{
				return false;
			}
			m_oOutputBuffersQueue.pop(lpFrame);
			uint8_t* pVideo = (uint8_t*)cc_memory_pool.allocate(lpFrame.ui32VideoRowPitchInBytes*lpFrame.ui32VideoHeight);
			frame.pvideo = std::shared_ptr<uint8_t>(pVideo, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpFrame.ui32VideoRowPitchInBytes*lpFrame.ui32VideoHeight); });
			uint8_t* pAudio = (uint8_t*)cc_memory_pool.allocate(lpFrame.ui32AudioSize);
			frame.paudio = std::shared_ptr<uint8_t>(pAudio, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpFrame.ui32AudioSize); });

			memcpy(frame.pvideo.get(), lpFrame.pVideoBuffer, lpFrame.ui32VideoRowPitchInBytes*lpFrame.ui32VideoHeight);
			memcpy(frame.paudio.get(), lpFrame.pAudioBuffer, lpFrame.ui32AudioSize);
			frame.videolen = lpFrame.ui32VideoRowPitchInBytes*lpFrame.ui32VideoHeight;
			frame.audiolen = lpFrame.ui32AudioSize;
			frame.width = lpFrame.ui32Width;
			frame.height = lpFrame.ui32VideoHeight;
			frame.interlaced_frame = 0;
			frame.top_field_first = 0;
			frame.afd_aspect_ratio_ = -1;
			frame.afd_command_ = -1;
			switch (m_in_Resolution.eFrameRate)
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
			if (lpFrame.pVideoBuffer)
				free(lpFrame.pVideoBuffer);
			if (lpFrame.pAudioBuffer)
				free(lpFrame.pAudioBuffer);
			return true;
		}
			
		
		matrox_sdi_capture::matrox_sdi_capture(core::video_format format,int NeedAChannel,producer_need need)
			:impl_(new impl(format, NeedAChannel,need))
		{
		}
		
		bool matrox_sdi_capture::get_frame(FrameforProducer & frame) {return impl_->get_frame(frame);}
		int  matrox_sdi_capture::_GetChannels()
		{
			return impl_->_GetChannels();
		}

		matrox_sdi_capture::~matrox_sdi_capture()
		{
			impl_->Stop();
			impl_ = NULL;
		}
	}
}