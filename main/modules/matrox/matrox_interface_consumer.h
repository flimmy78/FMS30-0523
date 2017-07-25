#pragma once
#include <core/video_format.h>

#include <common/forward.h>
#include <common/memory.h>
#include <common/cache_aligned_vector.h>
#include <common/array.h>

#include <core/frame/frame_visitor.h>
#include <core/monitor/monitor.h>

#include <vector>
#include <cstdint>
#include "common.h"
namespace caspar {
	namespace matrox {
		/*struct mvsParameters
		{
			short stCard;
			short stSdi;
			core::video_format	stformat;
			short stOutChannel;
			std::wstring stRatio;
			bool stIsVanc;
			bool stIsKey;

		};*/
		class matrox_interface_consumer
		{
		public:
			matrox_interface_consumer(consumer_need need, core::video_format format,int  channels);
			~matrox_interface_consumer() {}
// 			bool send_frame(MatroxFrame &);
// 			int _GetChannels();
			void _ProcessVanc(void * pvideo, void * paudio, void*pvideo1, void *paudio1, int nAR, int nCmd);
			bool _IsFieldBased();
		private:
			struct impl;
			spl::shared_ptr<impl> impl_;
		};

	}
}