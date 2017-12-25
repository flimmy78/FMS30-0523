#include "matrox_consumer.h"
#include "../common.h"
#include <assert.h>
#include <time.h>

#include <common/future.h>
#include <common/except.h>
#include <common/param.h>
#include <common/os/general_protection_fault.h>
#include <common/diagnostics/graph.h>

#include <core/video_format.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/consumer/frame_consumer.h>

#include <core/help/help_sink.h>

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>
#include <vector>

#include "../matrox_2022_playback.h"//必须位于boost下方，否则编译linux版本时matrox与boost库冲突
#include "../matrox_sdi_playback.h"

//intel ipp
#include <ippcc.h>

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif	


namespace caspar {
	namespace matrox {

		struct matrox_consumer : boost::noncopyable
 		{
			//////////////////////////////////////////
			
			const spl::shared_ptr<diagnostics::graph>			graph_;
			caspar::timer										tick_timer_;

			//const MatroxNeedParameters						m_Parameters;
			consumer_need										need_;
			//mvsParameters										m_Parameters_consumer;
			core::video_format_desc								format_desc_;
  			tbb::atomic<bool>									is_running_;
  			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;
			boost::thread										thread_;
			core::audio_channel_layout							m_InputChannelLayout;
			core::audio_channel_layout							m_OutChannelLayout;
			std::shared_ptr<SwsContext>							sws_video;
			std::shared_ptr<SwrContext>							swr_;
			std::shared_ptr<matrox_sdi_playback>				pjsdiplay;
			std::shared_ptr<matrox_2022_playback>				pj2022play;

			std::map<std::string, std::string>					options_;//2022 args
		public:

			std::future<bool> send(core::const_frame frame)
			{
				graph_->set_value("tick-time", tick_timer_.elapsed()*format_desc_.fps*0.5);
				if (!frame_buffer_.try_push(frame))
					graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
				graph_->set_text(print());
				graph_->set_value("buffer-frames", ((double)frame_buffer_.size()) / frame_buffer_.capacity());
				tick_timer_.restart();

				return make_ready_future(is_running_.load());
			}
			std::wstring print() const
			{
				return L"matrox_consumer[" + boost::lexical_cast<std::wstring>(need_.card) + L"|" + boost::lexical_cast<std::wstring>(need_.sdi) + L"|" + boost::lexical_cast<std::wstring>(frame_buffer_.size()) + L"]";
			}

			matrox_consumer(
				const consumer_need need,
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& OutputChannelLayout,
				const core::audio_channel_layout& InputChannelLayout)
				: m_InputChannelLayout(InputChannelLayout)
				, m_OutChannelLayout(OutputChannelLayout== core::audio_channel_layout::invalid() ? InputChannelLayout: OutputChannelLayout)
				, need_(need)
				, format_desc_(format_desc)
			{
				std::string options = u8(boost::to_lower_copy(need.args));
				for (auto it =
					boost::sregex_iterator(
						options.begin(),
						options.end(),
						boost::regex("-(?<NAME>[^-\\s]+)(\\s+(?<VALUE>[^\\s]+))?"));
					it != boost::sregex_iterator();
					++it)
				{
					options_[(*it)["NAME"].str()] = (*it)["VALUE"].matched ? (*it)["VALUE"].str() : "";
				}

				if (need.type == type_mid::SDI_TYPE)
				{
					pjsdiplay = std::make_shared< matrox_sdi_playback>(need, format_desc.format, m_OutChannelLayout.num_channels, options_);
				}
				else if (need.type == type_mid::IP_TYPE)
				{
					pj2022play = std::make_shared< matrox_2022_playback>(need, format_desc.format, m_OutChannelLayout.num_channels, options_);
				}

				int intype = (int)av_get_default_channel_layout(m_InputChannelLayout.num_channels);//AV_CH_LAYOUT_MONO
				int outtype = (int)av_get_default_channel_layout(m_OutChannelLayout.num_channels);//输入声道
				frame_buffer_.set_capacity(4);
				swr_ = {
					swr_alloc_set_opts(
						nullptr,
						outtype,
						AV_SAMPLE_FMT_S32,
						48000,
						intype ,
						AV_SAMPLE_FMT_S32,
						48000,
						0,
						nullptr),
					[](SwrContext* p)
				{
					swr_free(&p);
				}
				};
				swr_init(swr_.get());

				graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
				graph_->set_color("pushframe-time", diagnostics::color(0.1f, 1.0f, 0.1f));
				graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
				graph_->set_color("buffer-frames", diagnostics::color(0.7f, 0.4f, 0.4f));
				graph_->set_text(print());
				diagnostics::register_graph(graph_);

				is_running_ = true;
				thread_ = boost::thread([this] {run();});
 			}
			~matrox_consumer()
			{
				is_running_ = false;
				frame_buffer_.try_push(core::const_frame::empty());
				thread_.join();
			}


