//
// Created by zibj 2017/02/09.
//

#include "mainconcept_consumer.h"
#include <mcfourcc.h>
#include <mccolorspace.h>
#include <muxer/muxer_base.h>
#include <render/render_base.h>
#include <encoder/enc_base.h>

#include <common/future.h>
#include <common/param.h>
#include <common/ptree.h>
#include <common/os/general_protection_fault.h>
#include <common/diagnostics/graph.h>
#include <common/env.h>
#include <common/executor.h>

#include <core/video_format.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/consumer/frame_consumer.h>
#include <core/help/help_sink.h>

#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/regex.hpp>

#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4245)
#include <boost/crc.hpp>
#pragma warning(pop)

#include <vector>

extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libswresample/swresample.h>
}

namespace caspar {
	namespace mainconcept {

		struct mainconcept_consumer : boost::noncopyable
 		{
			const spl::shared_ptr<diagnostics::graph>			graph_;
			caspar::timer										tick_timer_;

			core::monitor::subject								subject_;
			std::string											path_;
			boost::filesystem::path                             full_path_;

			std::map<std::string, std::string>					options_;
			std::map<std::string, std::string>					options2_;//用于多音轨输出时，存储第二路音轨的参数

			core::video_format_desc								in_video_format_;
			core::audio_channel_layout							in_channel_layout_ = core::audio_channel_layout::invalid();
			std::shared_ptr<SwrContext>							swr_;

			tbb::atomic<bool>									is_running_;
  			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;

			boost::thread										thread_;

			executor											video_encoder_executor_;
			executor											audio_encoder_executor_;

			int                                                 framerate_interval_ = in_video_format_.fps > 0 ? in_video_format_.fps : 25;
			int                                                 framerate_count_ = 0;
			caspar::timer                                       framerate_timer_;
			double                                              framerate_ = framerate_interval_;
			//
			std::map<std::string, std::string>			path_options_;
			muxer_base *                                 muxer_;
			render_base *                                render_;
			enc_base*                                    video_enc_;
			std::map<uint32_t,enc_base*>                 audio_encs_;
			//
			int32_t										line_size;
			int32_t                                     img_start;
			int32_t                                     fourcc;
		public:

			std::future<bool> send(core::const_frame frame)
			{
				graph_->set_value("tick-time", tick_timer_.elapsed()*in_video_format_.fps*0.5);
 				if (!frame_buffer_.try_push(frame))
 					graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
  				graph_->set_text(print());
 				graph_->set_value("buffer-frames", ((double)frame_buffer_.size()) / frame_buffer_.capacity());
 				tick_timer_.restart();
 
 				return make_ready_future(is_running_.load());
			}
		
			std::wstring print() const
			{
				return L"mainconcept_consumer[" + u16(path_) + L"|" + boost::lexical_cast<std::wstring>(frame_buffer_.size()) + L"|" + boost::lexical_cast<std::wstring>((float)framerate_) + L"]";
			}

