#include "../StdAfx.h"
#include "redlink_consumer.h"
//#include "../utility.h"
#include <common/diagnostics/graph.h>
#include <common/future.h>
#include <common/param.h>

#include <common/executor.h>
#include <common/os/general_protection_fault.h>
#include <core/frame/frame.h>
#include <core/video_format.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/consumer/frame_consumer.h>
#include <core/help/help_sink.h>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>
#include <vector>

//[Omni_SDK] 16字节对齐的宏
#define GET_ALIGN_ADDR_16(P) (((reinterpret_cast<Om_UINT_PTR>(P)+0x0f) & (((Om_UINT_PTR)(-1)) << 4)))

namespace caspar {
	namespace redlink {
		struct configuration{
			std::wstring ratio = L"16:9";
			core::audio_channel_layout	out_channel_layout = core::audio_channel_layout::invalid();
			core::audio_channel_layout get_adjusted_layout(const core::audio_channel_layout& in_layout) const
			{
				auto adjusted = out_channel_layout == core::audio_channel_layout::invalid() ? in_layout : out_channel_layout;
				return adjusted;
			}
			int boardIndex;
			int portIndex;
			Omn_COLOR_FORMAT colorFmt =OmnCOLORFORMAT_BGRA;
			std::wstring name = L"RedLink Video";
		};
		struct redlink_consumer : boost::noncopyable {
			const configuration									config_;
			core::video_format_desc								format_desc_;
			const spl::shared_ptr<diagnostics::graph>			graph_;
			const core::audio_channel_layout					in_channel_layout_;
			const core::audio_channel_layout					out_channel_layout_ = config_.get_adjusted_layout(in_channel_layout_);
			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;
			caspar::timer										tick_timer_;
			tbb::atomic<bool>									is_running_;
			Omn_VIDEO_STANDARD vidStandard;
			executor							            executor_{ L"RedlinkConsumer" };
			struct SPlayCallbackParam
			{
				unsigned int	cardNo;
				unsigned int	chNo;
				unsigned int	wid;
				unsigned int	hig;
				unsigned int    pitch;
				unsigned char	*pV;
				unsigned char	*pA;
				redlink_consumer * redlink;
			};
			SPlayCallbackParam callbackParam;
		public:
			static Omn_RETURN_CODE PlayCallback(SOmn_SyncVACallbackInfo *sdkInfo, Om_VOID *param)//[Omni_SDK]	播出回调函数
			{
				static unsigned int c = 0;
				static int32_t * pAudio_ =  new int32_t[1920];
				SPlayCallbackParam *p = (SPlayCallbackParam *)param;

				{
					auto frame = core::const_frame::empty();
					if (p->redlink->frame_buffer_.try_pop(frame))
					{
						std::memcpy(p->pV, frame.image_data().begin(), p->wid * p->hig * 4);
						unsigned int i, j;
						const int32_t* data = frame.audio_data().begin();
						int32_t* pAA = (int32_t *)p->pA;

						for (i = 0; i < sdkInfo->dwAudioSampleCount; i++)
						{
							for (j = 0; j < 2; j++)
							{
								pAA[i * 16 + j] = *(data + i*2 + j);
							}
						}
					}
				}

				//[Omni_SDK]
				//数据提交时数据结构。在进行此次数据提交前需对该结构变量进行必要的
				//更新，包括要采集的视频属性、视音频Buffer信息等。
				//注：Buffer地址和pitch必须保证16字节对齐！！！
				SOmnBufUpdataInfo update_info;
				memset(&update_info, 0, sizeof(update_info));
				update_info.dwSize = sizeof(update_info);
				update_info.dwUpdateNo = c;

				update_info.enumBufUpdateFlag = Omn_BUFUPDATEFLAG_FRAME;
				update_info.enumVideoScanType = OmnVIDEOSCANMODE_Progressive;
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_FRAME].pBufferAddr = (Om_VOID *)(p->pV);
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_FRAME].dwBufferLinePitch = p->pitch;
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_FRAME].dwBufferSize = p->pitch*p->hig;

				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_AUDIO].pBufferAddr = (Om_VOID *)(p->pA);
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_AUDIO].dwBufferSize = sdkInfo->dwAudioSampleCount * 64;

				++c;
				//[Omni_SDK]
				//提交数据
				Om_HRESULT hr = Omn_UpdateBuffer(p->cardNo, Omn_PORTTYPE_PLAY_DATA, p->chNo, &update_info);
				return hr;
			}
			redlink_consumer(const configuration& config,
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& in_channel_layout
			) : config_(config)
				, format_desc_(format_desc)
				, in_channel_layout_(in_channel_layout)
			{
				graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
				graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
				graph_->set_text(print());
				diagnostics::register_graph(graph_);
				frame_buffer_.set_capacity(1);
				vidStandard = get_redlink_video_format(format_desc.format);
				is_running_ = false;
#pragma region初始化板卡数据
				//[Omni_SDK]
				//板卡全局信息
				SOmnGlobalInfo glbInfo;
				memset(&glbInfo, 0, sizeof(glbInfo));

				//[Omni_SDK]
				//查询当前全局信息
				Omn_QueryGlobalInfo(&glbInfo);

				//[Omni_SDK]
				//判断是否有板卡，并检测输入参数合法性
				if (glbInfo.dwBoardNum == 0 || config_.boardIndex >= glbInfo.dwBoardNum)
				{
					//Omn_Release();
					CASPAR_LOG(error) << print() << L" board index: " << config_.boardIndex << " error with board amount: " << glbInfo.dwBoardNum;
					return;
				}

				//[Omni_SDK]
				//检测输入参数合法性
				if (config_.portIndex >= glbInfo.psBoardInfo[config_.boardIndex].dwPlayDataPortNum)
				{
					//Omn_Release();
					CASPAR_LOG(error) << print() << L" port index: " << config_.portIndex << " error with port amount: " << glbInfo.psBoardInfo[config_.boardIndex].dwPlayDataPortNum;
					return;
				}

				//[Omni_SDK]
				//对于具有可切换接口的板卡，要判断当前接口的入出方向，只有为输出方向时才能进行播出。
				if (glbInfo.psBoardInfo[config_.boardIndex].enumBoardType == Omn_BOARDTYPE_SER400 || glbInfo.psBoardInfo[config_.boardIndex].enumBoardType == Omn_BOARDTYPE_SER400K)
				{
					SOmnBoardInterfaceInfo interfaceInfo;
					memset(&interfaceInfo, 0, sizeof(interfaceInfo));
					Omn_GetBoardParamEx(config_.boardIndex, Omn_BOARDCONFIGTYPE_INTERFACE, &interfaceInfo);
					if (interfaceInfo.InterfaceDirection[config_.portIndex] != 1)
					{
						//Omn_Release();
						printf("#ERROR: interface is input\n");
						CASPAR_LOG(error) << print() << L" interface is input.";
						return;
					}
				}

				//[Omni_SDK]
				//PDP端口参数
				SOmnPlayDataPortParam pdpParam;
				memset(&pdpParam, 0, sizeof(pdpParam));

				//[Omni_SDK]
				//获取PDP播出端口参数
				Omn_GetPlayDataPortParam(config_.boardIndex, config_.portIndex, &pdpParam);

				//[Omni_SDK]
				//更新PDP端口制式、颜色格式
				//此处队列长度使用缺省配置，若长度为1，则为场方式播出，否则，为帧方式播出
				pdpParam.enumVideoStandard = vidStandard;
				pdpParam.enumColorFormat = config_.colorFmt;
				//pdpParam.dwFrameBufferAmount = 10;

				//[Omni_SDK]
				//设置PDP端口参数
				Omn_SetPlayDataPortParam(config_.boardIndex, config_.portIndex, &pdpParam);

				//[Omni_SDK]
				//OSP输出端口参数
				SOmnOutputSignalPortParam ospParam;
				memset(&ospParam, 0, sizeof(ospParam));

				//[Omni_SDK]
				//获取OSP端口参数
				Omn_GetOutputSignalPortParam(config_.boardIndex, config_.portIndex, &ospParam);

				//[Omni_SDK]
				//更新OSP端口制式
				ospParam.enumVideoStandard = vidStandard;

				//[Omni_SDK]
				//设置OSP端口参数
				Omn_SetOutputSignalPortParam(config_.boardIndex, config_.portIndex, &ospParam);

				//--------------------------
				/*SOmnBoardInterfaceInfo itf_info = { 0 };
				Omn_GetBoardParamEx(config_.boardIndex, Omn_BOARDCONFIGTYPE_IO_WORK_MODE, &itf_info);
				itf_info.InterfaceDirection[config_.portIndex] = 1;*/
				//Omn_IO_WORK_MODE
				/*int workMode = Omn_IO_WORKMODE_7In1Out;
				Om_HRESULT hresult = Omn_SetBoardParamEx(config_.boardIndex, Omn_BOARDCONFIGTYPE_IO_WORK_MODE, (Om_PVOID)&workMode);*/
				//--------------------------

				// 准备回调函数用户自定义参数信息
				unsigned char *pV = new unsigned char[8 * format_desc_.width * format_desc_.height];
				unsigned char *pA = new unsigned char[256 * 1024];
				memset(pA, 0, 256 * 1024);
				unsigned int w, h;
				Omn_GetVidStdPara(vidStandard, w, h);
				
				callbackParam = { 0 };
				callbackParam.cardNo = config_.boardIndex;
				callbackParam.chNo = config_.portIndex;
				callbackParam.pV = (unsigned char *)GET_ALIGN_ADDR_16(pV);
				callbackParam.pA = (unsigned char *)GET_ALIGN_ADDR_16(pA);
				callbackParam.wid = format_desc_.width;//w;
				callbackParam.hig = format_desc_.height;//h;
				callbackParam.pitch = config_.colorFmt == OmnCOLORFORMAT_UYVY ? (w * 2) : (w * 4);
				callbackParam.redlink = this;

				//[Omni_SDK]
				//注册回调函数，分配播出资源
				Omn_RETURN_CODE hr = Omn_PrePlay(config_.boardIndex, config_.portIndex, Om_FALSE, redlink_consumer::PlayCallback , Om_NULL, Om_NULL, &callbackParam);
				if (hr != Omn_SUCCESS)
				{
					//Omn_Release();
					CASPAR_LOG(error) << print() << L" Omn_PrePlay() returned failed: " << hr;
					return;
				}

				//[Omni_SDK]
				//启动播出
				hr = Omn_StartPlay(config_.boardIndex, config_.portIndex, Om_NULL);
				if (hr != Omn_SUCCESS)
				{
					//Omn_Release();
					CASPAR_LOG(error) << print() << L" Omn_StartPlay() returned failed: " << hr;
					return;
				}
				CASPAR_LOG(info) << print() << L" Redlink play ok";

				is_running_ = true;
#pragma endregion
			}
			Omn_VIDEO_STANDARD get_redlink_video_format(core::video_format fmt)
			{
				switch (fmt)
				{
				case core::video_format::pal:			return OmnVIDEOSTANDARD_PAL;
				case core::video_format::ntsc:			return OmnVIDEOSTANDARD_NTSC2997;
				
				case core::video_format::x720p2398:		return OmnVIDEOSTANDARD_HD720p_2398;
				case core::video_format::x720p2400:		return OmnVIDEOSTANDARD_HD720p_24;
				case core::video_format::x720p2500:		return OmnVIDEOSTANDARD_HD720p_25;
				case core::video_format::x720p5000:		return OmnVIDEOSTANDARD_HD720p_50;
				case core::video_format::x720p2997:		return OmnVIDEOSTANDARD_HD720p_2997;
				case core::video_format::x720p5994:		return OmnVIDEOSTANDARD_HD720p_5994;
				case core::video_format::x720p3000:		return OmnVIDEOSTANDARD_HD720p_30;
				case core::video_format::x720p6000:		return OmnVIDEOSTANDARD_HD720p_60;
				case core::video_format::x1080p2398:	return OmnVIDEOSTANDARD_HD1080p_2398;
				case core::video_format::x1080p2400:	return OmnVIDEOSTANDARD_HD1080p_24;
				case core::video_format::x1080i5000:	return OmnVIDEOSTANDARD_HD1080i_25;
				
				case core::video_format::x1080p2500:	return OmnVIDEOSTANDARD_HD1080p_25;
				case core::video_format::x1080p2997:	return OmnVIDEOSTANDARD_HD1080p_2997;
				case core::video_format::x1080p3000:	return OmnVIDEOSTANDARD_HD1080p_30;
				case core::video_format::x1080p5000:	return OmnVIDEOSTANDARD_HD1080P_50;
				case core::video_format::x1080p5994:	return OmnVIDEOSTANDARD_HD1080P_5994;
				case core::video_format::x1080p6000:	return OmnVIDEOSTANDARD_HD1080P_60;
				case core::video_format::x1556p2398:	return OmnVIDEOSTANDARD_2K1556P_2398;
				case core::video_format::x1556p2400:	return OmnVIDEOSTANDARD_2K1556P_24;
				
				case core::video_format::x2160p2398:	return OmnVIDEOSTANDARD_4K_3840P_2398;
				case core::video_format::x2160p2400:	return OmnVIDEOSTANDARD_4K_3840P_24;
				case core::video_format::x2160p2500:	return OmnVIDEOSTANDARD_4K_3840P_25;
				case core::video_format::x2160p2997:	return OmnVIDEOSTANDARD_4K_3840P_2997;
				case core::video_format::x2160p3000:	return OmnVIDEOSTANDARD_4K_3840P_30;
				case core::video_format::x2160p5000:	return OmnVIDEOSTANDARD_4K_3840P_50;
				case core::video_format::x2160p5994:	return OmnVIDEOSTANDARD_4K_3840P_5994;
				case core::video_format::x2160p6000:	return OmnVIDEOSTANDARD_4K_3840P_60;

				case core::video_format::x576p2500:		
				case core::video_format::x1080i5994:	
				case core::video_format::x1080i6000:	
				case core::video_format::x1556p2500:	
				case core::video_format::dci1080p2398:	
				case core::video_format::dci1080p2400:	
				case core::video_format::dci1080p2500:	
				case core::video_format::dci2160p2398:	
				case core::video_format::dci2160p2400:	
				case core::video_format::dci2160p2500:	
					return OmnVIDEOSTANDARD_UNKNOW;
				default:								return OmnVIDEOSTANDARD_UNKNOW;
				}
			}
			~redlink_consumer()
			{
				//先停止播放再设置空帧
				StopPlay();
				frame_buffer_.try_push(core::const_frame::empty());				
				is_running_ = false;
			}
			void StopPlay()
			{
				Omn_RETURN_CODE hr = Omn_StopPlay(config_.boardIndex, config_.portIndex, Om_NULL);
				if (hr != Omn_SUCCESS)
				{
					CASPAR_LOG(error) << print() << L" Omn_StopPlay() returned failed: " << hr;
				}
				hr = Omn_ClosePlay(config_.boardIndex, config_.portIndex);
				if (hr != Omn_SUCCESS)
				{
					CASPAR_LOG(error) << print() << L" Omn_ClosePlay() returned failed: " << hr;
				}
			}
			std::wstring print() const
			{
				return L"redlink consumer[" + config_.name + L"|" + format_desc_.name + L"]";
			}
			std::future<bool> send(core::const_frame frame)
			{
				graph_->set_value("tick-time", tick_timer_.elapsed()*format_desc_.fps*0.5);
				if (!frame_buffer_.try_push(frame))
					graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
				tick_timer_.restart();
				return make_ready_future(is_running_.load());
			}
		};

		struct redlink_consumer_proxy : public core::frame_consumer
		{
			core::monitor::subject			monitor_subject_;
			const configuration				config_;
			std::unique_ptr<redlink_consumer> consumer_;
		public:
			redlink_consumer_proxy(const configuration& config)
				:config_(config)
			{}
			~redlink_consumer_proxy()
			{
				if (consumer_)
				{
					auto str = print();
					consumer_.reset();
					CASPAR_LOG(info) << str << L"Redlink Successfully Uninitialized.";
				}
			}
			std::future<bool> send(core::const_frame frame) override
			{
				return consumer_->send(frame);
			}
			void initialize(
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& audio_channel_layout,
				int channel_index) override
			{
				consumer_.reset();
				consumer_.reset(new redlink_consumer(config_, format_desc, audio_channel_layout));
			}
			core::monitor::subject& monitor_output()
			{
				return monitor_subject_;
			}
			std::wstring print() const override
			{
				return consumer_ ? consumer_->print() : L"[redlink_consumer]";
			}
			std::wstring name() const override
			{
				return L"redlink";
			}
			boost::property_tree::wptree info() const override
			{
				boost::property_tree::wptree info;
				info.add(L"type", L"redlink");
				return info;
			}

			bool has_synchronization_clock() const override
			{
				return false;
			}

			int buffer_depth() const override
			{
				return 2;
			}
			int index() const override
			{
				return 1601;
			}

			int64_t presentation_frame_age_millis() const override
			{
				return 1;
			}
		};

		void describe_consumer(core::help_sink& sink, const core::help_repository& repo)
		{
			sink.short_description(L"RedLink Consumer.");
			sink.definitions()
				->item(L"board_index", L"The Redlink video card to use (See board order). Default is 0.")
				->item(L"port_index", L"The Redlink video card to use (See port order in board). Default is 0.");
		}
		spl::shared_ptr<core::frame_consumer> create_consumer(const std::vector<std::wstring>& params, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			if (params.size() < 1 || !boost::iequals(params.at(0), L"REDLINK"))
				return core::frame_consumer::empty();
			configuration config;
			if (contains_param(L"channel-layout", params))
			{
				auto channel_layout = get_param(L"channel-layout", params);
				if (!channel_layout.empty())
				{
					CASPAR_SCOPED_CONTEXT_MSG("/channel-layout")

						auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(channel_layout);

					if (!found_layout)
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout " + channel_layout + L" not found."));

					config.out_channel_layout = *found_layout;
				}
			}
			config.boardIndex = get_param(L"board", params, -1);
			config.portIndex = get_param(L"port", params ,- 1);
			return spl::make_shared<redlink_consumer_proxy>(config);
		}
		spl::shared_ptr<core::frame_consumer> create_preconfigured_consumer(const boost::property_tree::wptree& ptree, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			configuration config;
			config.boardIndex = ptree.get(L"board", config.boardIndex);
			config.portIndex = ptree.get(L"port", config.portIndex);
			auto channel_layout = ptree.get_optional<std::wstring>(L"channel-layout");
			if (channel_layout)
			{
				CASPAR_SCOPED_CONTEXT_MSG("/channel-layout")

					auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(*channel_layout);

				if (!found_layout)
					CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout " + *channel_layout + L" not found."));

				config.out_channel_layout = *found_layout;
			}
			return spl::make_shared<redlink_consumer_proxy>(config);
		}
	}
}
