#include "../StdAfx.h"

#include "ffmpeg_consumer.h"

#include "../ffmpeg_error.h"
#include "../producer/util/util.h"
#include "../producer/filter/filter.h"
#include "../producer/filter/audio_filter.h"

#include <muxer/muxer_base.h>
#include <render/render_base.h>
#include <auxinfo.h>

#include <common/except.h>
#include <common/executor.h>
#include <common/assert.h>
#include <common/utf.h>
#include <common/future.h>
#include <common/diagnostics/graph.h>
#include <common/env.h>
#include <common/scope_exit.h>
#include <common/ptree.h>
#include <common/param.h>
#include <common/semaphore.h>
#include <common/memcpy.h>
#include <common/prec_timer.h>

#include <core/consumer/frame_consumer.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/video_format.h>
#include <core/monitor/monitor.h>
#include <core/help/help_repository.h>
#include <core/help/help_sink.h>

#include <boost/noncopyable.hpp>
#include <boost/rational.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/property_tree/ptree.hpp>

#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4245)
#include <boost/crc.hpp>
#pragma warning(pop)

#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_invoke.h>
#include <tbb/parallel_for.h>

#include <numeric>

//intel ipp
#include <ippcc.h>

#pragma warning(push)
#pragma warning(disable: 4244)

extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/frame.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libavutil/parseutils.h>
#include <libavfilter/avfilter.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
}

#pragma warning(pop)

namespace caspar {
	namespace ffmpeg {

		static const int aac_sample_rates[16] = {
			96000, 88200, 64000, 48000, 44100, 32000,
			24000, 22050, 16000, 12000, 11025, 8000, 7350
		};
		struct adts_header
		{
			adts_header(int profile, int channels, int samplerateindex)
			{
				profile_ = profile;
				channels_ = channels;
				samplerateindex_ = samplerateindex;
				pData = new uint8_t[7];
			}
			~adts_header()
			{
				if (pData)
				{
					delete pData;
					pData = nullptr;
				}
			}
			uint8_t* constructheader(int packetlen)
			{
				pData[0] = 0xFF;
				pData[1] = 0xF9;
				pData[2] = (((profile_) << 6) + (samplerateindex_ << 2) + (channels_ >> 2));
				pData[3] = (((channels_ & 3) << 6) + (packetlen >> 11));
				pData[4] = ((packetlen & 0x7FF) >> 3);
				pData[5] = (((packetlen & 7) << 5) + 0x1F);
				pData[6] = 0xFC;
				return pData;
			}
		private:
			int profile_;
			int channels_;
			int samplerateindex_;
			uint8_t* pData;
		};

		void set_pixel_format(AVFilterContext* sink, AVPixelFormat pix_fmt)
		{
#pragma warning (push)
#pragma warning (disable : 4245)

			FF(av_opt_set_int_list(
				sink,
				"pix_fmts",
				std::vector<AVPixelFormat>({ pix_fmt, AVPixelFormat::AV_PIX_FMT_NONE }).data(),
				-1,
				AV_OPT_SEARCH_CHILDREN));

#pragma warning (pop)
		}

		void adjust_video_filter(const AVCodec& codec, const core::video_format_desc& in_format, AVFilterContext* sink, std::string& filter)
		{
			switch (codec.id)
			{
			case AV_CODEC_ID_DVVIDEO:
				// Crop
				if (in_format.format == core::video_format::ntsc)
					filter = u8(append_filter(u16(filter), L"crop=720:480:0:2"));

				// Pixel format selection
				if (in_format.format == core::video_format::ntsc)
					set_pixel_format(sink, AVPixelFormat::AV_PIX_FMT_YUV411P);
				else if (in_format.format == core::video_format::pal)
					set_pixel_format(sink, AVPixelFormat::AV_PIX_FMT_YUV420P);
				else
					set_pixel_format(sink, AVPixelFormat::AV_PIX_FMT_YUV422P);

				// Scale
				if (in_format.height == 1080)
					filter = u8(append_filter(u16(filter), in_format.duration == 1001
						? L"scale=1280:1080"
						: L"scale=1440:1080"));
				else if (in_format.height == 720)
					filter = u8(append_filter(u16(filter), L"scale=960:720"));

				break;
			}
		}

		void setup_codec_defaults(AVCodecContext& encoder)
		{
			static const int MEGABIT = 1000000;

			switch (encoder.codec_id)
			{
			case AV_CODEC_ID_DNXHD:
				encoder.bit_rate = 220 * MEGABIT;

				break;
			case AV_CODEC_ID_PRORES:
				encoder.bit_rate = encoder.width < 1280
					? 63 * MEGABIT
					: 220 * MEGABIT;

				break;
			case AV_CODEC_ID_H264:
				av_opt_set(encoder.priv_data, "preset", "ultrafast", 0);
				av_opt_set(encoder.priv_data, "tune", "fastdecode", 0);
				av_opt_set(encoder.priv_data, "crf", "5", 0);

				break;
			}
		}

		bool is_pcm_s24le_not_supported(const AVFormatContext& container)
		{
			auto name = std::string(container.oformat->name);

			if (name == "mp4" || name == "dv")
				return true;

			return false;
		}

		template<typename Out, typename In>
		std::vector<Out> from_terminated_array(const In* array, In terminator)
		{
			std::vector<Out> result;

			while (array != nullptr && *array != terminator)
			{
				In val = *array;
				Out casted = static_cast<Out>(val);

				result.push_back(casted);

				++array;
			}

			return result;
		}

		class ffmpeg_consumer
		{
		private:
			const spl::shared_ptr<diagnostics::graph>	graph_;
			caspar::timer								tick_timer_;
			caspar::timer								video_enc_timer_;

			tbb::atomic<bool>									is_running_;
			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;
			boost::thread										thread_;

			core::monitor::subject						subject_;
			std::string									path_;
			std::string									path_redundancy_;
			boost::filesystem::path						full_path_;

			std::map<std::string, std::string>			options_;
			bool										mono_streams_;

			core::video_format_desc						in_video_format_;
			core::audio_channel_layout					in_channel_layout_ = core::audio_channel_layout::invalid();

			std::shared_ptr<AVFormatContext>			oc_;
			std::shared_ptr<AVFormatContext>			oc2_; //used for path_redundancy_
			tbb::atomic<bool>							abort_request_;

			std::shared_ptr<AVStream>					video_st_;
			std::vector<std::shared_ptr<AVStream>>		audio_sts_;

			std::int64_t								video_pts_ = 0;
			std::int64_t								audio_pts_ = 0;

			std::unique_ptr<audio_filter>				audio_filter_;

			// TODO: make use of already existent avfilter abstraction for video also
			AVFilterContext*							video_graph_in_;
			AVFilterContext*							video_graph_out_;
			std::shared_ptr<AVFilterGraph>				video_graph_;

			executor									video_encoder_executor_;
			executor									audio_encoder_executor_;

			tbb::atomic<int64_t>						current_encoding_delay_;

			executor									write_executor_;

			int                                                 framerate_interval_ = 25;
			int                                                 framerate_count_ = 0;
			caspar::timer                                       framerate_timer_;
			double                                              framerate_ = framerate_interval_;
			//
			std::map<std::string, std::string>			 path_options_;
			MUXER_TYPE                                   muxer_type_;
			RENDER_TYPE                                  render_type_;
			muxer_base *                                 muxer_;
			render_base *                                render_;
			std::map<int32_t, adts_header *>			 adts_headers_;

			//wxg record
			//--------------------------------------------------------------------
			bool										is_recodeMode_;
			bool										is_recording_;
			executor*									video_encoder_executor_record_;
			executor*									audio_encoder_executor_record_;
			executor*									write_executor_record_;
			int64_t										recordFramesNums_ = 0;
		public:

