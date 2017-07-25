
#include "Parser272M.h"
#include "common.h"


namespace caspar {
	namespace sdiopi_20226 {

		CParser272M::CParser272M() : receive_audio(nullptr), m_caller(nullptr)
		{
			//m_pBuffer = new unsigned char[24 * 48000 / 25];  //accept 1 group
			memset((unsigned char*)m_offset, 0, AUDIO_GROUPS * sizeof(int));
			//m_pBuffer = new unsigned char[AUDIO_SAMPLES_PER_FRAME_GROUP*16*6];   //each sample include three shorts by X,X+1,X+2, totally 6 bytes.
			for (int i = 0; i < AUDIO_GROUPS; i++)
			{
				m_offset[i] = 0;
				m_pBuffer[i] = new unsigned char[AUDIO_SAMPLES_PER_FRAME_CHANNEL * 4 * 6];
				memset(m_pBuffer[i], 0, AUDIO_SAMPLES_PER_FRAME_CHANNEL * 4 * 6);
			}
		}


		CParser272M::~CParser272M()
		{
			for (int i = 0; i < AUDIO_GROUPS; i++)
			{
				if (m_pBuffer[i] != NULL) {
					delete m_pBuffer[i];
					m_pBuffer[i] = NULL;
				}
			}
		}

		int CParser272M::Receive(unsigned char* p, int len, int group)
		{
			//group isnot a subscript
			if (group < 1) return 0;
			memcpy(m_pBuffer[group - 1] + m_offset[group - 1], p, len);
			m_offset[group - 1] += len;

			return 0;
		}

		void CParser272M::Flush()
		{
			{
			std::lock_guard<std::mutex> lock(m_mutex);

			for (int n = 0; n < AUDIO_GROUPS; n++) {
				unsigned char* p = m_pBuffer[n];
				int group_buffer_offset = m_offset[n];
				int co[4];
				memset(co, 0, sizeof(int) * 4);
				for (int m = 0; m < group_buffer_offset; m += 6)
				{
					unsigned char y = p[m] & 0x06;   //ch1+ch0
					y >>= 1;
					int channel = n * 4 + y;
					m_charResult[channel][co[y]++] = (p[m + 2] & 0x3F) << 2;
					unsigned char temp = ((p[m + 2] & 0xC0) >> 6) + ((p[m + 3] & 0x1) << 2);
					m_charResult[channel][co[y]++] = ((p[m + 4] & 0x1F) << 3) + temp;
				}//
				//if (n==0)
				//  OutputString("co: c1=%d, c2=%d, c3=%d, c4=%d\n", co[0], co[1], co[2], co[3]);
			}

			for (int i = 0; i < AUDIO_GROUPS; i++)
			{
				m_offset[i] = 0;
			}
		}
			if (receive_audio)
				receive_audio(m_charResult, AUDIO_CHANNELS * AUDIO_SAMPLES_PER_FRAME_CHANNEL * 2, m_caller);

			return;
		}
	}
}