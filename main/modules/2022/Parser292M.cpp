
#include <stdio.h>
#include "Parser292M.h"

namespace caspar {
	namespace sdiopi_20226 {
		CParser292M::CParser292M() : m_decode_count(0)
		{
			init();
		}


		CParser292M::~CParser292M()
		{
		}

		int err = 0;
		int CParser292M::Process()
		{
			
			//boost::int_least64_t _start_time = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
			//printf("pr 1\n");
			if ((m_length >= m_limit_left) && (m_length <= m_limit_right))
			{
				//printf("pr 2\n");
				m_offset = 0;
				for (int i = 0; i < 1125; ++i) {
					getActiveVideoCode();
					//20 EAV+LN+CRC
					//10 SAV
					m_parserAncillaryData.Add(&(m_pBuffer[m_offset + 20]), m_width_ancillary_10 - 20 - 10);  //exclude EAV and SAV
					if (m_field_blanking == FIELD) {
						//m_parserAncillaryData.Add(&(m_pBuffer[m_offset + 20]), m_width_ancillary - 20 - 10);  //exclude EAV and SAV
						m_parserVideo.Add(&(m_pBuffer[m_offset + m_width_ancillary_10]), m_width_video_10);
					}
					m_offset += m_width_ancillary_10;
					m_offset += m_width_video_10;
				}
				m_parserVideo.Flush();
				m_parserAncillaryData.Flush(PAL1080);
				++m_decode_count;
			}
			else
			{
				printf("err %d \n", ++err);   // m_length);
			}
			

			return m_decode_count;;
		}
	}
}