			ffmpeg_consumer(
				std::string path,
				std::string path_redundancy,
				std::string options,
				bool mono_streams)
				: path_(path)
				, path_redundancy_(path_redundancy)
				, full_path_(path)
				, mono_streams_(mono_streams)
				, audio_encoder_executor_(print() + L" audio_encoder")
				, video_encoder_executor_(print() + L" video_encoder")
				, write_executor_(print() + L" io")
				, muxer_type_(MUXER_UNKNOWN)
				, render_type_(RENDER_UNKNOWN)
				, muxer_(nullptr)
				, render_(nullptr)
				,is_recording_(false)
				,is_recodeMode_(false)
			{
				frame_buffer_.set_capacity(10);
				is_running_ = true;

				abort_request_ = false;
				current_encoding_delay_ = 0;

				for (auto it =
					boost::sregex_iterator(
						options.begin(),
						options.end(),
						boost::regex("-(?<NAME>[^\\s]+)(\\s+(?<VALUE>[^\\s]+))?"));
					it != boost::sregex_iterator();
					++it)
				{
					options_[(*it)["NAME"].str()] = (*it)["VALUE"].matched ? (*it)["VALUE"].str() : "";
				}

				if (options_.find("threads") == options_.end())
					options_["threads"] = "auto";

				graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
				graph_->set_color("pushframe-time", diagnostics::color(0.1f, 1.0f, 0.1f));
				graph_->set_color("videoenc-time", diagnostics::color(1.0f, 0.4f, 0.0f, 0.8f));
				graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
				graph_->set_color("buffer-frames", diagnostics::color(0.7f, 0.4f, 0.4f));
				graph_->set_text(print());
				diagnostics::register_graph(graph_);

				is_recodeMode_ = !boost::contains(path_, L"://");
			}

			~ffmpeg_consumer()
			{
				if (oc_)
				{
					try
					{
						video_encoder_executor_.begin_invoke([&] { encode_video(nullptr); });
						audio_encoder_executor_.begin_invoke([&] { encode_audio(core::const_frame::empty()); });

						video_encoder_executor_.stop();
						audio_encoder_executor_.stop();
						video_encoder_executor_.join();
						audio_encoder_executor_.join();

						video_graph_.reset();
						audio_filter_.reset();
						video_st_.reset();
						audio_sts_.clear();

						write_packet(nullptr);

						write_executor_.stop();
						write_executor_.join();

						FF(av_write_trailer(oc_.get()));

						if (!(oc_->oformat->flags & AVFMT_NOFILE) && oc_->pb)
							avio_close(oc_->pb);

						oc_.reset();

						if (oc2_)
						{
							FF(av_write_trailer(oc2_.get()));

							if (!(oc2_->oformat->flags & AVFMT_NOFILE) && oc2_->pb)
								avio_close(oc2_->pb);

							oc2_.reset();
						}
					}
					catch (...)
					{
						CASPAR_LOG_CURRENT_EXCEPTION();
					}
				}
				is_running_ = false;
				thread_.join();
					
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

				for (std::map<int32_t, adts_header*>::iterator iter = adts_headers_.begin(); iter != adts_headers_.end(); iter++)
				{
					adts_header* adts_header_ = iter->second;
					if (adts_header_)
					{
						delete adts_header_;
						adts_header_ = nullptr;
					}
				}
				adts_headers_.clear();
			}

			void initialize(
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& channel_layout)
			{
				//graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
				//graph_->set_color("pushframe-time", diagnostics::color(0.1f, 1.0f, 0.1f));
				//graph_->set_color("videoenc-time", diagnostics::color(1.0f, 0.4f, 0.0f, 0.8f));
				//graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
				//graph_->set_color("buffer-frames", diagnostics::color(0.7f, 0.4f, 0.4f));
				//graph_->set_text(print());
				//diagnostics::register_graph(graph_);
				CASPAR_VERIFY(format_desc.format != core::video_format::invalid);

				in_video_format_ = format_desc;
				in_channel_layout_ = channel_layout;

				framerate_ = framerate_interval_ = in_video_format_.fps;

				path_parser();
				if (render_type_ != RENDER_UNKNOWN)
				{
					initialize_new();
				}
				else
				{
					initialize_std_ffmpeg();
				}
			}

			void initialize_record(
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& channel_layout)
			{
				recordFramesNums_ = 0;
				is_running_ = true;
				video_encoder_executor_record_ = new executor(u16(path_) + L" video_encoder");
				audio_encoder_executor_record_ = new executor(u16(path_) + L" audio_encoder");
				write_executor_record_ = new executor(u16(path_) + L" io");
				//graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
				//graph_->set_color("pushframe-time", diagnostics::color(0.1f, 1.0f, 0.1f));
				//graph_->set_color("videoenc-time", diagnostics::color(1.0f, 0.4f, 0.0f, 0.8f));
				//graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
				//graph_->set_color("buffer-frames", diagnostics::color(0.7f, 0.4f, 0.4f));
				//graph_->set_text(print());
				//diagnostics::register_graph(graph_);

				CASPAR_VERIFY(format_desc.format != core::video_format::invalid);

				in_video_format_ = format_desc;
				in_channel_layout_ = channel_layout;

				framerate_ = framerate_interval_ = in_video_format_.fps;

				path_parser();
				if (render_type_ != RENDER_UNKNOWN)
				{
					initialize_new();
				}
				else
				{
					initialize_std_ffmpeg();
				}
			}

			void uninitiate_record()
			{
				core::const_frame frame;
				while (frame_buffer_.try_pop(frame))
				{
					boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
				}
				is_running_ = false;
				thread_.join();
				if (oc_)
				{
					try
					{
						video_encoder_executor_record_->begin_invoke([&] { encode_video(nullptr); });
						audio_encoder_executor_record_->begin_invoke([&] { encode_audio(core::const_frame::empty()); });
						video_encoder_executor_record_->stop();

						audio_encoder_executor_record_->stop();
						video_encoder_executor_record_->join();
						audio_encoder_executor_record_->join();

						graph_->auto_reset();
						boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
						video_graph_.reset();
						audio_filter_.reset();
						video_st_.reset();
						audio_sts_.clear();

						CASPAR_LOG(info) << L"ffmpeg record video and audio encode params reset! ";

						write_packet_record(nullptr);

						write_executor_record_->stop();
						write_executor_record_->join();

						FF(av_write_trailer(oc_.get()));

						if (!(oc_->oformat->flags & AVFMT_NOFILE) && oc_->pb)
							avio_close(oc_->pb);

						oc_.reset();

						if (oc2_)
						{
							FF(av_write_trailer(oc2_.get()));

							if (!(oc2_->oformat->flags & AVFMT_NOFILE) && oc2_->pb)
								avio_close(oc2_->pb);

							oc2_.reset();
						}
					}
					catch (...)
					{
						CASPAR_LOG_CURRENT_EXCEPTION();
					}
				}

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

				for (std::map<int32_t, adts_header*>::iterator iter = adts_headers_.begin(); iter != adts_headers_.end(); iter++)
				{
					adts_header* adts_header_ = iter->second;
					if (adts_header_)
					{
						delete adts_header_;
						adts_header_ = nullptr;
					}
				}
				adts_headers_.clear();
			}