			mainconcept_consumer(std::string path,std::string options,std::string options2)
				: path_(path)
				, full_path_(path)
				, audio_encoder_executor_(print() + L" audio_encoder")
				, video_encoder_executor_(print() + L" video_encoder")
				, muxer_(nullptr)
				, render_(nullptr)
				, video_enc_(nullptr)
  			{
				frame_buffer_.set_capacity(4);
				is_running_ = true;

				options = boost::to_lower_copy(options);
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

				options2 = boost::to_lower_copy(options2);
				for (auto it =
					boost::sregex_iterator(
						options2.begin(),
						options2.end(),
						boost::regex("-(?<NAME>[^-\\s]+)(\\s+(?<VALUE>[^\\s]+))?"));
					it != boost::sregex_iterator();
					++it)
				{
					options2_[(*it)["NAME"].str()] = (*it)["VALUE"].matched ? (*it)["VALUE"].str() : "";
				}

 			}
			void initialize(
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& channel_layout)
			{
				in_video_format_ = format_desc;
				in_channel_layout_ = channel_layout;
				framerate_ = framerate_interval_ = in_video_format_.fps;

				graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
				graph_->set_color("pushframe-time", diagnostics::color(0.1f, 1.0f, 0.1f));
				graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
				graph_->set_color("buffer-frames", diagnostics::color(0.7f, 0.4f, 0.4f));
				graph_->set_text(print());
				diagnostics::register_graph(graph_);

				//32bit transfer to 16bit
				int intype = static_cast<int>(av_get_default_channel_layout(in_channel_layout_.num_channels));
				int outtype = static_cast<int>(av_get_default_channel_layout(in_channel_layout_.num_channels));
				swr_ = {
					swr_alloc_set_opts(
						nullptr,
						outtype,
						AV_SAMPLE_FMT_S16,
						in_video_format_.audio_sample_rate,
						intype ,
						AV_SAMPLE_FMT_S32,
						in_video_format_.audio_sample_rate,
						0,
						nullptr),
					[](SwrContext* p)
				{
					swr_free(&p);
				}
				};
				swr_init(swr_.get());

				fourcc = FOURCC_BGRA;
				get_video_frame_size(in_video_format_.width, in_video_format_.height, fourcc, &line_size, &img_start);

				RENDER_TYPE render_type = path_parser(); 
				if (render_type == RENDER_UNKNOWN)
				{
					CASPAR_LOG(error) << "Not support this render type.";
					return;
				}
				else
				{
					render_ = render_base::create(render_type);
					if (nullptr == render_) return;

					bool bret = render_->init(full_path_.string(), path_options_);
					if (false == bret) return;

					//format
					MUXER_TYPE muxer_type = MUXER_UNKNOWN;
					const auto oformat_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^f|format$"));
					if (oformat_name)
						muxer_type = get_muxer_type(oformat_name->c_str());
					if (muxer_type != MUXER_UNKNOWN)
					{
						muxer_ = muxer_base::create(muxer_type);
						if (nullptr == muxer_)	return;
						bret = muxer_->init(options_, render_->getrenderinbufstrm());
						if (false == bret)	 return;
					}
					else
					{
						return;
					}

					//vcodec
					ENC_TYPE v_enc_type = ENC_UNKNOWN;
					const auto video_codec_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^c:v|codec:v|vcodec$"));
					if (video_codec_name)
						v_enc_type = get_video_enc_type(video_codec_name->c_str());
					if (ENC_UNKNOWN != v_enc_type)
					{
						video_enc_ = enc_base::createvideo(v_enc_type,in_video_format_.width,in_video_format_.height);
						if (nullptr == video_enc_) return;
						muxer_->addvideostream();
						bret = video_enc_->init(options_, muxer_->getvideobufstrm());
						if (false == bret)	 return;
					}
					else
					{
						return;
					}

					//acodec
					ENC_TYPE a_enc_type = ENC_UNKNOWN;
					const auto audio_codec_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^c:a|codec:a|acodec$"));
					if (audio_codec_name)
						a_enc_type = get_audio_enc_type(audio_codec_name->c_str());
					if (ENC_UNKNOWN != a_enc_type)
					{
						audio_encs_[0] = enc_base::createaudio(a_enc_type,in_video_format_.audio_sample_rate,in_channel_layout_.num_channels);
						if (nullptr == audio_encs_[0]) return;
						muxer_->addaudiostream(0);
						bret = audio_encs_[0]->init(options_, muxer_->getaudiobufstrm(0));
						if (false == bret)	 return;
					}
					else
					{
						return;
					}
                   
					//第二路音轨
					if (options2_.size() > 0)
					{
						ENC_TYPE a_enc_type2 = ENC_UNKNOWN;
						const auto audio_codec_name2 =
							try_remove_arg<std::string>(
								options2_,
								boost::regex("^c:a|codec:a|acodec$"));
						if (audio_codec_name2)
							a_enc_type2 = get_audio_enc_type(audio_codec_name2->c_str());
						if (ENC_UNKNOWN != a_enc_type2)
						{
							audio_encs_[1] = enc_base::createaudio(a_enc_type2, in_video_format_.audio_sample_rate, in_channel_layout_.num_channels);
							if (nullptr == audio_encs_[1]) return;
							muxer_->addaudiostream(1);
							bret = audio_encs_[1]->init(options2_, muxer_->getaudiobufstrm(1));
							if (false == bret)	 return;
						}
					}
				}
 				thread_ = boost::thread([this] {run(); });
			}

