#include "matrox_consumer.h"
#include "../matrox_interface_consumer.h"
#include "../matrox_2022_playback.h"
#include "../common.h"
#include <assert.h>
#include <time.h>

#include <common/memcpy.h>

#include <common/future.h>
#include <common/except.h>
#include <common/param.h>
#include <common/os/general_protection_fault.h>

#include <core/video_format.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/consumer/frame_consumer.h>

#include <core/help/help_sink.h>

#include <boost/algorithm/string.hpp>

#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>

#include <vector>



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
		
		
		struct AudioSampleCalc
		{
			AudioSampleCalc()
			{
				Reset();
			}
			double m_dblDiff;
			int NextSamples(double _dblFrameRate, int _nAudioFreq)
			{
				double dblNeed = (double)_nAudioFreq / _dblFrameRate;
				int nSamples = (int)(dblNeed + m_dblDiff);
				m_dblDiff += (dblNeed - nSamples);
				return nSamples;
			}

			void Reset()
			{
				m_dblDiff = 0;
			}
		};
		struct matrox_consumer : boost::noncopyable
 		{
			//////////////////////////////////////////
			

			//const MatroxNeedParameters						m_Parameters;
			consumer_need										need_;
			//mvsParameters										m_Parameters_consumer;
			core::video_format_desc								format_desc_;
  			tbb::atomic<bool>									m_isRunning;
  			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;
			boost::thread										thread_;
			AudioSampleCalc										m_audCalc;
			core::audio_channel_layout							m_InputChannelLayout;
			core::audio_channel_layout							m_OutChannelLayout;
			std::shared_ptr<SwsContext>							sws_video;
			std::shared_ptr<SwrContext>							swr_;
			std::shared_ptr<matrox_interface_consumer>			pjsdiplay;
			std::shared_ptr<matrox_2022_playback>				pj2022play;
		public:

			std::future<bool> send(core::const_frame frame)
			{
				frame_buffer_.try_push(frame);
				return make_ready_future(m_isRunning.load());
			}
			std::wstring print() const
			{
				return boost::lexical_cast<std::wstring>(need_.sdi);
			}

			matrox_consumer(
				const consumer_need need,
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& OutputChannelLayout,
				const core::audio_channel_layout& InputChannelLayout)
				: m_InputChannelLayout(InputChannelLayout)
				,m_OutChannelLayout(OutputChannelLayout== core::audio_channel_layout::invalid() ? InputChannelLayout: OutputChannelLayout)
				, need_(need)
				, format_desc_(format_desc)
			{
				if (need.type == type_mid::SDI_TYPE)
				{
					pjsdiplay = std::make_shared< matrox_interface_consumer>(need, format_desc.format, m_OutChannelLayout.num_channels);
				}
				else if (need.type == type_mid::IP_TYPE)
				{
					pj2022play = std::make_shared< matrox_2022_playback>(need, format_desc.format, m_OutChannelLayout.num_channels);
				}
				CASPAR_LOG(info) << L" matrox consumer creat";
				int intype = (int)av_get_default_channel_layout(m_InputChannelLayout.num_channels);//AV_CH_LAYOUT_MONO
				int outtype = (int)av_get_default_channel_layout(m_OutChannelLayout.num_channels);//输入声道
				frame_buffer_.set_capacity(1);
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

				
				m_isRunning = true;
				thread_ = boost::thread([this] {run();});
 			}
			~matrox_consumer()
			{
				//队列创建
				if (frame_buffer_.size())
				{
					frame_buffer_.clear();
				}
			}


			void run()
			{
				while (m_isRunning)
				{

					core::const_frame frame;
					if (!frame_buffer_.try_pop(frame))
					{
						boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
						continue;
					}
					
					_ProcessVanc(frame);
					
					
				}
			}
			void _ProcessVanc(core::const_frame &frame)//40ms
			{
				// Get the vanc packets from the host node.
				void * pvideo = NULL;
				void * pvideo1 = NULL;
				void * paudio = NULL;
				void * paudio1 = NULL;

				//逐行调用一次，隔行两次

				
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
					int nAR = -1;
					int nCmd = -1;
					if (frame.afd_command())
					{
						nAR = frame.afd_command()->afd_aspect_ratio_;
						nCmd = frame.afd_command()->afd_command_;
					}
					pjsdiplay->_ProcessVanc(pvideo, paudio, pvideo1, paudio1, nAR, nCmd);
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
					
					pj2022play->send(pvideo, paudio, pvideo1, paudio1);
				}
			}
			
			void get_top_frame(core::const_frame &frame, void **pvideo, void **pvideo1, void **paudio, void **paudio1)
			{
				int width = (int)frame.width();
				int height = (int)frame.height();

				if (!sws_video)
				{
					sws_video.reset(
						sws_getContext(
							width,
							height,
							AV_PIX_FMT_BGRA,
							width,
							height,
							AV_PIX_FMT_YUYV422,
							SWS_BICUBIC,
							nullptr,
							nullptr,
							nullptr
						),
						sws_freeContext);
					if (sws_video == nullptr)
						BOOST_THROW_EXCEPTION(caspar::caspar_exception() << caspar::msg_info(L"Cannot initialize the conversion context"));
				}
				unsigned long ulSizeToRead = width * 2 * height;

				uint8_t *rgbbuf[1];
				uint8_t *outbuf[3];
				int inlinesize[1] = { width * 4 };//ROW BYTE
				int outlinesize[1] = { width * 2 };//ROW BYTE

				rgbbuf[0] = (uint8_t *)malloc(width * 4 * height);
				outbuf[0] = (uint8_t *)malloc(ulSizeToRead);

				/*tbb::parallel_for(0, height, 1, [&](int y)
				{
					caspar::fast_memcpy(
						reinterpret_cast<char*>(rgbbuf[0]) + y *width * 4,
						(frame.image_data().begin()) + y * width * 4,
						width * 4
					);
				});*/

				memcpy(reinterpret_cast<char*>(rgbbuf[0]), (frame.image_data().begin()),height*width*4);

				sws_scale(sws_video.get(), rgbbuf, inlinesize,
					0, height, outbuf, outlinesize);

				////场消隐
				//char pall_buf[96] = { 0 };
				//memset(pall_buf, 0, 96);
				void * pBuffer = (uint8_t*)malloc((width * 2 + 100)*height / 2);
				void * pBuffer1 = (uint8_t*)malloc((width * 2 + 100)*height / 2);
				uint8_t*p = (uint8_t*)pBuffer;
				uint8_t*p1 = (uint8_t*)pBuffer1;
				for (int i = 0;i < height;i++)
				{
					////场消隐
					//if (width == 720 && (height == 288 *2|| height == 243*2))
					//{
					//	if (i % 2)
					//	{
					//		memcpy(p1, outbuf[0] + i*width * 2, width * 2);
					//		p1 += width * 2;
					//		memcpy(p1, pall_buf, 96);
					//		p1 += 96;
					//	}
					//	else
					//	{
					//		memcpy(p, outbuf[0] + i*width * 2, width * 2);
					//		p += (width * 2);
					//		memcpy(p, pall_buf, 96);
					//		p += 96;
					//	}
					//}
					//else
					{
						if (i % 2)//second
						{
							memcpy(p1, outbuf[0] + i*width * 2, width * 2);
							p1 += width * 2;
						}
						else
						{
							memcpy(p, outbuf[0] + i*width * 2, width * 2);
							p += width * 2;
						}
					}
				}

				//audio
				//int audio_frame_size = (int)((boost::iterator_range<const int32_t*>)frame.audio_data()).size() * sizeof(int32_t);
				void * source = (char *)malloc(frame.audio_data().size() * 4);
				
				void * pAudioBuffer = (char *)malloc(m_OutChannelLayout.num_channels * 48000 / 25 * 4);
				void * pAudioBuffer1 = (char *)malloc(m_OutChannelLayout.num_channels * 48000 / 25 * 2);
				int outsize = m_OutChannelLayout.num_channels * 48000 / 25 * 4;
				caspar::array<const int32_t>::iterator it;

				it = frame.audio_data().begin();
				int* p_ch = (int *)source;
				for (int sample_no = 0; sample_no < frame.audio_data().size();sample_no++)
				{
					p_ch[sample_no] = (int)*it;
					/*if (*it != 0)
					{
						int s = *it;
					}*/
					it++;
				}
				const uint8_t **in = const_cast<const uint8_t**>((uint8_t**)&source);
				uint8_t *out[] = { reinterpret_cast<uint8_t*>((uint8_t*)pAudioBuffer) };

				const auto channel_samples = swr_convert(
					swr_.get(),
					out,
					outsize,
					in,
					48000 / 25);

				memcpy(pAudioBuffer1, (uint8_t*)pAudioBuffer + m_OutChannelLayout.num_channels * 48000 / 25 * 2, m_OutChannelLayout.num_channels * 48000 / 25 * 2);
				*paudio = (uint8_t*)pAudioBuffer;
				*paudio1 = (uint8_t*)pAudioBuffer1;
				*pvideo1 = pBuffer1;
				*pvideo = pBuffer;
				free(source);
				free(rgbbuf[0]);
				free(outbuf[0]);
			}

			void get_frame(core::const_frame &frame, void **pvideo, void **paudio)
			{
				int width = (int)frame.width();
				int height = (int)frame.height();
				if (!sws_video)
				{
					sws_video.reset(
						sws_getContext(
							width,
							height,
							AV_PIX_FMT_BGRA,
							width,
							height,
							AV_PIX_FMT_YUYV422,
							SWS_BICUBIC,
							nullptr,
							nullptr,
							nullptr
						),
						sws_freeContext);
					if (sws_video == nullptr)
						BOOST_THROW_EXCEPTION(caspar::caspar_exception() << caspar::msg_info(L"Cannot initialize the conversion context"));
				}
				uint8_t *inbuf[1];
				uint8_t *outbuf[1];
				int inlinesize[1] = { width * 4 };
				int outlinesize[1] = { width * 2 };


				inbuf[0] = (uint8_t *)malloc(width*height * 4);
				outbuf[0] = (uint8_t *)malloc(width*height * 4);//全场逐行


				tbb::parallel_for(0, height, 1, [&](int y)
				{
					std::memcpy(
						reinterpret_cast<char*>(inbuf[0]) + y *width * 4,
						(frame.image_data().begin()) + y * width * 4,
						width * 4
					);
				});

				memcpy(reinterpret_cast<char*>(inbuf[0]), (frame.image_data().begin()),height*width*4);

				sws_scale(sws_video.get(), inbuf, inlinesize,
					0, height, outbuf, outlinesize);
				*pvideo = outbuf[0];

				//audio
				//int audio_frame_size = (int)((boost::iterator_range<const int32_t*>)frame.audio_data()).size() * sizeof(int32_t);
				void * source = (char *)malloc(frame.audio_data().size() * 4);
				void * pAudioBuffer = (char *)malloc(m_OutChannelLayout.num_channels * 48000 / 25 * 4);
				int outsize = m_OutChannelLayout.num_channels * 48000 / 25 * 4;
				caspar::array<const int32_t>::iterator it;

				it = frame.audio_data().begin();
				int* p_ch = (int *)source;
				for (int sample_no = 0; sample_no < frame.audio_data().size();sample_no++)
				{
					p_ch[sample_no] = (int)*it;
					/*if (*it != 0)
					{
						int s = *it;
					}*/
					it++;
				}
				const uint8_t **in = const_cast<const uint8_t**>((uint8_t**)&source);
				uint8_t *out[] = { reinterpret_cast<uint8_t*>((uint8_t*)pAudioBuffer) };

				const auto channel_samples = swr_convert(
					swr_.get(),
					out,
					outsize,
					in,
					48000 / 25);
				*paudio = (uint8_t*)pAudioBuffer;


				free(source);
				free(inbuf[0]);
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

			~matrox_consumer_proxy()
			{
				if (consumer_)
				{
					auto str = print();
					consumer_.reset();
					CASPAR_LOG(info) << str << L" Successfully Uninitialized.";
				}
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
			/*MatroxNeedParameters Parameters;
			if (contains_param(L"card", params))
				Parameters.stCard = boost::lexical_cast<int>(get_param(L"card", params));
			if (contains_param(L"sdi", params))
				Parameters.stSdi = boost::lexical_cast<int>(get_param(L"sdi", params));
			if (contains_param(L"ratio", params))
				Parameters.stRatio =get_param(L"ratio", params);
			if (contains_param(L"vanc-output", params))
				Parameters.stIsVanc = boost::lexical_cast<int>(get_param(L"vanc-output", params))==1?true:false;*/

				/*if (contains_param(L"channel-layout", params))
				{
					auto channel_layout = get_param(L"channel-layout", params);
					if (!channel_layout.empty())
					{
						CASPAR_SCOPED_CONTEXT_MSG("/channel-layout")

							auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(channel_layout);

						if (!found_layout)
							CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout " + channel_layout + L" not found."));

						Parameters.stNeedAudioChannelforPlay = *found_layout;
					}
				}
				if (contains_param(L"addr", params))

				return spl::make_shared<matrox_consumer_proxy>(Parameters);*/

			consumer_need need;
			if (contains_param(L"card", params))
				need.card = boost::lexical_cast<int>(get_param(L"card", params));
			if (contains_param(L"sdi", params))
				need.sdi = boost::lexical_cast<int>(get_param(L"sdi", params));
			if (contains_param(L"ratio", params))
				need.ratio = get_param(L"ratio", params);
			if (contains_param(L"vanc", params))
				need.vanc = boost::lexical_cast<int>(get_param(L"vanc-output", params)) == 1 ? true : false;

			if (contains_param(L"key", params))
				need.key = boost::lexical_cast<int>(get_param(L"key", params)) == 1 ? true : false;

			if (contains_param(L"addr", params))
			{
				need.type = type_mid::IP_TYPE;
				need.addr = get_param(L"addr", params);
				need.port = boost::lexical_cast<int>(get_param(L"port", params));
				need.localhost = get_param(L"localhost",params);
			}
			else
			{
				need.type = type_mid::SDI_TYPE;
			}


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
 		//	MatroxNeedParameters Parameters;
			//Parameters.stCard = ptree.get(L"card", Parameters.stCard);
			//Parameters.stRatio = ptree.get(L"ratio", Parameters.stRatio);
			//Parameters.stSdi = ptree.get(L"sdi", Parameters.stSdi);
			//Parameters.stIsVanc = ptree.get(L"vanc-output", Parameters.stIsVanc);//config vanc
			//Parameters.stIsKey = ptree.get(L"key", Parameters.stIsKey);
			
			consumer_need need;

			need.addr=ptree.get(L"card", 0);
			need.sdi = ptree.get(L"card",0);
			need.ratio = ptree.get(L"ratio", L"16:9");
			need.vanc = ptree.get(L"vanc", false);
			need.vanc = ptree.get(L"key", false);

			need.addr = ptree.get(L"addr", L"");
			if (!need.addr.empty())
			{
				need.type = type_mid::IP_TYPE;
				need.port = ptree.get(L"port", 0);
				if (need.port==0)
				{
					CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"port " + boost::lexical_cast<std::wstring>(need.port) + L" error"));
				}
				need.localhost = ptree.get(L"localhost",L"192.168.1.100");
			}
			else {
				need.type = type_mid::SDI_TYPE;
			}

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