			void initialize_new()
			{
				try
				{
					render_ = render_base::create(render_type_);
					if (nullptr == render_) return;

					bool bret = render_->init(full_path_.string(), path_options_);
					if (false == bret) return;
	
					/*const */auto oformat_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^f|format$"));
					
					if (0 == oformat_name->compare("mcmpegts")) //mcmpegts
					{
						muxer_type_ = MUXER_MC_MPEG;
						oformat_name.reset("mpegts");
					}

					if (muxer_type_ != MUXER_UNKNOWN)
					{
						muxer_ = muxer_base::create(muxer_type_);
						if (nullptr == muxer_)	return;
              			bret = muxer_->init(options_,render_->getrenderinbufstrm());
						if (false == bret)	 return;
					}

					AVFormatContext* oc;
					FF(avformat_alloc_output_context2(
						&oc,
						nullptr,
						oformat_name && !oformat_name->empty() ? oformat_name->c_str() : nullptr,
						full_path_.string().c_str()));

					oc_.reset(
						oc,
						avformat_free_context);

					CASPAR_VERIFY(oc_->oformat);

					oc_->interrupt_callback.callback = ffmpeg_consumer::interrupt_cb;
					oc_->interrupt_callback.opaque = this;

					CASPAR_VERIFY(oc_->oformat);

					const auto video_codec_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^c:v|codec:v|vcodec$"));

					const auto video_codec =
						video_codec_name
						? avcodec_find_encoder_by_name(video_codec_name->c_str())
						: avcodec_find_encoder(oc_->oformat->video_codec);

					const auto audio_codec_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^c:a|codec:a|acodec$"));

					const auto audio_codec =
						audio_codec_name
						? avcodec_find_encoder_by_name(audio_codec_name->c_str())
						: (is_pcm_s24le_not_supported(*oc_)
							? avcodec_find_encoder(oc_->oformat->audio_codec)
							: avcodec_find_encoder_by_name("pcm_s24le"));

					if (!video_codec)
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(
							"Failed to find video codec " + (video_codec_name
								? *video_codec_name
								: "with id " + boost::lexical_cast<std::string>(
									oc_->oformat->video_codec))));
					if (!audio_codec)
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(
							"Failed to find audio codec " + (audio_codec_name
								? *audio_codec_name
								: "with id " + boost::lexical_cast<std::string>(
									oc_->oformat->audio_codec))));

					// Filters

					{
						configure_video_filters(
							*video_codec,
							try_remove_arg<std::string>(options_, boost::regex("vf|f:v|filter:v"))
							.get_value_or(""),
							try_remove_arg<std::string>(options_, boost::regex("pix_fmt")));

						configure_audio_filters(
							*audio_codec,
							try_remove_arg<std::string>(options_,
								boost::regex("af|f:a|filter:a")).get_value_or(""));
					}

					// Encoders

					{
						auto video_options = options_;
						auto audio_options = options_;

						video_st_ = open_encoder(
							*video_codec,
							video_options,
							0);

						for (int i = 0; i < audio_filter_->get_num_output_pads(); ++i)
							audio_sts_.push_back(open_encoder(
								*audio_codec,
								audio_options,
								i));

						auto it = options_.begin();
						while (it != options_.end())
						{
							if (video_options.find(it->first) == video_options.end() || audio_options.find(it->first) == audio_options.end())
								it = options_.erase(it);
							else
								++it;
						}
					}
					//Muxer
					if (nullptr != muxer_)
					{
						muxer_->addvideostream();
						for (int pad_id = 0; pad_id < audio_filter_->get_num_output_pads(); ++pad_id)
						{
							muxer_->addaudiostream(pad_id);
							if (audio_sts_.at(pad_id)->codec->codec_id == AV_CODEC_ID_AAC) //AAC ADTS
							{
								int profile = audio_sts_.at(pad_id)->codec->profile; //AAC LC 
								int channels = audio_sts_.at(pad_id)->codec->channels;
								int samplerateindex = -1;
								for (int i = 0; i < 16; i++)
								{
									if (audio_sts_.at(pad_id)->codec->sample_rate == aac_sample_rates[i])
									{
										samplerateindex = i;
										break;
									}
								}
								if (samplerateindex == -1)
								{
									CASPAR_LOG(error) << L"not support this samplerate:" << audio_sts_.at(pad_id)->codec->sample_rate;
									return;
								}
								adts_header* adts_header_ = new adts_header(profile, channels, samplerateindex);
								adts_headers_[pad_id] = adts_header_;
							}
						}
					}

 					// Output
 					{
 						AVDictionary* av_opts = nullptr;
 
 						to_dict(
 							&av_opts,
 							std::move(options_));
 
 						CASPAR_SCOPE_EXIT
 						{
 							av_dict_free(&av_opts);
 						};
 
						if (!(oc_->oformat->flags & AVFMT_NOFILE))
						{
							FF(avio_open2(
								&oc_->pb,
								full_path_.string().c_str(),
								AVIO_FLAG_WRITE,
								&oc_->interrupt_callback,
								&av_opts));
						}
 
 						FF(avformat_write_header(
 							oc_.get(),
 							&av_opts));
 
 						options_ = to_map(av_opts);
 					}

					// Dump Info

					av_dump_format(
						oc_.get(),
						0,
						oc_->filename,
						1);

					for (const auto& option : options_)
					{
						CASPAR_LOG(warning)
							<< L"Invalid option: -"
							<< u16(option.first)
							<< L" "
							<< u16(option.second);
					}
					
					if (is_recodeMode_)
						thread_ = boost::thread([this] { run_record(); });
					else
						thread_ = boost::thread([this] {run(); });
				}
				catch (...)
				{
					video_st_.reset();
					audio_sts_.clear();
					oc_.reset();
					throw;
				}
			}

			void initialize_std_ffmpeg()
			{
				try
				{
					/*const*/ auto oformat_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^format$"));

					AVFormatContext* oc;
					FF(avformat_alloc_output_context2(
						&oc,
						nullptr,
						oformat_name && !oformat_name->empty() ? oformat_name->c_str() : nullptr,
						full_path_.string().c_str()));

					oc_.reset(
						oc,
						avformat_free_context);

					CASPAR_VERIFY(oc_->oformat);

					oc_->interrupt_callback.callback = ffmpeg_consumer::interrupt_cb;
					oc_->interrupt_callback.opaque = this;

					CASPAR_VERIFY(oc_->oformat);

					const auto video_codec_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^c:v|codec:v|vcodec$"));

					const auto video_codec =
						video_codec_name
						? avcodec_find_encoder_by_name(video_codec_name->c_str())
						: avcodec_find_encoder(oc_->oformat->video_codec);

					const auto audio_codec_name =
						try_remove_arg<std::string>(
							options_,
							boost::regex("^c:a|codec:a|acodec$"));

					const auto audio_codec =
						audio_codec_name
						? avcodec_find_encoder_by_name(audio_codec_name->c_str())
						: (is_pcm_s24le_not_supported(*oc_)
							? avcodec_find_encoder(oc_->oformat->audio_codec)
							: avcodec_find_encoder_by_name("pcm_s24le"));

					if (!video_codec)
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(
							"Failed to find video codec " + (video_codec_name
								? *video_codec_name
								: "with id " + boost::lexical_cast<std::string>(
									oc_->oformat->video_codec))));
					if (!audio_codec)
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(
							"Failed to find audio codec " + (audio_codec_name
								? *audio_codec_name
								: "with id " + boost::lexical_cast<std::string>(
									oc_->oformat->audio_codec))));

					// Filters

					{
						configure_video_filters(
							*video_codec,
							try_remove_arg<std::string>(options_, boost::regex("vf|f:v|filter:v"))
							.get_value_or(""),
							try_remove_arg<std::string>(options_, boost::regex("pix_fmt")));

						configure_audio_filters(
							*audio_codec,
							try_remove_arg<std::string>(options_,
								boost::regex("af|f:a|filter:a")).get_value_or(""));
					}

					// Encoders

					{
						auto video_options = options_;
						auto audio_options = options_;

						video_st_ = open_encoder(
							*video_codec,
							video_options,
							0);

						for (int i = 0; i < audio_filter_->get_num_output_pads(); ++i)
							audio_sts_.push_back(open_encoder(
								*audio_codec,
								audio_options,
								i));

						auto it = options_.begin();
						while (it != options_.end())
						{
							if (video_options.find(it->first) == video_options.end() || audio_options.find(it->first) == audio_options.end())
								it = options_.erase(it);
							else
								++it;
						}
					}

