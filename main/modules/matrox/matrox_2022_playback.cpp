#include "matrox_2022_playback.h"

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
		matrox_2022_playback::impl::impl(consumer_need need,core::video_format format, uint32_t channels, std::map<std::string, std::string>& ops)
			:CMvUnknown(L"ConsumerMvsNotificationCallback", NULL)
			,m_ui32WriteToReadDelayInFrame(4)
			,m_ui32DepthInFrame(12)
			,m_format_(format)
			,m_need_(need)
			,m_preset_channel_(channels)
			,args_options_(ops)
			,m_isplaying(false)
		{
                    
			CMvHResult oHr = MV_NOERROR;
			oHr = _SysConfiguration();
			if (oHr.DidFail())
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(mvErrorToString(oHr))
					<< boost::errinfo_api_function("in matrox_2022_playback, _SysConfiguration"));
			}

			oHr = _SetSMvSfpIp();
			if (oHr.DidFail())
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(mvErrorToString(oHr))
					<< boost::errinfo_api_function("in matrox_2022_playback, SetSMvSfpIp"));
			}

			oHr = _SetSMvSdiIpOutputConnector();
			if (oHr.DidFail())
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(mvErrorToString(oHr))
					<< boost::errinfo_api_function("in matrox_2022_playback, SetSMvSdiIpOutputConnector"));
			}

			oHr = _BuildTopology();
			if (oHr.DidFail())
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(mvErrorToString(oHr))
					<< boost::errinfo_api_function("in matrox_2022_playback, _BuildTopology"));
			}
			bufferqueue.set_capacity(50);
		}
		
		matrox_2022_playback::impl::~impl()
		{

		}

		CMvHResult matrox_2022_playback::impl::Stop()
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

		void matrox_2022_playback::impl::Play()
		{
			CMvHResult oHr;
			oHr = m_pJHostNode->RegisterCallbackForWrite(this);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"matrox_2022_playback::impl::Play Failure";
			}
		}
		void matrox_2022_playback::impl::send(void *pvideo, void * pvideo1, void * paudio, void * paudio1)
		{
			if (_IsFieldBased())
			{
				FrameForConsumer frame;
				frame.pvideo.reset((uint8_t*)pvideo);
				frame.paudio.reset((uint8_t*)paudio);
				frame.IsTop = true;
				//bufferqueue.push(frame2022);
				if (!bufferqueue.try_push(frame))
					CASPAR_LOG(warning) << L"matrox_2022_playback::impl::send try push top field failure!";
				frame.pvideo.reset((uint8_t*)pvideo1);
				frame.paudio.reset((uint8_t*)paudio1);
				frame.IsTop = false;
				//bufferqueue.push(frame2022);
				if (!bufferqueue.try_push(frame))
					CASPAR_LOG(warning) << L"matrox_2022_playback::impl::send try push bottom field failure!";
			}
			else
			{
				FrameForConsumer frame;
				frame.pvideo.reset((uint8_t*)pvideo);
				frame.paudio.reset((uint8_t*)paudio);
				//bufferqueue.push(frame2022);
				if (!bufferqueue.try_push(frame))
					CASPAR_LOG(warning) << L"matrox_2022_playback::impl::send try push frame failure!";
			}
			if (!m_isplaying)
			{
				m_isplaying = true;
				this->Play();
			}
		}

		HRESULT __stdcall matrox_2022_playback::impl::NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters)
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

		CMvHResult matrox_2022_playback::impl::_SysConfiguration()
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
				CASPAR_LOG(error) << L"in matrox_2022_playback, CoCreateInstance Failure : " << mvErrorToString(oHr);
				return oHr;
			}

			//获取板卡信息
			oHr = _EnumerateCards();
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback, _EnumerateCards Failure : " << mvErrorToString(oHr);
				return oHr;
			}
			if (m_CardConfigs.size() < m_need_.card + 1)
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback, card count less than deviceIndex";
				return MV_E_INVALID_PARAMETER;
			}
			//检测输出通道数量
			if (m_CardConfigs[m_need_.card].vecpJSdiIpOutputConnectors.size() == 0 ||
				m_CardConfigs[m_need_.card].vecpJSdiIpOutputConnectors.size() < (m_need_.sdi + 1))
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback,output connectors empty or less than connector index";
				return MV_E_INVALID_PARAMETER;
			}

			return MV_NOERROR;
		}

		void matrox_2022_playback::impl::_GetResolution(SMvResolutionInfo *out_pResInfo)
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
			CASPAR_LOG(error) << L"in matrox_2022_playback, Unspecified or invalid resolution format";
		}

		CMvHResult matrox_2022_playback::impl::_EnumerateCards()
		{
			CMvHResult oHr = MV_NOERROR;
			// Get the cards enumerator
			TMvSmartPtr<IMvSystemConfigurationCardEnumerator> pJEnum;
			oHr = m_IMvSystemConfiguration_->CreateCardEnumerator(&pJEnum);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback, _EnumerateCards CreateCardEnumerator Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			oHr.AssignNoAssert(pJEnum->Next(&pJCardConfig));
			while (oHr.DidSucceed())
			{
				SdiIpCardInfo	CardInfo;
				CardInfo.sHwInfo.size = sizeof(CardInfo.sHwInfo);
				CardInfo.pJCardConfig = pJCardConfig;
				CardInfo.sHwInfo.sConnectorsDescription.size = sizeof(CardInfo.sHwInfo.sConnectorsDescription);
				oHr = pJCardConfig->GetCardInformation(&CardInfo.sHwInfo, 0);

				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback, GetCardInformation Failure:" << mvErrorToString(oHr);
					return oHr;
				}

				oHr = _FillSfps(CardInfo);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback, _FillSfps Failure:" << mvErrorToString(oHr);
					return oHr;
				}

				oHr = _FillConnectors(CardInfo);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback, _FillConnectors Failure:" << mvErrorToString(oHr);
					return oHr;
				}

				m_CardConfigs.push_back(CardInfo);
				oHr = _ValidateAndDisplayCardTemperature(CardInfo);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"in matrox_2022_playback, _ValidateAndDisplayCardTemperature Failure:" << mvErrorToString(oHr);
					return oHr;
				}
				// Next card
				pJCardConfig = NULL;
				oHr.AssignNoAssert(pJEnum->Next(&pJCardConfig));
			}			
			return MV_NOERROR;
		}

		CMvHResult matrox_2022_playback::impl::_FillSfps(SdiIpCardInfo & io_rsCardInfo)
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

		CMvHResult matrox_2022_playback::impl::_FillConnectors(SdiIpCardInfo & io_rsCardInfo)
		{
			CMvHResult oHr;

			//
			// Enumerate Output connectors
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
					io_rsCardInfo.vecpJSdiIpOutputConnectors.push_back(pJOutputConnector);

					// Next card
					pJOutputConnector = NULL;
					oHr.AssignNoAssert(pJEnumOutput->Next(&pJOutputConnector));
				}

				// Ignore the error from the NEXT of the enumerator.
				oHr = MV_NOERROR;
			}
			return oHr;
		}

		CMvHResult matrox_2022_playback::impl::_ValidateAndDisplayCardTemperature(SdiIpCardInfo & in_krsCardInfo)
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
						CASPAR_LOG(warning) << L"in matrox_2022_playback,WARNING: OVERHEAT!";
						oHr = MV_E_FAIL;
					}

					if (asInfo[i].eFanStatus == keMvFanStatusTooSlowOrStopped)
					{
						CASPAR_LOG(warning) << L"in matrox_2022_playback,Fan: ERROR: Too slow or stopped!";
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

		void matrox_2022_playback::impl::set_params(std::map<std::string, std::string>& ops,SMvSfpIpSettings& sfpipsets)
		{
			//	sfpipaddr		--	Ipv4Address
			// 	sfpipgw			--	IPv4Gateway
			// 	sfpipnetmask	--	IPv4Netmask
			// 	vlan			--	EnableVirtualLAN  -- true/false
			// 	pcp				--	VirtualLANTagPCP
			// 	dei				--	EnableVirtualLANTagDEI -- true/false
			// 	vid				--	VirtualLANTagVID
			auto it = ops.begin();
			while (it != ops.end())
			{
				if (it->first == "sfpipaddr")
				{
					std::string sfpipaddr = it->second;
					GetIpAddress(u16(sfpipaddr), sfpipsets.ui32IPv4Address);
					it = ops.erase(it);
				}
				else if (it->first == "sfpipgw")
				{
					std::string sfpipgw = it->second;
					GetIpAddress(u16(sfpipgw), sfpipsets.ui32IPv4Gateway);
					it = ops.erase(it);
				}
				else if (it->first == "sfpipnetmask")
				{
					std::string sfpipnetmask = it->second;
					GetIpAddress(u16(sfpipnetmask), sfpipsets.ui32IPv4Netmask);
					it = ops.erase(it);
				}
				else if (it->first == "vlan")
				{
					std::string vlan = it->second;
					if (vlan.compare("false"))
					{
						sfpipsets.bEnableVirtualLAN = false;
					}
					else
					{
						sfpipsets.bEnableVirtualLAN = true;
					}
					it = ops.erase(it);
				}	
				else if (it->first == "pcp")
				{
					sfpipsets.ui32VirtualLANTagPCP = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else if (it->first == "dei")
				{
					std::string dei = it->second;
					if (dei.compare("false"))
					{
						sfpipsets.bEnableVirtualLANTagDEI = false;
					}
					else
					{
						sfpipsets.bEnableVirtualLANTagDEI = true;
					}
					it = ops.erase(it);
				}
				else if (it->first == "vid")
				{
					sfpipsets.ui32VirtualLANTagVID = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else
				{
					it++;
				}
			}
		}

		void matrox_2022_playback::impl::set_params(std::map<std::string, std::string>& ops, SMvSdiIpOutputConnectorSettings& sdiipoutsets)
		{
			// 		rtpsrc			--	RTPSyncSourceIdentifier
			// 		dscp			--	TypeOfServiceDSCP
			// 		ecn				--	TypeOfServiceECN
			// 		ttl				--	TimeToLiveInSeconds
			// 		srcport			--  SrcUDPPort
			// 		dstaddr			--	DstIPv4Address
			// 		dstport			--	DstUDPport
			// 		redundancy      --	RedundancyEnable				--true/false
			// 		resrcport		--	RedundancySrcUDPPort
			// 		redstaddr       --	RedundancyDstIPv4Address
			// 		redstport		--	RedundancyDstUDPPort
			auto it = ops.begin();
			while (it != ops.end())
			{
				if (it->first == "rtpsrc")
				{
					sdiipoutsets.ui32RTPSyncSourceIdentifier = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else if (it->first == "dscp")
				{
					sdiipoutsets.ui32TypeOfServiceDSCP = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else if (it->first == "ecn")
				{
					sdiipoutsets.ui32TypeOfServiceECN = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else if (it->first == "ttl")
				{
					sdiipoutsets.ui32TimeToLiveInSeconds = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else if (it->first == "srcport")
				{
					sdiipoutsets.ui16SrcUDPPort = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else if (it->first == "dstaddr")
				{
					std::string dstaddr = it->second;
					GetIpAddress(u16(dstaddr), sdiipoutsets.ui32DstIPv4Address);
					it = ops.erase(it);
				}
				else if (it->first == "dstport")
				{
					sdiipoutsets.ui16DstUDPport = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else if (it->first == "redundancy")
				{
					std::string redundancy = it->second;
					if (redundancy.compare("false"))
					{
						sdiipoutsets.bRedundancyEnable = false;
					}
					else
					{
						sdiipoutsets.bRedundancyEnable = true;
					}
					it = ops.erase(it);
				}
				else if (it->first == "resrcport")
				{
					sdiipoutsets.ui16RedundancySrcUDPPort = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else if (it->first == "redstaddr")
				{
					std::string redstaddr = it->second;
					GetIpAddress(u16(redstaddr), sdiipoutsets.ui32RedundancyDstIPv4Address);
					it = ops.erase(it);
				}
				else if (it->first == "redstport")
				{
					sdiipoutsets.ui16RedundancyDstUDPPort = atoi((it->second).c_str());
					it = ops.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
	
		// Control Sfp IP settings.
		CMvHResult matrox_2022_playback::impl::_SetSMvSfpIp()
		{
			CMvHResult oHr = MV_NOERROR;
			SMvSfpIpSettings sSettings = { sizeof(sSettings) };
			m_CardConfigs[m_need_.card].vecpJSdiIpOutputConnectors[m_need_.sdi]->GetAssociatedSfpIp(&m_pSfpIp);
			oHr = m_pSfpIp->GetSettings(sSettings);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"Unable to Get Sfp IP Settings :" << mvErrorToString(oHr);
				return oHr;
			}
			set_params(args_options_, sSettings);
			oHr = m_pSfpIp->SetSettings(sSettings);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"Unable to Set Sfp IP Settings: "<< mvErrorToString(oHr);
			}

			return oHr;
		}
			
		// Control SDI IP  settings
		CMvHResult matrox_2022_playback::impl::_SetSMvSdiIpOutputConnector()
		{
			CMvHResult oHr = MV_NOERROR;
			SMvSdiIpOutputConnectorSettings sConnectorSettings = { sizeof(sConnectorSettings) };
			oHr = m_CardConfigs[m_need_.card].vecpJSdiIpOutputConnectors[m_need_.sdi]->GetConnectorSettings(sConnectorSettings);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error)<<L"Error: Unable to Get Output SDI IP connector Settings:"<<mvErrorToString(oHr);
				return oHr;
			}

			set_params(args_options_, sConnectorSettings);
			oHr = m_CardConfigs[m_need_.card].vecpJSdiIpOutputConnectors[m_need_.sdi]->SetConnectorSettings(sConnectorSettings);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"Error: Unable to Set Output SDI IP connector Settings: "<< mvErrorToString(oHr);
			}

			return oHr;
		}

		CMvHResult matrox_2022_playback::impl::_BuildTopology()
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
	
		CMvHResult matrox_2022_playback::impl::_CleanTopology() //与SDK Playback2022 Sample中的Clean方式不同，待检验
		{
			CMvHResult oHr;
			//清除卡上的元素所有的默认状态并且永久内存，这个接口如果不是清除所有的拓扑的话应该不需要调用吧
			oHr = m_CardConfigs[m_need_.card].pJCardConfig->ClearDefaultsAndPermanentMemory();
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback, ClearDefaultsAndPermanentMemory Failure: " <<mvErrorToString(oHr);
				return oHr;
			}

			std::wstring strTopologyName = L"MatroxConsumer_"+ boost::lexical_cast<std::wstring>(m_need_.card) + L"_" + boost::lexical_cast<std::wstring>(m_need_.sdi);
			TMvSmartPtr<IMvTopologiesEnumerator>	pJTopologyEnumerator;
			oHr = m_CardConfigs[m_need_.card].pJCardConfig->CreateTopologiesEnumerator(&pJTopologyEnumerator);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback,CreateTopologiesEnumerator";
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
							CASPAR_LOG(error) << L"in matrox_2022_playback,DestroyTopology Failure:" <<mvErrorToString(oHr);
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
		
		CMvHResult matrox_2022_playback::impl::_RetrieveGenlockClock()
		{
			CMvHResult oHr;

			// Get the clock enumerator interface.
			TMvSmartPtr<IMvSystemClockEnumerator>	pJClockEnum;
			TMvSmartPtr<IMvSystemClock>				pJClock;
			oHr = m_CardConfigs[m_need_.card].pJCardConfig->CreateSystemClockEnumerator(&pJClockEnum);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback,CreateSystemClockEnumerator Failure: " << mvErrorToString(oHr);
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
				CASPAR_LOG(error) << L"in matrox_2022_playback,clock enum not find genlock";
				return MV_E_NOT_FOUND;
			}
			return MV_NOERROR;
		}

		CMvHResult matrox_2022_playback::impl::_SetupGenlock()//与SDK Playback2022 Sample中的SetupGenlock不同,待检验
		{
			CMvHResult oHr = MV_NOERROR;

			// Get genlock interface.         
			TMvSmartPtr<IMvGenlockConfiguration>	pJGenlockConfig;
			oHr = m_CardConfigs[m_need_.card].pJCardConfig->GetGenlockConfiguration(&pJGenlockConfig);

			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback,GetGenlockConfiguration Failure:" << mvErrorToString(oHr);
				return oHr;
			}

			// Get current genlock settings
			SMvGenlockSettings sCurrentGenlockSettings = { sizeof(sCurrentGenlockSettings) };
			oHr = pJGenlockConfig->GetGenlockSettings(sCurrentGenlockSettings);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback,GetGenlockSettings Failure:" << mvErrorToString(oHr);
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
				CASPAR_LOG(error) << L"in matrox_2022_playback,SetGenlockSettings";
				return oHr;
			}
			// Wait 2 seconds to be sure the hardware is stable enough to start playback.
			boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
			return MV_NOERROR;
		}

		
		CMvHResult matrox_2022_playback::impl::_BuildMainTopology()
		{
			CMvHResult oHr;

			//Create the topology
			std::wstring strTopologyName = L"MatroxConsumer_" + boost::lexical_cast<std::wstring>(m_need_.card) + L"_" + boost::lexical_cast<std::wstring>(m_need_.sdi);
			oHr = m_IMvSystemConfiguration_->CreateSystemTopology(u8(strTopologyName).c_str(), m_pJClock, &m_pJSystemTopology);
			if (oHr.DidFail())
			{
				CASPAR_LOG(error) << L"in matrox_2022_playback,CreateSystemTopology Failure:" << mvErrorToString(oHr);
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
				CASPAR_LOG(error) << L"in matrox_2022_playback,CreateCardNode Failure:" << mvErrorToString(oHr);
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
				CASPAR_LOG(error) << L"in matrox_2022_playback,CreateHostNode Failure:" << mvErrorToString(oHr);
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
				CASPAR_LOG(error) << L"in matrox_2022_playback,CreateTransferStream Failure: " << mvErrorToString(oHr);
				return oHr;
			}
		

			// Create the output stream.
			SMvOutputStreamSettings sOutStreamSettings;
			_InitOutputStreamSettings(sOutStreamSettings);				

			IMvSdiIpOutputConnector * apIVideoConnetor[1] = { m_CardConfigs[m_need_.card].vecpJSdiIpOutputConnectors[m_need_.sdi] };
			sname = L"Output" + boost::lexical_cast<std::wstring>((m_need_.sdi));
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
				CASPAR_LOG(error) << L"in matrox_2022_playback,CreateOutputStream Failure: " << mvErrorToString(oHr);
				return oHr;
			}

			return oHr;
		}
	

		void matrox_2022_playback::impl::_InitNodeSettings(SMvNodeSettings  &out_sNodeSettings,
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
		
		void matrox_2022_playback::impl::_InitOutputStreamSettings(SMvOutputStreamSettings & out_rsStreamSettings)
		{
			out_rsStreamSettings.ui32Size = sizeof(out_rsStreamSettings);
			out_rsStreamSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
// 			out_rsStreamSettings.aeVideoConnectorPosition[1] = keMvQuadrantTopRight;
// 			out_rsStreamSettings.aeVideoConnectorPosition[2] = keMvQuadrantBottomLeft;
// 			out_rsStreamSettings.aeVideoConnectorPosition[3] = keMvQuadrantBottomRight;
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

		bool matrox_2022_playback::impl::GetIpAddress(std::wstring addr,uint32_t & out_rui32Ipv4)
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

/////////////////////////////////////			
		matrox_2022_playback::matrox_2022_playback(consumer_need need, core::video_format format, int channels, std::map<std::string, std::string>& ops)
		:impl_(new impl(need, format, channels,ops))
		{
		}
		matrox_2022_playback::~matrox_2022_playback()
		{
			impl_->Stop();
			impl_ = NULL;
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
