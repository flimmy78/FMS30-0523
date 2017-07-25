#pragma once
#include "common.h"
#include "Parser272M.h"
#include "Parser299M.h"
namespace caspar {
	namespace sdiopi_20226 {
		class CParser291M
		{
		public:
			CParser291M();
			~CParser291M();

		public:
			//void Add(unsigned char d);
			void Add(unsigned char* d, int len);
			void Flush(FRAME f);
			//void Flush8();
			void GetAudio(unsigned char* p, int channel) {
				if (m_frametype == PAL)
					m_parser272.GetAudio(p, channel);
				else
					m_parser299.GetAudio(p, channel);
			};
			void SetAudioNotify(RECEIVE_DATA rd, void* p)
			{
				m_parser272.SetAudioNotify(rd, p);
				m_parser299.SetAudioNotify(rd, p);
			}

		private:
			unsigned char*  m_frame;
			int    m_offset;
			unsigned short m_audio[1440];  //in SD, each anciliary space contains 280 ANC words, they carry at most 280/3=100 samples

			const int m_width_ancillary_10 = 720 * 2 * 10 / 8 - 20 - 10; //in HD, each anciliary space contains (2640-1920)*2=1440 ANC words, they carry at most 1440/4=360 samples 
																		 // - 20 - 10 mean that subtract (EAV+LN+CRC+SAV)
																		 //1770    1770*8=14160
																		 //1770*1125=1991250byte
			int    m_anc_count;
			//unsigned char*  m_shrink;
			//int    m_shrink_offset;
			//void   shrink();

		private:
			CParser272M m_parser272;
			CParser299M m_parser299;
			void flush_sd();
			void flush_hd();
			FRAME m_frametype;
		};

	}
}