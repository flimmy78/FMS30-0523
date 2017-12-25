#include "../StdAfx.h"
#include "Omni_Api.h"
#include "redlink_producer.h"
#include "../buffermng.h"
//#include "../process.h"
#include <thread>

#include "../../ffmpeg/producer/filter/filter.h"
#include "../../ffmpeg/producer/muxer/frame_muxer.h"
#include "../../ffmpeg/producer/muxer/display_mode.h"
#include "../../ffmpeg/producer/util/util.h"
#include <common/executor.h>
#include <common/diagnostics/graph.h>
#include <common/except.h>
#include <common/log.h>
#include <common/param.h>
#include <common/timer.h>

#include <core/frame/audio_channel_layout.h>
#include <core/frame/frame.h>
#include <core/frame/draw_frame.h>
#include <core/frame/frame_transform.h>
#include <core/frame/frame_factory.h>
#include <core/producer/frame_producer.h>
#include <core/producer/framerate/framerate_producer.h>
#include <core/monitor/monitor.h>
#include <core/diagnostics/call_context.h>
#include <core/mixer/audio/audio_mixer.h>
#include <core/help/help_repository.h>
#include <core/help/help_sink.h>

#define __RedLink_Channel 16
#define __RedLink_Channel_SampleSize 4
namespace caspar {
	namespace redlink {
		typedef struct _BOARD_IO_BUFFER_32b {
			unsigned int  aud_value[__RedLink_Channel];
		}BOARD_IO_BUFFER_32b;
		typedef struct _STEREO_32 {
			unsigned int  AudioL;
			unsigned int  AudioR;
		}STEREO_32;

		core::audio_channel_layout get_adjusted_channel_layout(core::audio_channel_layout layout)
		{
			if (layout.num_channels <= 2)
				layout.num_channels = 2;
			else if (layout.num_channels <= 8)
				layout.num_channels = 8;
			else
				layout.num_channels = 16;

			return layout;
		}

		struct SCallbackParam
		{
			unsigned int boardIdx;
			unsigned int portIdx;
			unsigned int width;
			unsigned int height;
			unsigned int pitch;
			std::shared_ptr<CBufMng> pBufList;
			//----------------------------------
			/*template <typename T>
			std::wstring to_string(const T& cadence)
			{
				return boost::join(cadence | boost::adaptors::transformed([](size_t i) { return boost::lexical_cast<std::wstring>(i); }), L", ");
			}*/

			ffmpeg::audio_input_pad create_input_pad(const core::video_format_desc& in_format, int num_channels)
			{
				return ffmpeg::audio_input_pad(
					boost::rational<int>(1, in_format.audio_sample_rate),
					in_format.audio_sample_rate,
					AVSampleFormat::AV_SAMPLE_FMT_S32,
					av_get_default_channel_layout(num_channels));
			}
			Omn_COLOR_FORMAT colorFmt;
		};

