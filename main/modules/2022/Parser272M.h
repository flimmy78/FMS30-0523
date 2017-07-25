#pragma once
#include <mutex>
#include "common.h"
namespace caspar {
	namespace sdiopi_20226 {
		class CParser272M
		{
		public:
			CParser272M();
			~CParser272M();

		public:
			int  Receive(unsigned char* p, int len, int group);   //once time. to receive three shorts by X,X+1,X+2, totally 6 bytes.
			void Flush();
			void GetAudio(unsigned char* p, int channel) {
				std::lock_guard<std::mutex> lock(m_mutex);
				memcpy(p, &(m_charResult[channel - 1]), AUDIO_SAMPLES_PER_FRAME_CHANNEL * 2);
			};
			void SetAudioNotify(RECEIVE_DATA rd, void* p)
			{
				receive_audio = rd;
				m_caller = p;
			}

		private:
			//audio data packet  基本每一行1个
			//audio control packet  1个/场或帧，48K音频可以没有
			//extended data packet  紧跟在audio data packet后，并在同一个扫描行内   
			int            m_offset[AUDIO_GROUPS];
			unsigned char* m_pBuffer[AUDIO_GROUPS];

			//9.2 Data packet distribution is further constrained by defining a minimum receiver buffer size as explained in
			//	annex A.The minimum receiver buffer size is 64 samples per active channel.
			//char m_charResult[8][64*3];   //每个扫描行3-4个采样
			unsigned char m_charResult[AUDIO_CHANNELS][AUDIO_SAMPLES_PER_FRAME_CHANNEL * 2];  //2 channels、

		private:
			std::mutex m_mutex;
			RECEIVE_DATA  receive_audio;
			void* m_caller;

		};

	}
}