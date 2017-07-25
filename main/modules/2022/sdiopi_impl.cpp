#include "sdiopi_impl.h"
#include "c20226Service.h"
#include <tbb/concurrent_queue.h>
#include <common/memcpy.h>
#include <common/timer.h>
#include "common.h"
#include <mutex>
#include "udpboost.h"
extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
}

namespace caspar {	namespace sdiopi_20226 {
	
	enum datatype{
		MISS_AUDIO,
		MISS_VIDEO,
		FULL
	};
	struct Stu_2022_quedata
	{
		unsigned char*					g_buffer_video;
		unsigned char*					g_buffer_audio;
	};
	struct sdiopi_interface_20226::impl
	{
		C20226Service*						service_ =nullptr;
		UdpSocket  *						sock_ = nullptr;
		SdiOpineed							needs_;
		tbb::cache_aligned_allocator<uint8_t>  cc_memory_pool;
		std::shared_ptr<SwrContext>				swr_;
		unsigned char*					g_buffer_video;
		unsigned char*					g_buffer_audio;
		uint8_t *						datachannel_[16];
		tbb::atomic<datatype>				complete_;
		//tbb::concurrent_bounded_queue<Stu_2022_quedata>	data_buffer_;
		std::list<Stu_2022_quedata> data_buffer_;
		tbb::atomic<bool>			data_lock;
		tbb::atomic<bool>									is_running_;
		boost::thread										thread_;
		
		std::mutex						m_mutex;
		caspar::timer										tick_timer;
		impl(SdiOpineed needs)
		:
		needs_(needs)
		{
			//data_buffer_.set_capacity(4);
			data_lock = true;
			CASPAR_LOG(info) << L" sdi-20226 producer creat.";
			GetResolution();
			g_buffer_video = (unsigned char *)malloc(needs.width*needs.higth * 2);
			g_buffer_audio = (unsigned char *)malloc(16 * 1920 * 2);
			complete_ = FULL;
			//编译不过去，主动调用的方式也可以的

			for (int i = 0;i < 16;i++)
			{
				datachannel_[i] = (uint8_t*)malloc(1920 * sizeof(short));
			}
			
			int outchannel = (int)av_get_default_channel_layout(needs.channel);
			int intchannel = (int)av_get_default_channel_layout(needs.channel);
			swr_ = {
				swr_alloc_set_opts(
					nullptr,
					outchannel,
					AV_SAMPLE_FMT_S32,
					48000,
					intchannel,
					AV_SAMPLE_FMT_S16,
					48000,
					0,
					nullptr),
				[](SwrContext* p)
			{
				swr_free(&p);
			}
			};
			swr_init(swr_.get());
			if (service_)
			{
				service_->SetVideoNotify(set_func_video, this);
				service_->SetAudioNotify(set_func_audio, this);
				service_->Run();
			}
			else
			{
				CASPAR_THROW_EXCEPTION(caspar_exception()
					<< msg_info(L"init sdi iml error")
					<< boost::errinfo_api_function("sdiopi_interface_20226"));
				release();
			}

		//	thread_ = boost::thread([this] {run(); });
			
		}
		//void run()
		//{
		//	while (true)
		//	{
		//		//PutVideo(NULL,1920*1080*2);
		//		//PutAudio(NULL,1920*16*2);
		//		boost::this_thread::sleep_for(boost::chrono::milliseconds(40));
		//	}
		//}
		static void set_func_video(void *p, int size,void * oj)
		{
			sdiopi_interface_20226::impl * pt = (sdiopi_interface_20226::impl*)oj;
			pt->PutVideo(p,size);
		}
		static void set_func_audio(void *p, int size, void * oj)
		{
			sdiopi_interface_20226::impl * pt = (sdiopi_interface_20226::impl*)oj;
			//pt->PutAudio(p, size);
		}

		void PutVideo(void *p,int size)
		{/*
			if (complete_ == FULL)
			{
				memcpy(g_buffer_video, p, size);
				complete_ = MISS_AUDIO;
			}
			else if (complete_ == MISS_VIDEO)
			{*/
				//push();
				
				Stu_2022_quedata dp;
				dp.g_buffer_video = (unsigned char *)malloc(size);
				dp.g_buffer_audio = (unsigned char *)malloc(1920*16*2);
				memcpy(dp.g_buffer_video, p, size);
				memcpy(dp.g_buffer_audio,datachannel_[0], 1920 * 16 * 2);
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					data_buffer_.push_back(dp);

				}
				
				/*		complete_ = FULL;
					}*/
			//time_t t2 = time(NULL);
			//printf("VIDEO = %d\n", t2 - t);

		}
		void PutAudio(void *p, int size)
		{

			if (complete_ == FULL)
			{
				memcpy(datachannel_[0], p, size);
				complete_ = MISS_VIDEO;
			}
			else if (complete_ == MISS_AUDIO)
			{
				
				//push();
				{
					Stu_2022_quedata dp;
					dp.g_buffer_video = (unsigned char *)malloc(needs_.width*needs_.higth * 2);
					dp.g_buffer_audio = (unsigned char *)malloc(size);
					memcpy(dp.g_buffer_audio, p, size);
					memcpy(dp.g_buffer_video, g_buffer_video, needs_.width*needs_.higth * 2);
					{
						std::lock_guard<std::mutex> lock(m_mutex);
						data_buffer_.push_back(dp);

					}
				}
				
				complete_ = FULL;
			}
			//CASPAR_LOG(info)<<tick_timer.elapsed();
			//printf("PutAudio %f\n", tick_timer.elapsed());
			tick_timer.restart();
		}