		/*************************************************************************
		* [Omni_SDK]
		*
		* ������:
		*     RecCallback
		* �������:
		*  sdkInfo: SDK�����SOmn_SyncVACallbackInfo�ṹ���͵Ĳ���ָ�롣
		*    param: Ӧ�ó����ڵ���Omn_PreRecord()ʱע����Զ������ָ�롣
		* �������:
		*     �ޡ�
		* ����:
		*     �ú���չʾ������ڲɼ�Ӧ����ʵ�ֲɼ��ص�������
		*     ��Ҫע����ǣ�Ӧ�ó����ڻص�������Ӧ�þ���������˴βɼ��޹ص����飨��
		*     ���ݴ����ȴ��Ȳ��������Է������ɼ�����ɶ�֡��
		* ����ֵ:
		*     Omn_SUCCESS : �ɹ���
		*     OTHER   : ʧ�ܡ�
		*************************************************************************/
		Om_HRESULT RecCallback(SOmn_SyncVACallbackInfo *sdkInfo, Om_VOID *param)
		{
			Om_HRESULT hr = Omn_ERR_FAILED;
			SCallbackParam *p = (SCallbackParam *)param;
			SData va_data = { 0 };

			//[Omni_SDK]
			//�Ӳɼ�����������ȡ��Buffer�ڵ㡣
			//ע���ڴ����ʽ��Ӧ�ó���ȷ�����˴���Ϊʾ��չʾ�á�
			p->pBufList->GetFreeBuf(&va_data);
			if (va_data.pV)
			{
				//[Omni_SDK]
				//���ݻ�ȡʱ���ݽṹ���ڽ��д˴����ݻ�ȡǰ��Ըýṹ�������б�Ҫ��
				//���£�����Ҫ�ɼ�����Ƶ���ԡ�����ƵBuffer��Ϣ�ȡ�
				//ע��Buffer��ַ��pitch���뱣֤16�ֽڶ��룡����
				SOmnBufUpdataInfo update_info;
				memset(&update_info, 0, sizeof(update_info));
				update_info.dwSize = sizeof(update_info);
				update_info.enumBufUpdateFlag = Omn_BUFUPDATEFLAG_FRAME;
				update_info.enumVideoScanType = OmnVIDEOSCANMODE_Progressive;
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_FRAME].pBufferAddr = (Om_VOID *)GET_ALIGN_ADDR_16(va_data.pV);
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_FRAME].dwBufferSize = p->pitch*p->height;
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_FRAME].dwBufferLinePitch = p->pitch;
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_AUDIO].pBufferAddr = (Om_VOID *)GET_ALIGN_ADDR_16(va_data.pA);
				update_info.psBufferArr[Omn_UPDATEBUFFER_INDEX_AUDIO].dwBufferSize = sdkInfo->dwAudioSampleCount * __RedLink_Channel * __RedLink_Channel_SampleSize;//4 * 2;//

				//[Omni_SDK]
				//��ȡ1֡����Ƶ���ݣ���ɸò���������Ƶ���ݴӰ忨����Ӧ��׼�����ڴ��С�
				hr = Omn_UpdateBuffer(0, Omn_PORTTYPE_RECORD_DATA, p->portIdx, &update_info);

				//[Omni_SDK]
				//���ƽڵ���Ϣ�������ڵ�黹���ɼ�����������������ģ������ݽ��д���
				//�˴�ͬ��Ϊʾ��չʾʹ�ã����ع�ע�ڴ����ϸ�ڡ�
				va_data.wid = p->width;
				va_data.hig = p->height;
				va_data.pitch = p->pitch;
				va_data.audLen = sdkInfo->dwAudioSampleCount * __RedLink_Channel * __RedLink_Channel_SampleSize;//4 * 2;// 
				p->pBufList->PutDataBuf(&va_data);
			}
			static int count = 0;
			count++;
			return hr;
		}

		class redlink_producer
		{
			unsigned int boardIndex = 0;	//�忨����	��0��ʼ
			unsigned int portIndex = 0;		//�忨�������	��0��ʼ
			Omn_VIDEO_STANDARD vidStandard = OmnVIDEOSTANDARD_HD1080i_25;	//�ɼ����ݸ�ʽ
			Omn_COLOR_FORMAT colorFmt = OmnCOLORFORMAT_UYVY;

			SCallbackParam									config_;
			core::video_format_desc							in_format_desc_;
			core::video_format_desc							out_format_desc_;
			std::vector<int>								audio_cadence_ = in_format_desc_.audio_cadence;
			spl::shared_ptr<core::frame_factory>			frame_factory_;
			core::audio_channel_layout						channel_layout_;
			const std::wstring								filter_ = L"";
			ffmpeg::frame_muxer								muxer_{
				in_format_desc_.framerate,
				{ config_.create_input_pad(in_format_desc_, __RedLink_Channel /*channel_layout_.num_channels*/) },
				frame_factory_,
				out_format_desc_,
				channel_layout_,
				filter_,
				ffmpeg::filter::is_deinterlacing(filter_)
			};
			core::constraints								constraints_{ in_format_desc_.width, in_format_desc_.height };
			core::monitor::subject							monitor_subject_;
			tbb::concurrent_bounded_queue<core::draw_frame>	frame_buffer_;
			core::draw_frame								last_frame_ = core::draw_frame::empty();
			spl::shared_ptr<diagnostics::graph>				graph_;
			executor							            executor_{ L"Redlink" };
			executor							            executorVideoStandardChanged_{ L"RedlinkVideoStandardChanged" };
			bool _isRuning = false;
			bool _isRuningVideoStandardChanged = false;
			
			Omn_VIDEO_STANDARD rdpParamVideoStandard; //�ɼ��źŵ����ݵĸ�ʽ

		public: redlink_producer(
			const core::video_format_desc& in_format_desc,
			SCallbackParam params,
			const spl::shared_ptr<core::frame_factory>& frame_factory,
			const core::video_format_desc& out_format_desc,
			const core::audio_channel_layout& channel_layout,
			const std::wstring& filter) 
			: filter_(filter)
			, in_format_desc_(in_format_desc)
			, out_format_desc_(out_format_desc)
			, frame_factory_(frame_factory)
			, channel_layout_(get_adjusted_channel_layout(channel_layout))
			, boardIndex(params.boardIdx)
			, portIndex(params.portIdx)
			, colorFmt(params.colorFmt)
		{
			frame_buffer_.set_capacity(4);
			graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
			graph_->set_color("late-frame", diagnostics::color(0.6f, 0.3f, 0.3f));
			graph_->set_color("frame-time", diagnostics::color(1.0f, 0.0f, 0.0f));
			graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
			graph_->set_color("output-buffer", diagnostics::color(0.0f, 1.0f, 0.0f));
			graph_->set_text(print());
			diagnostics::register_graph(graph_);
			StartRecord();
		}
			SCallbackParam callbackParam;

			void ConstructionFrame(std::shared_ptr<CBufMng> param)
			{
				if (!_isRuning)
				{
					return;
				}
				caspar::timer			frame_timer;
				SData rec_data = { 0 };
				param->GetDataBuf(&rec_data);
				if (rec_data.pV)
				{
					auto video_frame = ffmpeg::create_frame();
					video_frame->data[0] = reinterpret_cast<uint8_t*>(rec_data.pV);
					video_frame->linesize[0] = rec_data.pitch;
					video_frame->format = AV_PIX_FMT_UYVY422;
					video_frame->width = callbackParam.width;
					video_frame->height = callbackParam.height;
					video_frame->interlaced_frame = in_format_desc_.field_mode != core::field_mode::progressive;
					video_frame->top_field_first = in_format_desc_.field_mode == core::field_mode::upper ? 1 : 0;
					video_frame->key_frame = 1;

					muxer_.push(static_cast<std::shared_ptr<AVFrame>>(video_frame));

					std::shared_ptr<core::mutable_audio_buffer>	audio_buffer;

					auto audio_data = reinterpret_cast<int32_t*>((int32_t*)rec_data.pA);
					audio_buffer = std::make_shared<core::mutable_audio_buffer>(
						audio_data,
						audio_data + rec_data.audLen / __RedLink_Channel_SampleSize);
					muxer_.push({ audio_buffer });

					for (auto frame = muxer_.poll(); frame != core::draw_frame::empty(); frame = muxer_.poll())
					{
						if (!frame_buffer_.try_push(frame))
						{
							auto dummy = core::draw_frame::empty();
							frame_buffer_.try_pop(dummy);

							frame_buffer_.try_push(frame);

							graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
						}
					}
					graph_->set_value("frame-time", frame_timer.elapsed()*out_format_desc_.fps*0.5);
					monitor_subject_ << core::monitor::message("/profiler/time") % frame_timer.elapsed() % out_format_desc_.fps;

					graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size()) / static_cast<float>(frame_buffer_.capacity()));
					monitor_subject_ << core::monitor::message("/buffer") % frame_buffer_.size() % frame_buffer_.capacity();

					param->PutFreeBuf(&rec_data);
				}
				else
				{
					boost::this_thread::sleep_for(boost::chrono::microseconds(40));
				}
				executor_.begin_invoke([=]() {ConstructionFrame(param); }, task_priority::high_priority);
			}

			void VideoStandardChanged()
			{
				if (!_isRuningVideoStandardChanged)
				{
					return;
				}
				Omn_VIDEO_STANDARD stan = GetVideoStandard();
				if (stan != OmnVIDEOSTANDARD_UNKNOW && stan != rdpParamVideoStandard)
				{
					_isRuning = _isRuningVideoStandardChanged = false;
					Om_HRESULT hr = Omn_StopRecord(boardIndex, portIndex, Om_NULL);
					if (hr != Omn_SUCCESS)
					{
						CASPAR_LOG(error) << print() << L" Omn_StopRecord() returned failed: " << hr;
					}
					//����close���ͷ��Ѿ�ע��Ļص���������RecCallbackȡ��������Ϊ�գ�""��
					hr = Omn_CloseRecord(boardIndex, portIndex);
					StartRecord();
					return;
				}
				boost::this_thread::sleep_for(boost::chrono::microseconds(40));
				executorVideoStandardChanged_.begin_invoke([=]() {VideoStandardChanged(); }, task_priority::high_priority);
			}

			void StartRecord()
			{
#pragma region ��ʼ���ɼ�������
				//[Omni_SDK]
				//�忨ȫ����Ϣ
				SOmnGlobalInfo glbInfo;
				memset(&glbInfo, 0, sizeof(glbInfo));

				//[Omni_SDK]
				//��ѯȫ����Ϣ�������ڼ���������м���Omni�忨���Լ����忨������Ϣ
				Omn_QueryGlobalInfo(&glbInfo);
				if (glbInfo.dwBoardNum == 0 || boardIndex >= glbInfo.dwBoardNum)
				{
					CASPAR_LOG(error) << print() << L" input board index: " << boardIndex << " error with board amount: " << glbInfo.dwBoardNum;
					return;
				}

				if (portIndex >= glbInfo.psBoardInfo[boardIndex].dwRecordDataPortNum)
				{
					CASPAR_LOG(error) << print() << L" input port index: " << portIndex << " error with port amount: " << glbInfo.psBoardInfo[boardIndex].dwRecordDataPortNum;
					return;
				}

				//[Omni_SDK]
				//���ھ��п��л��ӿڵİ忨��Ҫ�жϵ�ǰ�ӿڵ��������ֻ��Ϊ���뷽��ʱ���ܽ��вɼ���
				if (glbInfo.psBoardInfo[boardIndex].enumBoardType == Omn_BOARDTYPE_SER400 || glbInfo.psBoardInfo[boardIndex].enumBoardType == Omn_BOARDTYPE_SER400K)
				{
					SOmnBoardInterfaceInfo interfaceInfo;
					memset(&interfaceInfo, 0, sizeof(interfaceInfo));
					Omn_GetBoardParamEx(boardIndex, Omn_BOARDCONFIGTYPE_INTERFACE, &interfaceInfo);
					if (interfaceInfo.InterfaceDirection[portIndex] != 0 && portIndex < 4)
					{
						//Omn_Release();
						CASPAR_LOG(error) << print() << L" interface is output ";
						return;
					}
				}
				Om_HRESULT hr = Omn_ERR_FAILED;
				//----------
				//[Omni_SDK]
				//�����źŶ˿ڲ��������������źŵ���ʽ����Ϣ��
				//�ڲ�ѯ�˿ڲ���ǰ�����Ƚ��ñ�����ȫ��0�ķ�ʽ���г�ʼ������ͬ��
				SOmnInputSignalPortParam ispParam;
				memset(&ispParam, 0, sizeof(ispParam));

				//[Omni_SDK]
				//��ѯ�����źŶ˿ڲ�����
				hr = Omn_GetInputSignalPortParam(boardIndex, portIndex, &ispParam);

				//[Omni_SDK]
				//���������źŶ˿ڵ���ʽ��
				//ע���˴���Ӧע���Ƿ���Ҫ���������źŵ����ͣ����������ͺ�ʵ��
				//�����ź����Ͳ�һ�£������޷��ɼ������ݡ�
				vidStandard = GetVideoStandard();
				ispParam.enumVideoStandard = vidStandard;
				ispParam.bEnableDeinterlace =  Om_FALSE;//Om_TRUE;//
				//[Omni_SDK]
				//���������źŶ˿ڵĲ�����
				hr = Omn_SetInputSignalPortParam(boardIndex, portIndex, &ispParam);
				//[Omni_SDK]
				//�ɼ����ݶ˿ڲ����������ɼ��˿ڵ���ʽ����ɫ��ʽ����Ϣ��	��ʵ�����������
				//��ʼ��������
				SOmnRecordDataPortParam rdpParam;
				memset(&rdpParam, 0, sizeof(rdpParam));

				//[Omni_SDK]
				//��ѯ�ɼ����ݶ˿ڵ���ʽ
				hr = Omn_GetRecordDataPortParam(boardIndex, portIndex, &rdpParam);

				//[Omni_SDK]
				//���²ɼ����ݶ˿ڵ���ʽ����ɫ��ʽ
				rdpParamVideoStandard = rdpParam.enumVideoStandard = vidStandard;
				rdpParam.enumColorFormat = colorFmt;
				//[Omni_SDK]
				//���òɼ����ݶ˿ڵĲ�����
				hr = Omn_SetRecordDataPortParam(boardIndex, portIndex, &rdpParam);
#pragma endregion

				//[Omni_SDK]
				//׼���ɼ��ص�����ʹ�õ��Զ������
				callbackParam.boardIdx = boardIndex;
				callbackParam.portIdx = portIndex;

				unsigned int w, h;
				Omn_GetVidStdPara(vidStandard, w, h);
				callbackParam.width = w;
				callbackParam.height = h;
				callbackParam.colorFmt = colorFmt;
				callbackParam.pitch = colorFmt == OmnCOLORFORMAT_UYVY ? (w * 2) : (w * 4);
				callbackParam.pBufList = std::shared_ptr<CBufMng>(new CBufMng(callbackParam.pitch * h), [&](CBufMng* p)
				{
					delete p;
				});

				//[Omni_SDK]
				//ע��ɼ��ص�������������׼���ɼ���Դ��
				hr = Omn_PreRecord(boardIndex, portIndex, Om_FALSE, RecCallback, Om_NULL, &callbackParam);
				if (hr != Omn_SUCCESS)
				{
					//Omn_Release();
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(print() + L" Could not enable video input.")
						<< boost::errinfo_api_function("EnableVideoInput"));
				}

				//[Omni_SDK]
				//�����ɼ���
				hr = Omn_StartRecord(boardIndex, portIndex, Om_NULL);
				if (hr != Omn_SUCCESS)
				{
					CASPAR_LOG(error) << print() << L" Omn_StartRecord() returned failed: " << hr;
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(print() + L"  Omn_StartRecord() returned failed.")
						<< boost::errinfo_api_function("EnableVideoInput"));
				}
				_isRuning = _isRuningVideoStandardChanged = true;
				executor_.begin_invoke([=]() {ConstructionFrame(callbackParam.pBufList); }, task_priority::high_priority);
				executorVideoStandardChanged_.begin_invoke([=]() {VideoStandardChanged(); }, task_priority::high_priority);
			}

			//��ȡ��Ƶ��ʽ
			Omn_VIDEO_STANDARD GetVideoStandard()
			{
				SOmnMonitorInfo monitorInfo;
				memset(&monitorInfo, 0, sizeof(monitorInfo));
				monitorInfo.dwMonitorMask = 0xFFFF;
				//[Omni_SDK]
				//��ѯ��ǰ״̬��Ϣ
				Omn_QueryMonitorInfo(boardIndex, &monitorInfo);
				return monitorInfo.enumInputVideoStandard[portIndex];
			}

			~redlink_producer()
			{
				StopRecord();
			}
			core::monitor::subject& monitor_output()
			{
				return monitor_subject_;
			}
			boost::rational<int> get_out_framerate() const
			{
				return muxer_.out_framerate();
			}
			
			void StopRecord()
			{
				executor_.begin_invoke([=] 
				{
					_isRuning = false;
					Om_HRESULT hr = Omn_StopRecord(boardIndex, portIndex, Om_NULL);
					if (hr != Omn_SUCCESS)
					{
						CASPAR_LOG(error) << print() << L" Omn_StopRecord() returned failed: " << hr;
					}

					//[Omni_SDK]
					//�ͷŲɼ���Դ��
					Omn_CloseRecord(boardIndex, portIndex);
				}, task_priority::high_priority);
				executorVideoStandardChanged_.begin_invoke([=]
				{
					_isRuningVideoStandardChanged = false;
				}, task_priority::high_priority);
			}

			core::draw_frame get_frame()
			{
				core::draw_frame frame = last_frame_;

				if (!frame_buffer_.try_pop(frame))
					graph_->set_tag(diagnostics::tag_severity::WARNING, "late-frame");
				else
					last_frame_ = frame;

				graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size()) / static_cast<float>(frame_buffer_.capacity()));

				return frame;
			}
			std::wstring print() const
			{
				return L"redlink producer [" + boost::lexical_cast<std::wstring>(callbackParam.boardIdx) + L"|" + boost::lexical_cast<std::wstring>(callbackParam.portIdx) + L"]";
			}
			core::constraints& pixel_constraints()
			{
				return constraints_;
			}
		};
		
		class redlink_producer_proxy : public core::frame_producer_base
		{
			std::unique_ptr<redlink_producer>	producer_;
			const uint32_t						length_;
			executor							executor_;
		public:
			explicit redlink_producer_proxy(const core::video_format_desc& in_format_desc,
				const spl::shared_ptr<core::frame_factory>& frame_factory,
				const core::video_format_desc& out_format_desc,
				const core::audio_channel_layout& channel_layout, SCallbackParam params, const std::wstring& filter_str,uint32_t length)
				: executor_(L"redlink_producer[" + boost::lexical_cast<std::wstring>(params.boardIdx) + L"]")
				, length_(length)
			{
				auto ctx = core::diagnostics::call_context::for_thread();
				executor_.invoke([=]
				{
					core::diagnostics::call_context::for_thread() = ctx;
					producer_.reset(new redlink_producer(in_format_desc, params, frame_factory, out_format_desc, channel_layout, filter_str));
				});
			}
			~redlink_producer_proxy()
			{
				executor_.invoke([=]
				{
					producer_.reset();
				});
			}
			core::monitor::subject& monitor_output()
			{
				return producer_->monitor_output();
			}
			core::draw_frame receive_impl() override
			{
				return producer_->get_frame();
			}
			int producer_type()
			{
				//return FFMPEG_Resource::FFMPEG_DEVICE;
				return FFMPEG_Resource::FFMPEG_FILE;
			}
			core::constraints& pixel_constraints() override
			{
				return producer_->pixel_constraints();
			}
			std::wstring print() const override
			{
				return producer_->print();
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
			boost::rational<int> get_out_framerate() const
			{
				return producer_->get_out_framerate();
			}
		};
		void describe_producer(core::help_sink& sink, const core::help_repository& repo)
		{
			sink.short_description(L"Allows video sources to be input from RedLink");
			sink.syntax(L"NDI [source:string],{[grops:string] [ips:ip,ip] [showlocal: 1 or 0] [colorformat : rgb or yuv]}");
			sink.para()->text(L"Allows video sources to be input from redlink cards. Parameters:");
			sink.definitions()
				->item(L"board_index", L"The Redlink video card to use (See board order). Default is 0.")
				->item(L"port_index", L"The Redlink video card to use (See port order in board). Default is 0.")
				->item(L"color_format", L"The Redlink video card to use . Default is OmnCOLORFORMAT_UYVY.");
				
			sink.para()->text(L"Examples:");
			sink.example(L">> PLAY 1-10 REDLINK BOARDINDEX 0 PORTINDEX 3", L"Play using redlink device, boardindex is 1, poartindex is 4.");
			sink.example(L">> PLAY 1-10 REDLINK BOARDINDEX 0 PORTINDEX 3 COLORFORMAT UYVY", L"Play using redlink device, boardindex is 1, poartindex is 4, colorformat is UYVY.");
			sink.example(L">> PLAY 1-10 REDLINK BOARDINDEX 0 PORTINDEX 3 COLORFORMAT BGRA", L"Play using redlink device, boardindex is 1, poartindex is 4, colorformat is RGBA.");
		}

		spl::shared_ptr<core::frame_producer> create_producer(const core::frame_producer_dependencies& dependencies, const std::vector<std::wstring>& params)
		{
			if (params.empty() || !boost::iequals(params.at(0), "REDLINK"))
			{
				return core::frame_producer::empty();
			}

			auto board_index = get_param(L"BOARDINDEX", params, -1);
			if (board_index == -1)
				board_index = boost::lexical_cast<int>(params.at(1));
			auto port_index = get_param(L"PORTINDEX", params, -1); // TODO����ʱ�Ȳ��ж�
			SCallbackParam callparams;
			callparams.portIdx = port_index;
			callparams.boardIdx = board_index;
			callparams.colorFmt = OmnCOLORFORMAT_UYVY;
			if (contains_param(L"COLORFORMAT", params))
			{
				callparams.colorFmt = get_param(L"COLORFORMAT", params) == L"UYVY" ? OmnCOLORFORMAT_UYVY : OmnCOLORFORMAT_BGRA;
			}

			auto filter_str = get_param(L"FILTER", params);
			auto length = get_param(L"LENGTH", params, std::numeric_limits<uint32_t>::max());
			auto in_format_desc = core::video_format_desc(get_param(L"FORMAT", params, L"INVALID"));	//TODO: ��ʱ�Ȳ���

			if (in_format_desc.format == core::video_format::invalid)
				in_format_desc = dependencies.format_desc;

			auto channel_layout_spec = get_param(L"CHANNEL_LAYOUT", params);
			auto channel_layout = *core::audio_channel_layout_repository::get_default()->get_layout(L"stereo");

			if (!channel_layout_spec.empty())
			{
				auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(channel_layout_spec);

				if (!found_layout)
					CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout not found."));

				channel_layout = *found_layout;
			}

			boost::ireplace_all(filter_str, L"DEINTERLACE_BOB", L"YADIF=1:-1");
			boost::ireplace_all(filter_str, L"DEINTERLACE_LQ", L"SEPARATEFIELDS");
			boost::ireplace_all(filter_str, L"DEINTERLACE", L"YADIF=0:-1");

			auto producer = spl::make_shared<redlink_producer_proxy>(
				in_format_desc,
				dependencies.frame_factory,
				dependencies.format_desc,
				channel_layout,
				callparams,
				filter_str,
				length);

			auto get_source_framerate = [=] { return producer->get_out_framerate(); };
			auto target_framerate = dependencies.format_desc.framerate;

			return core::create_destroy_proxy(core::create_framerate_producer(
				producer,
				get_source_framerate,
				target_framerate,
				dependencies.format_desc.field_mode,
				dependencies.format_desc.audio_cadence));
		}
	}
}



