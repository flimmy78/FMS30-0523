#pragma once
#include <mutex>
#include "common.h"

namespace caspar {
	namespace sdiopi_20226 {
		class CParserVideo
		{
		public:
			CParserVideo();
			~CParserVideo();

		public:
			void Add(unsigned char* d, int len);
			void Flush();
			void GetVideo(unsigned char* p, int size) {
				std::lock_guard<std::mutex> lock(m_mutex);
				memcpy(p, m_shrink, size);
			};
			void SetVideoNotify(RECEIVE_DATA rd, void* p)
			{
				receive_video = rd;
				m_caller = p;
			}

		private:
			unsigned char*  m_frame;
			unsigned char*  m_shrink;
			int    m_offset;
			int    m_width;
			void   shrink();
			RECEIVE_DATA  receive_video;
			void*  m_caller;
		private:
			std::mutex m_mutex;
		};
	}
}
