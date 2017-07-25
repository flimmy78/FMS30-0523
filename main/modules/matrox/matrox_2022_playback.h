#pragma once
#include <core/video_format.h>

#include <common/forward.h>
#include <common/memory.h>
#include <common/cache_aligned_vector.h>
#include <common/array.h>

#include <core/frame/frame_visitor.h>
#include <core/monitor/monitor.h>
#include "common.h"
namespace caspar {
	namespace matrox {
		class matrox_2022_playback
		{
		public:
			matrox_2022_playback(consumer_need need,core::video_format format, int channels);
			~matrox_2022_playback() {}
			void send(void *pvideo,void * pvideo1,void * paudio, void * paudio1);
			bool _IsFieldBased();
		private:
			struct impl;
			spl::shared_ptr<impl> impl_;
		};

	}
}