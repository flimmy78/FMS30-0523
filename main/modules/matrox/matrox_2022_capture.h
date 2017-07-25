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
		
		class matrox_2022_capture
		{
		public:
			/*matrox_interface_producer(
				int card,
				int sdi,
				std::wstring ratio_s,
				core::video_format format,
				int NeedAChannel
			);*/
			matrox_2022_capture(
				core::video_format format,
				int NeedAChannel,
				producer_need need
			);
			~matrox_2022_capture() {}
			bool get_frame(FrameforProducer &);
			int _GetChannels();
		private:
			struct impl;
			spl::shared_ptr<impl> impl_;
		};

	}
}