#pragma once
#include "ParserVideo.h"
#include "Parser291M.h"
#include <atomic>

namespace caspar {
	namespace sdiopi_20226 {
		class CParserBT601
		{
		public:
			CParserBT601();
			~CParserBT601();

		private:
			unsigned char* m_pBuffer;
			int            m_length;
			int            m_offset;

		private:
			const int  m_width_video_10 = 720 * 2 * 10 / 8;
			const int  m_width_video = 720 * 2;
			const int  m_width_ancillary_10 = (280 + 8) * 10 / 8;;

		private:
			const int  m_limit_left = (720 * 2 + 280 + 8) * 625 * 10 / 8;     ////(2640 + 12) * 1125 * 20 / 8;
			const int  m_limit_right = (m_limit_left / 1376 + 1) * 1376;


		public:
			int Receive(unsigned char* p, int len)
			{
				m_offset = 0;
				m_pBuffer = p;
				m_length = len;
				return 0;
			}
			int Process();
			void GetVideo(unsigned char* p) { return m_parserVideo.GetVideo(p, m_width_video * 576); }
			void GetAudio(unsigned char* p, int channel) { return m_parserAncillaryData.GetAudio(p, channel); }
			void SetVideoNotify(RECEIVE_DATA rd, void* p)
			{
				m_parserVideo.SetVideoNotify(rd, p);
			}
			void SetAudioNotify(RECEIVE_DATA rd, void* p)
			{
				m_parserAncillaryData.SetAudioNotify(rd, p);
			}
			int  GetDecodeCount() { return m_decode_count; }

		private:
			void getActiveVideoCode()
			{
				if (m_pBuffer[m_offset] == 0xFF)
				{
					if (m_pBuffer[m_offset + 1] == 0xC0)
					{
						if (m_pBuffer[m_offset + 2] == 0x00)
						{
							m_field_number = FIELD_NUMBER(m_pBuffer[m_offset + 3] & 0x1);
							m_field_blanking = FIELD_OR_BLANKING((m_pBuffer[m_offset + 4] & 0x80) >> 7);
							m_line_blanking = EAV_OR_SAV((m_pBuffer[m_offset + 4] & 0x40) >> 6);
						}
					}
				}
			};

			void init() { m_field_blanking = BLANKING;	m_line_blanking = EAV; }  //帧头包XY=0x2d8； 
																				  //F=0 first field；
																				  //V=1 field blanking
																				  //H=1 EAV
																				  //第二个标志XY=0x2AC


		private:
			enum FIELD_NUMBER
			{
				FIELD_0 = 0,
				FIELD_1
			}  m_field_number;

			enum FIELD_OR_BLANKING
			{
				FIELD = 0,
				BLANKING
			}  m_field_blanking;

			enum EAV_OR_SAV
			{
				SAV = 0,     //1440
				EAV          //280(PAL), 276(NTSC) 
			}  m_line_blanking;

			CParserVideo    m_parserVideo;
			CParser291M     m_parserAncillaryData;
			std::atomic<int>        m_decode_count;
		};
	}
}