		void GetResolution()
		{
			switch (needs_.format)
			{
			case caspar::core::video_format::pal:
				service_ = new C20226Service(needs_.host, needs_.addr, needs_.port, PAL);
				break;
			case caspar::core::video_format::x1080i5000:
				service_ = new C20226Service(needs_.host, needs_.addr, needs_.port, PAL1080);
				break;
			case caspar::core::video_format::x1080p2500:
				service_ = new C20226Service(needs_.host, needs_.addr, needs_.port, OTHER);
				break;
			default:
				CASPAR_LOG(error) << L"Unspecified or invalid resolution format.";
				service_ = new C20226Service(needs_.host, needs_.addr, needs_.port, OTHER);
				break;
			}
		}
		void release()
		{
			if (service_ != nullptr)
			{
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
				delete service_;
				service_ = nullptr;
			}
			if (g_buffer_video!=nullptr)
			{
				free(g_buffer_video);
			}
			if (g_buffer_audio!=nullptr)
			{
				free(g_buffer_audio);
			}
			for (int i = 0;i < needs_.channel;i++)
			{
				free(datachannel_[i]);
			}
		}

		~impl()
		{
			release();
			CASPAR_LOG(info) << L" sdi2022 iml release.";
		}

		void push(std::shared_ptr<Sdi2022Frame>  &desframe,unsigned char * g_buffer_video,unsigned char * g_buffer_audio)
		{

			if (g_buffer_audio==nullptr|| g_buffer_audio == nullptr)
			{
				if (g_buffer_video)
					free(g_buffer_video);
				if (g_buffer_audio)
				{
					free(g_buffer_audio);
				}
				return;
			}
			auto frame = std::make_shared<Sdi2022Frame>();
			
			uint8_t* pv = (uint8_t*)cc_memory_pool.allocate(needs_.width*needs_.higth * 2);
			frame->pvideo = std::shared_ptr<uint8_t>(pv, [&](uint8_t* p) {cc_memory_pool.deallocate(p, needs_.width*needs_.higth * 2);});


			uint8_t* pa = (uint8_t*)cc_memory_pool.allocate(1920 * needs_.channel * 4);
			frame->paudio = std::shared_ptr<uint8_t>(pa, [&](uint8_t* p) {cc_memory_pool.deallocate(p, 1920 * 16 * 4); });

			//video
			uint8_t * pT = g_buffer_video;
			uint8_t * pB = g_buffer_video + (needs_.width*needs_.higth);//高的一般*2还是高
			tbb::parallel_for<size_t>(0, needs_.higth, [&](size_t y)
			{
				if (y % 2)
				{
					std::memcpy(frame->pvideo.get() + y * needs_.width * 2, pB + (y / 2)*needs_.width * 2, needs_.width * 2);
				}
				else
				{
					std::memcpy(frame->pvideo.get() + y *  needs_.width * 2, pT + (y / 2)*needs_.width * 2, needs_.width * 2);
				}
			});
			/*for (int y = 0;y<needs_.higth;y++)
			{
				if (y % 2)
				{
					fast_memcpy(frame->pvideo.get() + y * needs_.width * 2, pB + (y / 2)*needs_.width * 2, needs_.width * 2);
				}
				else
				{
					fast_memcpy(frame->pvideo.get() + y *  needs_.width * 2, pT + (y / 2)*needs_.width * 2, needs_.width * 2);
				}
			}*/
			//fast_memcpy(frame->pvideo.get(), pT, needs_.width* needs_.higth * 2);
			//audio
			int n = 0;
			for (int i = 0; i < 1920 * sizeof(short)*/*needs_.channel*/16;)
			{
				for (int m = 0;m < needs_.channel;m++)
				{
					unsigned short  s1 = datachannel_[m][n];
					unsigned short	s2 = datachannel_[m][n + 1];
					unsigned short  s3 = s1 + (s2 << 8);

					short dtl = (short)s3;
					std::memcpy(g_buffer_audio + i, &dtl, sizeof(short));
					i += 2;
				}
				n += 2;
			}
			uint8_t * vest = frame->paudio.get();
			const uint8_t **in = const_cast<const uint8_t**>((uint8_t**)&g_buffer_audio);
			uint8_t *out[] = { reinterpret_cast<uint8_t*>(vest) };

			const auto channel_samples = swr_convert(
				swr_.get(),
				out,
				1920 * needs_.channel * 4,
				in,
				1920);
			desframe = frame;
			//frame_buffer_.push(frame);
		}
		bool get_frame(std::shared_ptr<Sdi2022Frame>  &desFrame)//40ms
		{
			Stu_2022_quedata sd;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				if (data_buffer_.size() > 0)
				{
					sd = data_buffer_.front();
					data_buffer_.pop_front();
					//printf("..%d..",data_buffer_.size());
				}
				else
					return false;
			}
			
			push(desFrame, sd.g_buffer_video, sd.g_buffer_audio);
			free(sd.g_buffer_audio);
			free(sd.g_buffer_video);
			return true;
		}

	};


	sdiopi_interface_20226::sdiopi_interface_20226(SdiOpineed pneed)
	:impl_(new impl(pneed))
	{
	}
	bool sdiopi_interface_20226::get_frame(std::shared_ptr<Sdi2022Frame>  & frame) { return impl_->get_frame(frame); }

}}