			void run()
			{
				caspar::timer pushframe_timer;
				while (is_running_)
				{

					core::const_frame frame;
					if (!frame_buffer_.try_pop(frame))
					{
						boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
						continue;
					}
					pushframe_timer.restart();
					_ProcessVanc(frame);
					graph_->set_value("pushframe-time", pushframe_timer.elapsed() * format_desc_.fps * 0.5);
				}
			}
			void _ProcessVanc(core::const_frame &frame)
			{
				void * pvideo = NULL;
				void * pvideo1 = NULL;
				void * paudio = NULL;
				void * paudio1 = NULL;
				
				if (need_.type == type_mid::SDI_TYPE)
				{
					if (pjsdiplay->_IsFieldBased())
					{
						get_top_frame(frame, &pvideo, &pvideo1, &paudio, &paudio1);
					}
					else
					{
						get_frame(frame, &pvideo, &paudio);
					}
					pjsdiplay->send(pvideo, pvideo1, paudio, paudio1);
				}
				else if (need_.type == type_mid::IP_TYPE)
				{

					if (pj2022play->_IsFieldBased())
					{
						get_top_frame(frame, &pvideo, &pvideo1, &paudio, &paudio1);
					}
					else
					{
						get_frame(frame, &pvideo, &paudio);
					}
					
					pj2022play->send(pvideo, pvideo1, paudio, paudio1);
				}
			}
			void get_frame(core::const_frame &frame, void **pvideo, void **paudio)
			{
				int32_t width = frame.width();
				int32_t height = frame.height();

				//video intel BGRA To YUY2(YUYV422)	
				IppStatus ippStatus;
				uint8_t* outbuf = (uint8_t *)malloc(width * height * 2);
				Ipp8u* pDst = (Ipp8u*)outbuf;
				ippStatus = ippiBGRToYCbCr422_8u_AC4C2R(frame.image_data().begin(), width * 4, pDst, width * 2, { width, height });
				*pvideo = outbuf;

				//audio  32bit transfer to matrox 32bit-24 bit valid
				uint8_t * audio_buf = (uint8_t*)malloc(frame.audio_data().size() * 4);
				caspar::array<const int32_t>::iterator it;
				it = frame.audio_data().begin();
				int32_t* p_ch = (int32_t*)audio_buf;
				for (int sample_no = 0; sample_no < frame.audio_data().size(); sample_no++)
				{
					p_ch[sample_no] = (int32_t(((*it) / (double)0x7fffffff) * 0x7fffff)) << 8;
					it++;
				}

				*paudio = audio_buf;
			}

			void get_top_frame(core::const_frame &frame, void **pvideo, void **pvideo1, void **paudio, void **paudio1)
			{
				int32_t width = frame.width();
				int32_t height = frame.height();

				//video  intel BGRA To YUY2(YUYV422)	
				IppStatus ippStatus;
				uint8_t* outbuf = (uint8_t *)malloc(width * height * 2);
				Ipp8u* pDst = (Ipp8u*)outbuf;
				ippStatus = ippiBGRToYCbCr422_8u_AC4C2R(frame.image_data().begin(), width * 4, pDst, width * 2, { width, height });
				*pvideo = outbuf;

				void * pTop = (uint8_t*)malloc(width *height * 2 / 2);
				void * pBottom = (uint8_t*)malloc(width *height * 2 / 2);
				uint8_t*p = (uint8_t*)pTop;
				uint8_t*p1 = (uint8_t*)pBottom;
				for (int32_t i = 0; i < height; i++)
				{
					if (i % 2)
					{
						memcpy(p1, outbuf + i*width * 2, width * 2);
						p1 += width * 2;
					}
					else
					{
						memcpy(p, outbuf + i*width * 2, width * 2);
						p += width * 2;
					}
				}
				*pvideo = pTop;
				*pvideo1 = pBottom;
				free(outbuf);

				//audio  32bit transfer to matrox 32bit-24bit valid
				uint8_t * audio_buf = (uint8_t*)malloc(frame.audio_data().size() * 4);
				caspar::array<const int32_t>::iterator it;
				it = frame.audio_data().begin();
				int32_t* p_ch = (int32_t*)audio_buf;
				for (int sample_no = 0; sample_no < frame.audio_data().size(); sample_no++)
				{
					p_ch[sample_no] = (int32_t(((*it) / (double)0x7fffffff) * 0x7fffff)) << 8;
					it++;
				}
				uint8_t* audio_buf1 = (uint8_t*)malloc(m_OutChannelLayout.num_channels * 48000 / 25 * 2);
				memcpy(audio_buf1, (uint8_t*)audio_buf + m_OutChannelLayout.num_channels * 48000 / 25 * 2, m_OutChannelLayout.num_channels * 48000 / 25 * 2);
				*paudio = audio_buf;
				*paudio1 = audio_buf1;
			}
		};

		struct matrox_consumer_proxy : public core::frame_consumer
		{
 			core::monitor::subject			monitor_subject_;
 			const consumer_need		need_;
 			std::unique_ptr<matrox_consumer> consumer_;
			const core::audio_channel_layout channel_layout_out;
 		public:
			matrox_consumer_proxy(consumer_need need, const core::audio_channel_layout& channel_layout )
				:need_(need)
				, channel_layout_out(channel_layout)
			{
			}

