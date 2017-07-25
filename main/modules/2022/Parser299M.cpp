
#include "Parser299M.h"
#include "common.h"

namespace caspar {
	namespace sdiopi_20226 {

		CParser299M::CParser299M() : receive_audio(nullptr)
		{
			memset((unsigned char*)m_offset, 0, AUDIO_GROUPS * sizeof(int));
			for (int i = 0; i < AUDIO_GROUPS; i++)
			{
				m_offset[i] = 0;
				m_pBuffer[i] = new unsigned char[AUDIO_SAMPLES_PER_FRAME_CHANNEL * 2 * 16];
				memset(m_pBuffer[i], 0, AUDIO_SAMPLES_PER_FRAME_CHANNEL * 2 * 16);
			}
		}


		CParser299M::~CParser299M()
		{
			for (int i = 0; i < AUDIO_GROUPS; i++)
			{
				if (m_pBuffer[i] != NULL) {
					delete m_pBuffer[i];
					m_pBuffer[i] = NULL;
				}
			}
		}

		int CParser299M::Receive(unsigned char* p, int len, int group)
		{
			//group isnot a subscript
			if (group < 1) return 0;
			memcpy(m_pBuffer[group - 1] + m_offset[group - 1], p, len);
			m_offset[group - 1] += len;
			//if (group == 1)
			//	OutputString("group=%d\n", m_offset[0]);
			return 0;
		}


		//SMPTE 299M-2004 Table 3 - Bit-assignment of audio data (CHn) 
		void CParser299M::Flush()
		{
			//printf("flush a\n");
				std::lock_guard<std::mutex> lock(m_mutex);

				for (int n = 0; n < AUDIO_GROUPS; n++) {
					unsigned char* p = m_pBuffer[n];
					int group_buffer_offset = m_offset[n];
					int co[4];
					memset(co, 0, sizeof(int) * 4);
					for (int m = 0; m < group_buffer_offset; m += 32)
					{
						unsigned char* pbase = p + m;
						for (int k = 0; k < 4; k++) {
							int channel = n * 4 + k;
							m_charResult[channel][co[k]++] = (pbase[2] >> 4) + ((pbase[4] & 0xF) << 4);
							m_charResult[channel][co[k]++] = (pbase[4] >> 4) + (pbase[6] << 4);
							pbase += 8;
						}
					}//
					//if (n==3)
					//OutputString("co: c1=%d, c2=%d, c3=%d, c4=%d\n", co[0], co[1], co[2], co[3]);
				}

				for (int i = 0; i < AUDIO_GROUPS; i++)
				{
					m_offset[i] = 0;
				}
				if (receive_audio) {
					
					receive_audio(m_charResult, AUDIO_CHANNELS * AUDIO_SAMPLES_PER_FRAME_CHANNEL * 2, m_caller);
				}

			return;

		}
	}
}