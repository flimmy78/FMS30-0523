
#include <cstring>
#include "ParserVideo.h"
namespace caspar {
	namespace sdiopi_20226 {
		CParserVideo::CParserVideo() : receive_video(nullptr), m_caller(nullptr)
		{
			m_offset = 0;
			m_frame = new unsigned char[4800 * 1125];     //4800 is the length of HD Line
			memset(m_frame, 0, 4800 * 1125);
			m_shrink = new unsigned char[4800 * 1125];
			memset(m_shrink, 0, 4800 * 1125);
		}


		CParserVideo::~CParserVideo()
		{
			if (m_frame) {
				delete[]m_frame;
				m_frame = NULL;
			}
			if (m_shrink) {
				delete[]m_shrink;
				m_shrink = NULL;
			}
		}

		void CParserVideo::Add(unsigned char* d, int len)
		{
			memcpy(&(m_frame[m_offset]), d, len);
			m_offset += len;
		}

		void CParserVideo::shrink()
		{
			//A 1111 1111 
			//B 0011 1111 
			//C 1100 1111 
			//D 1111 0011 
			//E 1111 1100

			//A 0011 1111 
			//B 1100 1111 
			//C 1111 0011 
			//D 1111 1100 
			//E 1111 1111 
			{


			
			std::lock_guard<std::mutex> lock(m_mutex);
			/*for (int i = 0; i < m_offset; i+=5)
			{
				int so = 4 * i / 5;
				m_shrink[so] = (m_frame[i] << 2) + ((m_frame[i + 1] & 0x0C0) >> 6);
				m_shrink[so + 1] = (m_frame[i + 1] << 4) + ((m_frame[i + 2] & 0x0F0) >> 4);
				m_shrink[so + 2] = (m_frame[i + 2] << 6) + ((m_frame[i + 3] & 0x0FC) >> 2);
				m_shrink[so + 3] = m_frame[i + 4];
			}*/
			for (int i = 0; i < m_offset; i += 5)
			{
				int so = 4 * i / 5;
				m_shrink[so] = m_frame[i];
				m_shrink[so + 1] = (m_frame[i + 1] << 2) + ((m_frame[i + 2] & 0x0C0) >> 6);
				m_shrink[so + 2] = (m_frame[i + 2] << 4) + ((m_frame[i + 3] & 0x0F0) >> 4);
				m_shrink[so + 3] = (m_frame[i + 3] << 6) + ((m_frame[i + 4] & 0x0FC) >> 2);
			}

			//!@#$  
			//YVYU  or  YUY2 ?  
			/*int border = m_offset * 4 / 5;
			for (int i = 0; i < border; i += 4)
			{
				unsigned char u = m_shrink[i + 1];
				m_shrink[i + 3] = m_shrink[i + 1];
				m_shrink[i + 1] = u;
			}*/
			}
			if (receive_video)
				receive_video(m_shrink, m_offset * 8 / 10, m_caller);

			
		}

		void CParserVideo::Flush()
		{
			shrink();
			m_offset = 0;

		}
	}
}