					// Output
					{
						AVDictionary* av_opts = nullptr;

						to_dict(
							&av_opts,
							std::move(options_));

						CASPAR_SCOPE_EXIT
						{
							av_dict_free(&av_opts);
						};

						if (!(oc_->oformat->flags & AVFMT_NOFILE))
						{
							FF(avio_open2(
								&oc_->pb,
								full_path_.string().c_str(),
								AVIO_FLAG_WRITE,
								&oc_->interrupt_callback,
								&av_opts));
						}

						FF(avformat_write_header(
							oc_.get(),
							&av_opts));

						//
						if (!path_redundancy_.empty())
						{
							int32_t nIdx = static_cast<int32_t>(path_redundancy_.find(':'));
							if (nIdx > 0)
							{
								std::string protocolstr = path_redundancy_.substr(0, nIdx + 3);
								if (0 == protocolstr.compare("rtmp://"))
								{
									oformat_name.reset("flv");
								}
							}
							
							AVFormatContext* oc2;
							FF(avformat_alloc_output_context2(
								&oc2,
								nullptr,
								oformat_name && !oformat_name->empty() ? oformat_name->c_str() : nullptr,
								path_redundancy_.c_str()));

							oc2_.reset(
								oc2,
								avformat_free_context);

							CASPAR_VERIFY(oc2_->oformat);

							oc2_->interrupt_callback.callback = ffmpeg_consumer::interrupt_cb;
							oc2_->interrupt_callback.opaque = this;

							CASPAR_VERIFY(oc2_->oformat);

							for (int i = 0; i < oc_->nb_streams; i++) 
							{
								AVStream *in_stream = oc_->streams[i];
								AVStream *out_stream = avformat_new_stream(oc2_.get(), in_stream->codec->codec);
								avcodec_copy_context(out_stream->codec, in_stream->codec);
							}


							if (!(oc2_->oformat->flags & AVFMT_NOFILE))
							{
								FF(avio_open2(
									&oc2_->pb,
									path_redundancy_.c_str(),
									AVIO_FLAG_WRITE,
									&oc2_->interrupt_callback,
									&av_opts));
							}

							FF(avformat_write_header(
								oc2_.get(),
								&av_opts));
						}

						options_ = to_map(av_opts);
					}

					// Dump Info

					av_dump_format(
						oc_.get(),
						0,
						oc_->filename,
						1);
					if (oc2_)
					{
						av_dump_format(
							oc2_.get(),
							0,
							oc2_->filename,
							1);
					}					

					for (const auto& option : options_)
					{
						CASPAR_LOG(warning)
							<< L"Invalid option: -"
							<< u16(option.first)
							<< L" "
							<< u16(option.second);
					}