			// Methods
			std::future<bool> send(core::const_frame frame) override
			{
				return consumer_->send(frame);
			}
			void initialize(const core::video_format_desc& format_desc, const core::audio_channel_layout& channel_layout_in, int channel_index) override
			{
				consumer_.reset();
				consumer_.reset(new matrox_consumer(need_, format_desc, channel_layout_out,channel_layout_in));

				//CASPAR_LOG(info) << print() << L" Successfully Initialized.";
			}

			// monitor::observable
			core::monitor::subject& monitor_output()
			{
				return monitor_subject_;
			}
			
			// Properties

			std::wstring print() const override
			{
				return consumer_ ? consumer_->print() : L"[matrox consumer]";
			}

			std::wstring name() const override
			{
				return L"matrox";
			}

			boost::property_tree::wptree info() const override
			{
				boost::property_tree::wptree info;
				info.add(L"type", L"matrox");
				return info;
			}

			bool has_synchronization_clock() const override
			{
				return false;
			}

			int buffer_depth() const override// -1 to not participate in frame presentation synchronization
			{
				return 2;
			}

			int index() const override
			{
				return 7500+ boost::lexical_cast<int>(need_.sdi)+ boost::lexical_cast<int>(need_.card)*10;
			}

			int64_t presentation_frame_age_millis() const override
			{
				return 1;
			}

		};

		void describe_consumer(core::help_sink& sink, const core::help_repository& repo)
		{
			sink.short_description(L"matrox Consumer");
		}

		spl::shared_ptr<core::frame_consumer> create_consumer(const std::vector<std::wstring>& params, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			if (params.size() < 1 || !boost::iequals(params.at(0), L"matrox"))
				return core::frame_consumer::empty();

			consumer_need need;
			if (contains_param(L"card", params))
				need.card = boost::lexical_cast<int>(get_param(L"card", params));
			if (contains_param(L"sdi", params))
				need.sdi = boost::lexical_cast<int>(get_param(L"sdi", params));
			if (contains_param(L"ratio", params))
				need.ratio = get_param(L"ratio", params);
			if (contains_param(L"vanc", params))
				need.vanc = boost::lexical_cast<int>(get_param(L"vanc", params)) == 1 ? true : false;
			if (contains_param(L"key", params))
				need.key = boost::lexical_cast<int>(get_param(L"key", params)) == 1 ? true : false;

			if (contains_param(L"type", params))
			{
				auto type = get_param(L"type", params);
				type = boost::to_lower_copy(type);
				if (type == L"sdiip-out")
	 			{
	 				need.type = type_mid::IP_TYPE;
	 			}
	 			else if (type == L"sdi-out")
	 			{
	 				need.type = type_mid::SDI_TYPE;
	 			}
	 
			}
			if (type_mid::IVLID == need.type)
			{
				CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"output type invalid!"));
			}

			if (contains_param(L"args", params)) need.args = get_param(L"args", params);

			auto channel_str = get_param(L"channel-layout", params);
			core::audio_channel_layout channel_layout = *core::audio_channel_layout_repository::get_default()->get_layout(L"stereo");;
			if (!channel_str.empty())
			{
				CASPAR_SCOPED_CONTEXT_MSG("/channel-layout")

					auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(channel_str);

				if (!found_layout)
					CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout " + channel_str + L" not found."));

				channel_layout = *found_layout;
			}
			return spl::make_shared<matrox_consumer_proxy>(need, channel_layout);

		}

		spl::shared_ptr<core::frame_consumer> create_preconfigured_consumer(const boost::property_tree::wptree& ptree, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			consumer_need need;
			need.card=ptree.get(L"card", 0);
			need.sdi = ptree.get(L"sdi",0);
			need.ratio = ptree.get(L"ratio", L"16:9");
			need.vanc = ptree.get(L"vanc", false);
			need.key = ptree.get(L"key", false);

			auto type = ptree.get(L"type", L"");
			type = boost::to_lower_copy(type);
			if (type == L"sdiip-out")
			{
				need.type = type_mid::IP_TYPE;
			}
			else if (type == L"sdi-out")
			{
				need.type = type_mid::SDI_TYPE;
			}
			if (type_mid::IVLID == need.type)
			{
				CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"output type invalid!"));
			}
			need.args = ptree.get(L"args", L"");

			auto channel_str = ptree.get_optional<std::wstring>(L"channel-layout");
			core::audio_channel_layout channel_layout=*core::audio_channel_layout_repository::get_default()->get_layout(L"stereo");;
			if (channel_str)
			{
				CASPAR_SCOPED_CONTEXT_MSG("/channel-layout")

					auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(*channel_str);

				if (!found_layout)
					CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout " + *channel_str + L" not found."));

				channel_layout = *found_layout;
			}
			return spl::make_shared<matrox_consumer_proxy>(need,channel_layout);
		}
}}