			RENDER_TYPE path_parser()
			{
				/*example:
				* udp://236.0.0.2:10002?rtype=dtnet&devtype=2162&devport=2&delaytime=1000&bitrate=8000000
				* udp://236.0.0.2:10002?rtype=mcnet&localaddr=172.16.3.83
				* d:/test.ts?rtype=mcfile
				*/
				RENDER_TYPE render_type = RENDER_UNKNOWN;
				std::string tmp_path = path_;
				std::string path_ops = "";
				int32_t nIdx = static_cast<int32_t>(path_.find('?'));
				if (nIdx > 0)
				{
					tmp_path = path_.substr(0, nIdx);
					full_path_ = tmp_path;
					path_ops = path_.substr(nIdx + 1, path_.length());
				}				

				if (!path_ops.empty())
				{
					for (auto it =
						boost::sregex_iterator(
							path_ops.begin(),
							path_ops.end(),
							boost::regex("(?<NAME>[^=]+)(=(?<VALUE>[^&]+)&*)?"));
						it != boost::sregex_iterator();
						++it)
					{
						path_options_[(*it)["NAME"].str()] = (*it)["VALUE"].matched ? (*it)["VALUE"].str() : "";
					}
				}

				std::map<std::string, std::string>::iterator it = path_options_.find("rtype");
				if (it != path_options_.end())
				{
					if (0 == it->second.compare("mcfile"))
					{
						render_type = RENDER_MC_FILE;
					}
					else if (0 == it->second.compare("mcnet"))
					{
						render_type = RENDER_MC_NET;
					}
					else if (0 == it->second.compare("dtnet"))
					{
						render_type = RENDER_DT_NET;
					}
					path_options_.erase(it);
				}
				else //not specified render type
				{
					full_path_ = path_;
				}

				static boost::regex prot_exp("^.+:.*");
				static boost::regex prot_exp_disk("^.{1}:.*");
				if (!boost::regex_match(tmp_path, prot_exp))//relative path
				{
					if (!full_path_.is_complete())
					{
						full_path_ =
							u8(
								env::media_folder()) +
							tmp_path;
					}
					if (boost::filesystem::is_directory(full_path_))
					{
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"the complete path [" + u16(full_path_.string()) + L"] is not a file path."));
					}
					else if (boost::filesystem::exists(full_path_))
						boost::filesystem::remove(full_path_);
					boost::filesystem::create_directories(full_path_.parent_path());
				}
				else if (boost::regex_match(tmp_path, prot_exp_disk))//absolute path, if directory is not existed, create it
				{
					if (boost::filesystem::is_directory(full_path_))
					{
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"the complete path [" + u16(full_path_.string()) + L"] is not a file path."));
					}
					else if (boost::filesystem::exists(full_path_))
						boost::filesystem::remove(full_path_);
					boost::filesystem::create_directories(full_path_.parent_path());
				}
				return render_type;
			}

			MUXER_TYPE get_muxer_type(std::string oformatname)
			{
				MUXER_TYPE muxer_type = MUXER_UNKNOWN;
				if (0 == oformatname.compare("mcmpegts"))
				{
					muxer_type= MUXER_MC_MPEG;
				}
				else
				{
					muxer_type = MUXER_UNKNOWN;
					CASPAR_LOG(error) << L"Not support this muxer format:" << oformatname;
				}
				return muxer_type;
			}
			ENC_TYPE get_video_enc_type(std::string vcodecname)
			{
				ENC_TYPE v_enc_type = ENC_UNKNOWN;
				if (0 == vcodecname.compare("h264"))
				{
					v_enc_type = ENC_MC_H264;
				}
				else if (0 == vcodecname.compare("mpeg2"))
				{
					v_enc_type = ENC_MC_MPEG2;
				}
				else
				{
					v_enc_type = ENC_UNKNOWN;
					CASPAR_LOG(error) << L"Not support this video format:" << vcodecname;
				}
				return v_enc_type;
			}

			ENC_TYPE get_audio_enc_type(std::string acodecname)
			{
				ENC_TYPE a_enc_type = ENC_UNKNOWN;
				if (0 == acodecname.compare("mpa"))
				{
					a_enc_type = ENC_MC_MPA;
				}
				else if (0 == acodecname.compare("aac"))
				{
					a_enc_type = ENC_MC_AAC;
				}
				else if (0 == acodecname.compare("pcm")) //TS not support PCM
				{
					a_enc_type = ENC_MC_PCM;
				}
#ifdef _MSC_VER
				else if (0 == acodecname.compare("ac3"))
				{
					a_enc_type = ENC_MC_DDPP;
				}
#endif
				else
				{
					a_enc_type = ENC_UNKNOWN;
					CASPAR_LOG(error) << L"Not support this audio format:" << acodecname;
				}
				return a_enc_type;
			}
  
			void run()
 			{
				ensure_gpf_handler_installed_for_thread(
					"mainconcept-consumer-thread");
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
					video_encoder_executor_.begin_invoke([=]() mutable
					{
						encode_video(frame);
						if (++framerate_count_ >= framerate_interval_)
						{
							framerate_ = framerate_count_ / framerate_timer_.elapsed();
							framerate_timer_.restart();
							framerate_count_ = 0;
						}
						graph_->set_text(print());
					});

					audio_encoder_executor_.begin_invoke([=]() mutable
					{
						encode_audio(frame);
					});
					graph_->set_value("pushframe-time", pushframe_timer.elapsed() * in_video_format_.fps * 0.5);
				}
 			}

   			~mainconcept_consumer()
 			{
				video_encoder_executor_.stop();
				audio_encoder_executor_.stop();
				video_encoder_executor_.join();
				audio_encoder_executor_.join();

				is_running_ = false;
				thread_.join();

				if (video_enc_)
				{
					delete video_enc_;
					video_enc_ = nullptr;
				}
				for (std::map<uint32_t,enc_base*>::iterator iTer = audio_encs_.begin();iTer!= audio_encs_.end();++iTer)
				{
					enc_base* aenc = iTer->second;
					if (aenc)
					{
						delete aenc;
						aenc = nullptr;
					}
				}
				audio_encs_.clear();
				if (muxer_)
				{
					delete muxer_;
					muxer_ = nullptr;
				}
				if (render_)
				{
					delete render_;
					render_ = nullptr;
				}
			}

			core::monitor::subject& monitor_output()
			{
				return subject_;
			}

			template<typename T>
			static boost::optional<T> try_remove_arg(
				std::map<std::string, std::string>& options,
				const boost::regex& expr)
			{
				for (auto it = options.begin(); it != options.end(); ++it)
				{
					if (boost::regex_search(it->first, expr))
					{
						auto arg = it->second;
						options.erase(it);
						return boost::lexical_cast<T>(arg);
					}
				}

				return boost::optional<T>();
			}

			void encode_video(core::const_frame &frame)
			{
				uint8_t* tmp_video_buffer = (uint8_t*)malloc(frame.size());
				if (tmp_video_buffer)
				{
					std::memcpy(
						reinterpret_cast<char*>(tmp_video_buffer),
						frame.image_data().begin(),
						in_video_format_.height * in_video_format_.width * 4
					);
					video_enc_->encodevideo(tmp_video_buffer + img_start, line_size, fourcc);
					free(tmp_video_buffer);
					tmp_video_buffer = nullptr;
				}
			}
			void encode_audio(core::const_frame &frame)
			{
				uint8_t* input_audio_buffer = (uint8_t*)malloc(frame.audio_data().size() * sizeof(int32_t));
				uint8_t* tmp_audio_buffer = (uint8_t*)malloc(frame.audio_data().size() * sizeof(int16_t));
				if (tmp_audio_buffer)
				{
					std::memcpy((void*)input_audio_buffer, frame.audio_data().begin(), frame.audio_data().size() * sizeof(int32_t));
					//32bit transfer to 16bit
					const uint8_t **in = const_cast<const uint8_t**>(&input_audio_buffer);
					uint8_t* out[] = { reinterpret_cast<uint8_t*>(tmp_audio_buffer) };
					const auto channel_samples = swr_convert(
						swr_.get(),
						out,
						static_cast<int>(frame.audio_data().size() * sizeof(int16_t) / in_channel_layout_.num_channels),
						in,
						static_cast<int>(frame.audio_data().size() / in_channel_layout_.num_channels));
					
					for (std::map<uint32_t, enc_base*>::iterator iTer = audio_encs_.begin(); iTer != audio_encs_.end(); ++iTer)
					{
						enc_base* aenc = iTer->second;
						if (aenc)
						{
							aenc->encodeaudio(tmp_audio_buffer, static_cast<uint32_t>(frame.audio_data().size() * sizeof(int16_t)));
						}
					}
				
					free(input_audio_buffer);
					input_audio_buffer = nullptr;
					free(tmp_audio_buffer);
					tmp_audio_buffer = nullptr;
				}
			}
			int32_t get_video_frame_size(int32_t w, int32_t h, uint32_t cs_fourcc, int32_t *linesize, int32_t *imgstart)
			{
				frame_colorspace_info_tt cs_info;
				int32_t error = get_frame_colorspace_info(&cs_info, w, h, cs_fourcc, 0);
				if (error)
					return 0;
				/* comment out by zibj 20170424   not need flip
				//if (get_cs_type(cs_fourcc) == CS_FORMAT_RGB)
				//	flip_colorspace(&cs_info);
				*/
				*linesize = cs_info.stride[0];
				*imgstart = cs_info.plane_offset[0];
				return cs_info.frame_size;
			}
		};

		int crc16(const std::string& str)
		{
			boost::crc_16_type result;

			result.process_bytes(str.data(), str.length());

			return result.checksum();
		}
		struct mainconcept_consumer_proxy : public core::frame_consumer
		{
			const std::string						path_;
			const std::string						options_;
			const std::string						options2_;

			int									consumer_index_offset_;

 			std::unique_ptr<mainconcept_consumer> consumer_;
 		public:
			mainconcept_consumer_proxy(const std::string& path, const std::string& options, const std::string& options2)
				:path_(path)
				,options_(options)
				, options2_(options2)
				, consumer_index_offset_(crc16(path))
			{
			}

			// Methods
			std::future<bool> send(core::const_frame frame) override
			{
				return consumer_->send(frame);
			}
			void initialize(
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& channel_layout,
				int channel_index) override
			{
				if (consumer_)
					CASPAR_THROW_EXCEPTION(invalid_operation() << msg_info("Cannot reinitialize mainconcept-consumer."));
				consumer_.reset(new mainconcept_consumer(path_, options_, options2_));
				consumer_->initialize(format_desc, channel_layout);
			}

			// monitor::observable
			core::monitor::subject& monitor_output() override
			{
				return consumer_->monitor_output();
			}
			
			// Properties

			std::wstring print() const override
			{
				return consumer_ ? consumer_->print() : L"[mainconcept_consumer]";
			}

			std::wstring name() const override
			{
				return L"mainconcept";
			}

			boost::property_tree::wptree info() const override
			{
				boost::property_tree::wptree info;
				info.add(L"type", L"mainconcept");
				info.add(L"path", u16(path_));
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
				return 8000 + consumer_index_offset_;
			}

			int64_t presentation_frame_age_millis() const override
			{
				return 1;
			}
		};

		void describe_consumer(core::help_sink& sink, const core::help_repository& repo)
		{
			sink.short_description(L"Mainconcept Consumer.");
			sink.para()->text(L"Examples:");
			sink.example(L">> ADD 1 MAINCONCEPT output.ts  args \"-format mpegts -vcodec mpeg2 -acodec aac -vbitrate 8000000 -pcrinterval 30 -psiinterval 100 -videopid 1234 -audiopid 2134\"");
			sink.example(L">> ADD 1 MAINCONCEPT e:/output.ts args \"-format mpegts -vcodec mpeg2 -acodec aac -vbitrate 8000000 -pcrinterval 30 -psiinterval 100 -videopid 1234 -audiopid 2134\"");
			sink.example(L">> ADD 1 MAINCONCEPT udp://234.5.5.1:2345 args \"-format mpegts -vcodec mpeg2 -acodec aac -vbitrate 8000000 -pcrinterval 30 -psiinterval 100 -videopid 1234 -audiopid 2134\"");
			sink.example(L">> REMOVE 1 MAINCONCEPT udp://234.5.5.1:2345");
			sink.example(L">> REMOVE 1 MAINCONCEPT e:/output.ts");
			sink.example(L">> REMOVE 1 MAINCONCEPT output.ts");
		}

		spl::shared_ptr<core::frame_consumer> create_consumer(
			const std::vector<std::wstring>& params, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			if (params.size() < 1 || !boost::iequals(params.at(0), L"MAINCONCEPT"))
				return core::frame_consumer::empty();
			auto params2 = params;
			auto path = u8(params2.size() > 1 ? params2.at(1) : L"");
			auto args = u8(get_param(L"args", params, L""));
			auto args2 = u8(get_param(L"args2", params, L""));

			return spl::make_shared<mainconcept_consumer_proxy>(path,args,args2);
		}

		spl::shared_ptr<core::frame_consumer> create_preconfigured_consumer(
			const boost::property_tree::wptree& ptree, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			return spl::make_shared<mainconcept_consumer_proxy>(
				u8(ptree_get<std::wstring>(ptree, L"path")),
				u8(ptree.get<std::wstring>(L"args", L"")),
				u8(ptree.get<std::wstring>(L"args2", L"")));
		}
}}