					if (is_recodeMode_)
						thread_ = boost::thread([this] { run_record(); });
					else
						thread_ = boost::thread([this] {run(); });
				}
				catch (...)
				{
					video_st_.reset();
					audio_sts_.clear();
					oc_.reset();
					throw;
				}
			}

			core::monitor::subject& monitor_output()
			{
				return subject_;
			}

			void send(core::const_frame frame)
			{
				graph_->set_value("tick-time", tick_timer_.elapsed()*in_video_format_.fps*0.5);
				if (!frame_buffer_.try_push(frame))
					graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
				if (is_recodeMode_ && !is_recording_)
				{
					core::const_frame dropFrame;
					frame_buffer_.try_pop(dropFrame);
				}
				graph_->set_text(print());
				graph_->set_value("buffer-frames", ((double)frame_buffer_.size()) / frame_buffer_.capacity());
				tick_timer_.restart();
			}

			void run()
			{
				ensure_gpf_handler_installed_for_thread(
					"ffmpeg-consumer-thread");
				char* pNewData = nullptr;
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
 					if (!pNewData)
 					{
 						pNewData = (char*)malloc(in_video_format_.width * in_video_format_.height *2);
 					}
 
					if (pNewData)
					{
						//intel BGRA To NV12	
						IppStatus ippStatus;
						Ipp8u* pDstY = (Ipp8u*)pNewData;
						Ipp8u* pDstCbCr = (Ipp8u*)&pNewData[in_video_format_.width*in_video_format_.height];
						ippStatus = ippiBGRToYCbCr420_8u_AC4P2R(frame.image_data().begin(), in_video_format_.width * 4,
							pDstY, in_video_format_.width, pDstCbCr ,in_video_format_.width,{ in_video_format_.width, in_video_format_.height });
						
						//构建av_frame
						auto video_frame = create_frame();
						const auto sample_aspect_ratio =
							boost::rational<int>(
								in_video_format_.square_width,
								in_video_format_.square_height) /
							boost::rational<int>(
								in_video_format_.width,
								in_video_format_.height);

						video_frame->format = AVPixelFormat::AV_PIX_FMT_NV12;
						video_frame->width = in_video_format_.width;
						video_frame->height = in_video_format_.height;
						video_frame->sample_aspect_ratio.num = sample_aspect_ratio.numerator();
						video_frame->sample_aspect_ratio.den = sample_aspect_ratio.denominator();
						video_frame->pts = video_pts_;
						video_pts_ += 1;

						FF(av_image_fill_arrays(
							video_frame->data,
							video_frame->linesize,
							reinterpret_cast<uint8_t*>(pNewData),
							static_cast<AVPixelFormat>(video_frame->format),
							in_video_format_.width,
							in_video_format_.height,
							1));

						video_encoder_executor_.begin_invoke([=]() mutable
						{
							encode_video(video_frame);
						});
					}
					
					audio_encoder_executor_.begin_invoke([=]() mutable
					{
						encode_audio(frame);
					});
 					graph_->set_value("pushframe-time", pushframe_timer.elapsed() * in_video_format_.fps * 0.5);
				}
				if (pNewData)
				{
					free(pNewData);
					pNewData = nullptr;
				}
			}

			//wxg record 2017年9月1日09:53:22
			void run_record()
			{
				ensure_gpf_handler_installed_for_thread(
					"ffmpeg-consumer-thread");
				caspar::timer pushframe_timer;
				while (is_running_)
				{
					core::const_frame frame;
					if (!frame_buffer_.try_pop(frame))
					{
						boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
						continue;
					}
					recordFramesNums_++;
					pushframe_timer.restart();

					auto src_av_frame = create_frame();

					const auto sample_aspect_ratio =
						boost::rational<int>(
							in_video_format_.square_width,
							in_video_format_.square_height) /
						boost::rational<int>(
							in_video_format_.width,
							in_video_format_.height);

					src_av_frame->format = AVPixelFormat::AV_PIX_FMT_BGRA;
					src_av_frame->width = in_video_format_.width;
					src_av_frame->height = in_video_format_.height;
					src_av_frame->sample_aspect_ratio.num = sample_aspect_ratio.numerator();
					src_av_frame->sample_aspect_ratio.den = sample_aspect_ratio.denominator();
					src_av_frame->pts = video_pts_;
					src_av_frame->interlaced_frame = in_video_format_.field_mode != core::field_mode::progressive;
					src_av_frame->top_field_first = (in_video_format_.field_mode & core::field_mode::upper) == core::field_mode::upper ? 1 : 0;

					video_pts_ += 1;

					subject_
						<< core::monitor::message("/frame") % video_pts_
						<< core::monitor::message("/path") % path_
						<< core::monitor::message("/fps") % in_video_format_.fps;

					FF(av_image_fill_arrays(
						src_av_frame->data,
						src_av_frame->linesize,
						frame.image_data().begin(),
						static_cast<AVPixelFormat>(src_av_frame->format),
						in_video_format_.width,
						in_video_format_.height,
						1));

					FF(av_buffersrc_add_frame(
						video_graph_in_,
						src_av_frame.get()));

					auto filt_frame = create_frame();

					av_buffersink_get_frame(
						video_graph_out_,
						filt_frame.get());

					video_encoder_executor_record_->begin_invoke([=]() mutable
					{
						encode_video(filt_frame);
					});

					audio_encoder_executor_record_->begin_invoke([=]() mutable
					{
						encode_audio(frame);
					});
					graph_->set_value("pushframe-time", pushframe_timer.elapsed() * in_video_format_.fps * 0.5);
				}
			}

			void mark_dropped()
			{
				graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
			}

			std::wstring print() const
			{
				return L"ffmpeg_consumer[" + u16(path_) + L"|" + u16(path_redundancy_)+ L"|" + boost::lexical_cast<std::wstring>((float)framerate_) + L"]";
			}

			int64_t presentation_frame_age_millis() const
			{
				return current_encoding_delay_;
			}


			bool record_init(std::wstring strFileName)
			{
				return true;
			}

			bool record_start()
			{
				recordFramesNums_ = 0;
				return true;
			}

			bool record_stop()
			{
				//下面这个参数可以停止写文件，但是还在编码
				//abort_request_ = true;
				return true;
			}

			bool is_recording()
			{
				return is_recording_;
			}

			void set_recordStatus(bool recording)
			{
				is_recording_ = recording;
			}

			void set_newPath_options(std::string strFileName, const std::string opts)
			{
				path_ = strFileName;

				for (auto it =
					boost::sregex_iterator(
						opts.begin(),
						opts.end(),
						boost::regex("-(?<NAME>[^\\s]+)(\\s+(?<VALUE>[^\\s]+))?"));
					it != boost::sregex_iterator();
					++it)
				{
					options_[(*it)["NAME"].str()] = (*it)["VALUE"].matched ? (*it)["VALUE"].str() : "";
				}

				if (options_.find("threads") == options_.end())
					options_["threads"] = "auto";

				is_running_ = true;

				abort_request_ = false;
				current_encoding_delay_ = 0;
			}

			uint32_t getRecordFrames(std::wstring& fileName)
			{
				bool bfindClip = false;
				int pos = path_.find('.');
				if (pos > 0)
					bfindClip = u8(fileName) == path_.substr(0, pos);
				else
					bfindClip = u8(fileName) == path_;

				if(bfindClip)
					return  recordFramesNums_;
				return 0;
			}
		private:

		void path_parser()
			{
				/*example:
				* udp://236.0.0.2:10002?rtype=dtnet&devtype=2162&devport=2&delaytime=1000&bitrate=8000000
				* udp://236.0.0.2:10002?rtype=mcnet&localaddr=172.16.3.83
				* d:/test.ts?rtype=mcfile
				* udp://236.0.0.2:10002?pkt_size=1316
				*/
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
						render_type_ = RENDER_MC_FILE;
					}
					else if (0 == it->second.compare("mcnet"))
					{
						render_type_ = RENDER_MC_NET;
					}
					else if (0 == it->second.compare("dtnet"))
					{
						render_type_ = RENDER_DT_NET;
					}
					path_options_.erase(it);
				}
				else //not specified render type,default ffmpeg 
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
					{
						boost::filesystem::remove(full_path_);
						CASPAR_LOG(warning) << full_path_.c_str() << L"  has already existed, recreate it!";
					}
					boost::filesystem::create_directories(full_path_.parent_path());
				}
				else if (boost::regex_match(tmp_path, prot_exp_disk))//absolute path, if directory is not existed, create it
				{
					if (boost::filesystem::is_directory(full_path_))
					{
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"the complete path [" + u16(full_path_.string()) + L"] is not a file path."));
					}
					else if (boost::filesystem::exists(full_path_))
					{
						boost::filesystem::remove(full_path_);
						CASPAR_LOG(warning) << full_path_.c_str() << L"  has already existed, recreate it!";
					}
					boost::filesystem::create_directories(full_path_.parent_path());
				}
			}
			static int interrupt_cb(void* ctx)
			{
				CASPAR_ASSERT(ctx);
				return reinterpret_cast<ffmpeg_consumer*>(ctx)->abort_request_;
			}

			std::shared_ptr<AVStream> open_encoder(
				const AVCodec& codec,
				std::map<std::string,
				std::string>& options,
				int stream_number_for_media_type)
			{
				auto st =
					avformat_new_stream(
						oc_.get(),
						&codec);

				if (!st)
					CASPAR_THROW_EXCEPTION(caspar_exception() << msg_info("Could not allocate video-stream.") << boost::errinfo_api_function("avformat_new_stream"));

				auto enc = st->codec;

				CASPAR_VERIFY(enc);

				switch (enc->codec_type)
				{
				case AVMEDIA_TYPE_VIDEO:
				{
					enc->time_base = video_graph_out_->inputs[0]->time_base;
					enc->pix_fmt = static_cast<AVPixelFormat>(video_graph_out_->inputs[0]->format);
					enc->sample_aspect_ratio = st->sample_aspect_ratio = video_graph_out_->inputs[0]->sample_aspect_ratio;
					enc->width = video_graph_out_->inputs[0]->w;
					enc->height = video_graph_out_->inputs[0]->h;
					enc->bit_rate_tolerance = 400 * 1000000;

					break;
				}
				case AVMEDIA_TYPE_AUDIO:
				{
					enc->time_base = audio_filter_->get_output_pad_info(stream_number_for_media_type).time_base;
					enc->sample_fmt = static_cast<AVSampleFormat>(audio_filter_->get_output_pad_info(stream_number_for_media_type).format);
					enc->sample_rate = audio_filter_->get_output_pad_info(stream_number_for_media_type).sample_rate;
					enc->channel_layout = audio_filter_->get_output_pad_info(stream_number_for_media_type).channel_layout;
					enc->channels = audio_filter_->get_output_pad_info(stream_number_for_media_type).channels;

					break;
				}
				}

				setup_codec_defaults(*enc);

				if (oc_->oformat->flags & AVFMT_GLOBALHEADER)
					enc->flags |= CODEC_FLAG_GLOBAL_HEADER;

				static const std::array<std::string, 4> char_id_map = { { "v", "a", "d", "s" } };

				const auto char_id = char_id_map.at(enc->codec_type);

				const auto codec_opts =
					remove_options(
						options,
						boost::regex("^(" + char_id + "?[^:]+):" + char_id + "$"));

				AVDictionary* av_codec_opts = nullptr;

				to_dict(
					&av_codec_opts,
					options);

				to_dict(
					&av_codec_opts,
					codec_opts);

				options.clear();

				FF(avcodec_open2(
					enc,
					&codec,
					av_codec_opts ? &av_codec_opts : nullptr));

				if (av_codec_opts)
				{
					auto t =
						av_dict_get(
							av_codec_opts,
							"",
							nullptr,
							AV_DICT_IGNORE_SUFFIX);

					while (t)
					{
						options[t->key + (codec_opts.find(t->key) != codec_opts.end() ? ":" + char_id : "")] = t->value;

						t = av_dict_get(
							av_codec_opts,
							"",
							t,
							AV_DICT_IGNORE_SUFFIX);
					}

					av_dict_free(&av_codec_opts);
				}

				if (enc->codec_type == AVMEDIA_TYPE_AUDIO && !(codec.capabilities & CODEC_CAP_VARIABLE_FRAME_SIZE))
				{
					CASPAR_ASSERT(enc->frame_size > 0);
					audio_filter_->set_guaranteed_output_num_samples_per_frame(
						stream_number_for_media_type,
						enc->frame_size);
				}

				return std::shared_ptr<AVStream>(st, [this](AVStream* st)
				{
					avcodec_close(st->codec);
				});
			}

			void configure_video_filters(
				const AVCodec& codec,
				std::string filtergraph,
				const boost::optional<std::string>& preferred_pix_fmt)
			{
				video_graph_.reset(
					avfilter_graph_alloc(),
					[](AVFilterGraph* p)
				{
					avfilter_graph_free(&p);
				});

				video_graph_->nb_threads = boost::thread::hardware_concurrency() / 2;
				video_graph_->thread_type = AVFILTER_THREAD_SLICE;

				const auto sample_aspect_ratio =
					boost::rational<int>(
						in_video_format_.square_width,
						in_video_format_.square_height) /
					boost::rational<int>(
						in_video_format_.width,
						in_video_format_.height);

				int pixFormat = AVPixelFormat::AV_PIX_FMT_NV12;
				if (is_recodeMode_)
					pixFormat = AV_PIX_FMT_BGRA;

				const auto vsrc_options = (boost::format("video_size=%1%x%2%:pix_fmt=%3%:time_base=%4%/%5%:pixel_aspect=%6%/%7%:frame_rate=%8%/%9%")
					% in_video_format_.width % in_video_format_.height
					% pixFormat
					% in_video_format_.duration	% in_video_format_.time_scale
					% sample_aspect_ratio.numerator() % sample_aspect_ratio.denominator()
					% in_video_format_.time_scale % in_video_format_.duration).str();

				AVFilterContext* filt_vsrc = nullptr;
				FF(avfilter_graph_create_filter(
					&filt_vsrc,
					avfilter_get_by_name("buffer"),
					"ffmpeg_consumer_buffer",
					vsrc_options.c_str(),
					nullptr,
					video_graph_.get()));

				AVFilterContext* filt_vsink = nullptr;
				FF(avfilter_graph_create_filter(
					&filt_vsink,
					avfilter_get_by_name("buffersink"),
					"ffmpeg_consumer_buffersink",
					nullptr,
					nullptr,
					video_graph_.get()));

#pragma warning (push)
#pragma warning (disable : 4245)

				FF(av_opt_set_int_list(
					filt_vsink,
					"pix_fmts",
					codec.pix_fmts,
					-1,
					AV_OPT_SEARCH_CHILDREN));

#pragma warning (pop)

				adjust_video_filter(codec, in_video_format_, filt_vsink, filtergraph);

				if (preferred_pix_fmt)
				{
					auto requested_fmt = av_get_pix_fmt(preferred_pix_fmt->c_str());
					auto valid_fmts = from_terminated_array<AVPixelFormat>(codec.pix_fmts, AVPixelFormat::AV_PIX_FMT_NONE);

					if (!cpplinq::from(valid_fmts).contains(requested_fmt))
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(*preferred_pix_fmt + " is not supported by codec."));

					set_pixel_format(filt_vsink, requested_fmt);
				}

				if (in_video_format_.width < 1280)
					video_graph_->scale_sws_opts = av_strdup("out_color_matrix=bt601");
				else
					video_graph_->scale_sws_opts = av_strdup("out_color_matrix=bt709");

				configure_filtergraph(
					*video_graph_,
					filtergraph,
					*filt_vsrc,
					*filt_vsink);

				video_graph_in_ = filt_vsrc;
				video_graph_out_ = filt_vsink;

				CASPAR_LOG(info)
					<< u16(std::string("\n")
						+ avfilter_graph_dump(
							video_graph_.get(),
							nullptr));
			}

			void configure_audio_filters(
				const AVCodec& codec,
				std::string filtergraph)
			{
				int num_output_pads = 1;

				if (mono_streams_)
				{
					num_output_pads = in_channel_layout_.num_channels;
				}

				if (num_output_pads > 1)
				{
					std::string splitfilter = "[a:0]channelsplit=channel_layout=";

					splitfilter += (boost::format("0x%|1$x|") % create_channel_layout_bitmask(in_channel_layout_.num_channels)).str();

					for (int i = 0; i < num_output_pads; ++i)
						splitfilter += "[aout:" + boost::lexical_cast<std::string>(i) + "]";

					filtergraph = u8(append_filter(u16(filtergraph), u16(splitfilter)));
				}

				std::vector<audio_output_pad> output_pads(
					num_output_pads,
					audio_output_pad(
						from_terminated_array<int>(codec.supported_samplerates, 0),
						from_terminated_array<AVSampleFormat>(codec.sample_fmts, AVSampleFormat::AV_SAMPLE_FMT_NONE),
						from_terminated_array<uint64_t>(codec.channel_layouts, static_cast<uint64_t>(0))));

				audio_filter_.reset(new audio_filter(
				{ audio_input_pad(
					boost::rational<int>(1, in_video_format_.audio_sample_rate),
					in_video_format_.audio_sample_rate,
					AVSampleFormat::AV_SAMPLE_FMT_S32,
					create_channel_layout_bitmask(in_channel_layout_.num_channels)) },
					output_pads,
					filtergraph));
			}

			void configure_filtergraph(
				AVFilterGraph& graph,
				const std::string& filtergraph,
				AVFilterContext& source_ctx,
				AVFilterContext& sink_ctx)
			{
				AVFilterInOut* outputs = nullptr;
				AVFilterInOut* inputs = nullptr;

				if (!filtergraph.empty())
				{
					outputs = avfilter_inout_alloc();
					inputs = avfilter_inout_alloc();

					try
					{
						CASPAR_VERIFY(outputs && inputs);

						outputs->name = av_strdup("in");
						outputs->filter_ctx = &source_ctx;
						outputs->pad_idx = 0;
						outputs->next = nullptr;

						inputs->name = av_strdup("out");
						inputs->filter_ctx = &sink_ctx;
						inputs->pad_idx = 0;
						inputs->next = nullptr;
					}
					catch (...)
					{
						avfilter_inout_free(&outputs);
						avfilter_inout_free(&inputs);
						throw;
					}

					FF(avfilter_graph_parse(
						&graph,
						filtergraph.c_str(),
						inputs,
						outputs,
						nullptr));
				}
				else
				{
					FF(avfilter_link(
						&source_ctx,
						0,
						&sink_ctx,
						0));
				}

				FF(avfilter_graph_config(
					&graph,
					nullptr));
			}
			void encode_video(const std::shared_ptr<AVFrame>& video_frame)
			{
				encode_av_frame(
					*video_st_,
					avcodec_encode_video2,
					video_frame);

				if (++framerate_count_ >= framerate_interval_)
				{
					framerate_ = framerate_count_ / framerate_timer_.elapsed();
					framerate_timer_.restart();
					framerate_count_ = 0;
				}
				graph_->set_text(print());
			}
 
			void encode_audio(core::const_frame frame_ptr)
			{
				if (audio_sts_.empty())
					return;

				if (frame_ptr != core::const_frame::empty())
				{
					auto src_av_frame = create_frame();

					src_av_frame->channels = in_channel_layout_.num_channels;
					src_av_frame->channel_layout = create_channel_layout_bitmask(in_channel_layout_.num_channels);
					src_av_frame->sample_rate = in_video_format_.audio_sample_rate;
					src_av_frame->nb_samples = static_cast<int>(frame_ptr.audio_data().size()) / src_av_frame->channels;
					src_av_frame->format = AV_SAMPLE_FMT_S32;
					src_av_frame->pts = audio_pts_;

					audio_pts_ += src_av_frame->nb_samples;

					FF(av_samples_fill_arrays(
						src_av_frame->extended_data,
						src_av_frame->linesize,
						reinterpret_cast<const std::uint8_t*>(&*frame_ptr.audio_data().begin()),
						src_av_frame->channels,
						src_av_frame->nb_samples,
						static_cast<AVSampleFormat>(src_av_frame->format),
						16));

					audio_filter_->push(0, src_av_frame);
				}

				for (int pad_id = 0; pad_id < audio_filter_->get_num_output_pads(); ++pad_id)
				{
					for (auto filt_frame : audio_filter_->poll_all(pad_id))
					{
						audio_encoder_executor_.begin_invoke([=]
						{
							encode_av_frame(
								*audio_sts_.at(pad_id),
								avcodec_encode_audio2,
								filt_frame);

							boost::this_thread::yield(); // TODO:
						});
					}
				}

				bool eof = frame_ptr == core::const_frame::empty();

				if (eof)
				{
					audio_encoder_executor_.begin_invoke([=]
					{
						for (int pad_id = 0; pad_id < audio_filter_->get_num_output_pads(); ++pad_id)
						{
							auto enc = audio_sts_.at(pad_id)->codec;

							if (enc->codec->capabilities & CODEC_CAP_DELAY)
							{
								while (encode_av_frame(
									*audio_sts_.at(pad_id),
									avcodec_encode_audio2,
									nullptr))
								{
									boost::this_thread::yield(); // TODO:
								}
							}
						}
					});
				}
			}

			template<typename F>
			bool encode_av_frame(
				AVStream& st,
				const F& func,
				const std::shared_ptr<AVFrame>& src_av_frame)
			{
				AVPacket pkt = {};
				av_init_packet(&pkt);

				int got_packet = 0;
				if (st.codec->codec_type == AVMEDIA_TYPE_VIDEO)
				{
					video_enc_timer_.restart();
				}
				FF(func(
					st.codec,
					&pkt,
					src_av_frame.get(),
					&got_packet));

				if (!got_packet || pkt.size <= 0)
					return false;
				if (st.codec->codec_type == AVMEDIA_TYPE_VIDEO)
				{
					graph_->set_value("videoenc-time", video_enc_timer_.elapsed() * in_video_format_.fps * 0.5);
				}


				pkt.stream_index = st.index;

				if (pkt.pts != AV_NOPTS_VALUE)
				{
					pkt.pts =
						av_rescale_q(
							pkt.pts,
							st.codec->time_base,
							st.time_base);
				}

				if (pkt.dts != AV_NOPTS_VALUE)
				{
					pkt.dts =
						av_rescale_q(
							pkt.dts,
							st.codec->time_base,
							st.time_base);
				}

				pkt.duration =
					static_cast<int>(
						av_rescale_q(
							pkt.duration,
							st.codec->time_base, st.time_base));

				if (is_recodeMode_)
				{
					write_packet_record(
						std::shared_ptr<AVPacket>(
							new AVPacket(pkt),
							[](AVPacket* p)
					{
						av_free_packet(p);
						delete p;
					}));
				}
				else 
				{
					write_packet(
						std::shared_ptr<AVPacket>(
							new AVPacket(pkt),
							[](AVPacket* p)
					{
						av_free_packet(p);
						delete p;
					}));
				}

				return true;
			}

			void write_packet(
				const std::shared_ptr<AVPacket>& pkt_ptr)
			{
				write_executor_.begin_invoke([this, pkt_ptr]() mutable
				{
					if (nullptr == muxer_)
					{
						if (pkt_ptr && oc2_)
						{
							auto pkt_cpy = create_packet();
							av_copy_packet(pkt_cpy.get(), pkt_ptr.get());
							FF(av_interleaved_write_frame(
								oc2_.get(),
								pkt_cpy.get()));
						}
						FF(av_interleaved_write_frame(
							oc_.get(),
							pkt_ptr.get()));
					}
					else
					{
						write_packet_mc(pkt_ptr);
					}
					
				});
			}
			void write_packet_record(
				const std::shared_ptr<AVPacket>& pkt_ptr)
			{
				write_executor_record_->begin_invoke([this, pkt_ptr]() mutable
				{
					if (nullptr == muxer_)
					{
						if (pkt_ptr && oc2_)
						{
							auto pkt_cpy = create_packet();
							av_copy_packet(pkt_cpy.get(), pkt_ptr.get());
							FF(av_interleaved_write_frame(
								oc2_.get(),
								pkt_cpy.get()));
						}
						FF(av_interleaved_write_frame(
							oc_.get(),
							pkt_ptr.get()));
					}
					else
					{
						write_packet_mc(pkt_ptr);
					}

				});
			}

			void write_packet_mc(
				const std::shared_ptr<AVPacket>& pkt_ptr)
			{
				if (pkt_ptr == nullptr)
				{
					return;
				}
				if (pkt_ptr->stream_index == video_st_->index)
				{
					muxer_->getvideobufstrm()->copybytes(muxer_->getvideobufstrm(), pkt_ptr->data, pkt_ptr->size);
					v_au_struct videoinfo;
					memset(&videoinfo, 0, sizeof(v_au_struct));
					videoinfo.length = pkt_ptr->size;
					pkt_ptr->dts = pkt_ptr->dts * 300;
					pkt_ptr->pts = pkt_ptr->pts * 300;
					videoinfo.DTS = pkt_ptr->dts;
					videoinfo.PTS = pkt_ptr->pts;
					muxer_->getvideobufstrm()->auxinfo(muxer_->getvideobufstrm(), 0, VIDEO_AU_CODE, (uint8_t*)&videoinfo, sizeof(v_au_struct));
				}
				else
				{
					for (int pad_id = 0; pad_id < audio_filter_->get_num_output_pads(); ++pad_id)
					{
						if (pkt_ptr->stream_index == audio_sts_.at(pad_id)->index)
						{
							int packetlen = pkt_ptr->size;
							if (audio_sts_.at(pad_id)->codec->codec_id == AV_CODEC_ID_AAC) 
							{
								adts_header* adtsheader = adts_headers_[pad_id];
							 	if (adtsheader != nullptr)
							 	{
							 		packetlen = pkt_ptr->size + 7;
							 		uint8_t* pData = adtsheader->constructheader(packetlen);
							 		muxer_->getaudiobufstrm(pad_id)->copybytes(muxer_->getaudiobufstrm(pad_id), pData, 7);
							 	}
							}
							muxer_->getaudiobufstrm(pad_id)->copybytes(muxer_->getaudiobufstrm(pad_id), pkt_ptr->data, pkt_ptr->size);
							a_au_struct audioinfo;
							memset(&audioinfo, 0, sizeof(a_au_struct));
							audioinfo.length = packetlen;
							pkt_ptr->pts = pkt_ptr->pts * 300;
							audioinfo.pts = pkt_ptr->pts;
							muxer_->getaudiobufstrm(pad_id)->auxinfo(muxer_->getaudiobufstrm(pad_id), 0, AUDIO_AU_CODE, (uint8_t*)&audioinfo, sizeof(a_au_struct));
						}
					}
				}
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

			static std::map<std::string, std::string> remove_options(
				std::map<std::string, std::string>& options,
				const boost::regex& expr)
			{
				std::map<std::string, std::string> result;

				auto it = options.begin();
				while (it != options.end())
				{
					boost::smatch what;
					if (boost::regex_search(it->first, what, expr))
					{
						result[
							what.size() > 0 && what[1].matched
								? what[1].str()
								: it->first] = it->second;
						it = options.erase(it);
					}
					else
						++it;
				}

				return result;
			}

			static void to_dict(AVDictionary** dest, const std::map<std::string, std::string>& c)
			{
				for (const auto& entry : c)
				{
					av_dict_set(
						dest,
						entry.first.c_str(),
						entry.second.c_str(), 0);
				}
			}

			static std::map<std::string, std::string> to_map(AVDictionary* dict)
			{
				std::map<std::string, std::string> result;

				for (auto t = dict
					? av_dict_get(
						dict,
						"",
						nullptr,
						AV_DICT_IGNORE_SUFFIX)
					: nullptr;
					t;
					t = av_dict_get(
						dict,
						"",
						t,
						AV_DICT_IGNORE_SUFFIX))
				{
					result[t->key] = t->value;
				}

				return result;
			}
		};

		int crc16(const std::string& str)
		{
			boost::crc_16_type result;

			result.process_bytes(str.data(), str.length());

			return result.checksum();
		}

		struct ffmpeg_consumer_proxy : public core::frame_consumer
		{
			const std::string					path_;
			const std::string					path_redundancy_;
			const std::string					options_;
			const bool							separate_key_;
			const bool							mono_streams_;
			const bool							compatibility_mode_;
			int									consumer_index_offset_;

			std::unique_ptr<ffmpeg_consumer>	consumer_;
			std::unique_ptr<ffmpeg_consumer>	key_only_consumer_;
			//wxg record
			core::video_format_desc             format_desc_;
			core::audio_channel_layout          chn_layout_ = core::audio_channel_layout::invalid();
			bool								isFilePath_ = false;
		public:

			ffmpeg_consumer_proxy(const std::string& path, const std::string& path_redundancy,const std::string& options, bool separate_key, bool mono_streams, bool compatibility_mode)
				: path_(path)
				, path_redundancy_(path_redundancy)
				, options_(options)
				, separate_key_(separate_key)
				, mono_streams_(mono_streams)
				, compatibility_mode_(compatibility_mode)
				, consumer_index_offset_(crc16(path))
			{
				//通过path判断是文件路径还是stream
				isFilePath_ = !boost::contains(path_, L"://");
			}

			void initialize(const core::video_format_desc& format_desc, const core::audio_channel_layout& channel_layout, int) override
			{
				//wxg record
				//---------------------------------------------
				format_desc_ = format_desc;
				chn_layout_ = channel_layout;

				//---------------------------------------------
				if (consumer_)
					CASPAR_THROW_EXCEPTION(invalid_operation() << msg_info("Cannot reinitialize ffmpeg-consumer."));

				consumer_.reset(new ffmpeg_consumer(path_, path_redundancy_, options_, mono_streams_));

				if (isFilePath_)
				{
					return;
				}
				consumer_->initialize(format_desc, channel_layout);

				if (separate_key_)
				{
					boost::filesystem::path fill_file(path_);
					auto without_extension = u16(fill_file.parent_path().string() + "/" + fill_file.stem().string());
					auto key_file = without_extension + L"_A" + u16(fill_file.extension().string());

					key_only_consumer_.reset(new ffmpeg_consumer(u8(key_file), "",options_, mono_streams_));
					key_only_consumer_->initialize(format_desc, channel_layout);
				}
			}

			int64_t presentation_frame_age_millis() const override
			{
				return consumer_ ? static_cast<int64_t>(consumer_->presentation_frame_age_millis()) : 0;
			}

			std::future<bool> send(core::const_frame frame) override
			{
				consumer_->send(frame);
				if (separate_key_)
					key_only_consumer_->send(frame.key_only());

				return make_ready_future(true);
			}

			std::wstring print() const override
			{
				return consumer_ ? consumer_->print() : L"[ffmpeg_consumer]";
			}

			std::wstring name() const override
			{
				return L"ffmpeg";
			}

			boost::property_tree::wptree info() const override
			{
				boost::property_tree::wptree info;

				info.add(L"type", L"ffmpeg");
				info.add(L"path", u16(path_));
				info.add(L"separate_key", separate_key_);
				info.add(L"mono_streams", mono_streams_);

				return info;
			}

			bool has_synchronization_clock() const override
			{
				return false;
			}

			int buffer_depth() const override
			{
				return -1;
			}

			int index() const override
			{
				return compatibility_mode_ ? 200 : 100000 + consumer_index_offset_;
			}

			core::monitor::subject& monitor_output() override
			{
				return consumer_->monitor_output();
			}

			//wxg record 初始化可以多次，录制过程中初始化实际没有影响
			bool record_init(std::wstring strFileName) const override
			{
				if (consumer_->is_recording() || !isFilePath_)
					return false;

				std::string fileNameTem = u8(strFileName);
				size_t pos = fileNameTem.find('.');
				size_t len = fileNameTem.length();
				std::string newFileName;
				//TODO 暂不处理同时录制多个的文件名问题,只能有一个录制通道

				if (pos > 0 && (pos < len))
				{
					newFileName = fileNameTem;   //已经带有后缀
					//newFileName = fileNameTem.substr(0, pos) +"_" + path_ + fileNameTem.substr(pos, len - pos);
				}
				else
				{
					//从配置文件读后缀
					size_t pos = path_.find('.');
					if (pos == std::string::npos)
						pos = 0;
					newFileName = u8(strFileName) + path_.substr(pos);
				}
				
				consumer_->set_newPath_options(newFileName, options_);
				return true;
			}

			bool record_start() const override
			{
				if (consumer_->is_recording() || !isFilePath_)
					return false;

				consumer_->set_recordStatus(true);
				consumer_->initialize_record(format_desc_, chn_layout_);
				return true;
			}

			bool record_stop() const override
			{
				if (!consumer_->is_recording() || !isFilePath_)
					return false;

				consumer_->uninitiate_record();
				consumer_->set_recordStatus(false);
				return true;
			}

			bool is_recording() const override
			{
				return consumer_->is_recording();
			}

			uint32_t getRecordFrames(std::wstring& fileName) const override
			{
				if(is_recording())
					return consumer_->getRecordFrames(fileName);
				return 0;
			}

		};

		void describe_ffmpeg_consumer(core::help_sink& sink, const core::help_repository& repo)
		{
			sink.short_description(L"For streaming/recording the contents of a channel using FFmpeg.");
			sink.syntax(L"FILE,STREAM [filename:string],[url:string] {-[ffmpeg_param1:string] [value1:string] {-[ffmpeg_param2:string] [value2:string] {...}}} {[separate_key:SEPARATE_KEY]} {[mono_streams:MONO_STREAMS]}");
			sink.para()->text(L"For recording or streaming the contents of a channel using FFmpeg");
			sink.definitions()
				->item(L"filename", L"The filename under the media folder including the extension (decides which kind of container format that will be used).")
				->item(L"url", L"If the filename is given in the form of an URL a network stream will be created instead of a file on disk.")
				->item(L"ffmpeg_paramX", L"A parameter supported by FFmpeg. For example vcodec or acodec etc.")
				->item(L"separate_key", L"If defined will create two files simultaneously -- One for fill and one for key (_A will be appended).")
				->item(L"mono_streams", L"If defined every audio channel will be written to its own audio stream.");
			sink.para()->text(L"Examples:");
			sink.example(L">> ADD 1 FILE output.mov -vcodec dnxhd");
			sink.example(L">> ADD 1 FILE output.mov -vcodec prores");
			sink.example(L">> ADD 1 FILE output.mov -vcodec dvvideo");
			sink.example(L">> ADD 1 FILE output.mov -vcodec libx264 -preset ultrafast -tune fastdecode -crf 25");
			sink.example(L">> ADD 1 FILE output.mov -vcodec dnxhd SEPARATE_KEY", L"for creating output.mov with fill and output_A.mov with key/alpha");
			sink.example(L">> ADD 1 FILE output.mxf -vcodec dnxhd MONO_STREAMS", L"for creating output.mxf with every audio channel encoded in its own mono stream.");
			sink.example(L">> ADD 1 STREAM udp://<client_ip_address>:9250 -format mpegts -vcodec libx264 -crf 25 -tune zerolatency -preset ultrafast",
				L"for streaming over UDP instead of creating a local file.");
		}

		spl::shared_ptr<core::frame_consumer> create_ffmpeg_consumer(
			const std::vector<std::wstring>& params, core::interaction_sink*, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			if (params.size() < 1 || (!boost::iequals(params.at(0), L"STREAM") && !boost::iequals(params.at(0), L"FILE")))
				return core::frame_consumer::empty();

			auto params2 = params;
			bool separate_key = get_and_consume_flag(L"SEPARATE_KEY", params2);
			bool mono_streams = get_and_consume_flag(L"MONO_STREAMS", params2);
			auto compatibility_mode = boost::iequals(params.at(0), L"FILE");
			auto path = u8(params2.size() > 1 ? params2.at(1) : L"");
			auto path_redundancy = u8(L"");
			auto args = u8(boost::join(params2, L""));

			return spl::make_shared<ffmpeg_consumer_proxy>(path, path_redundancy, args, separate_key, mono_streams, compatibility_mode);
		}

		spl::shared_ptr<core::frame_consumer> create_preconfigured_ffmpeg_consumer(
			const boost::property_tree::wptree& ptree, core::interaction_sink*, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			return spl::make_shared<ffmpeg_consumer_proxy>(
				u8(ptree_get<std::wstring>(ptree, L"path")),
				u8(ptree.get<std::wstring>(L"path-redundancy",L"")),
				u8(ptree.get<std::wstring>(L"args", L"")),
				ptree.get<bool>(L"separate-key", false),
				ptree.get<bool>(L"mono-streams", false),
				false
				);
		}

	}
}
