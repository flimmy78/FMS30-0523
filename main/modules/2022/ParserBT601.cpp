
#include <stdio.h>
#include "ParserBT601.h"
#include <atomic>

namespace caspar {
	namespace sdiopi_20226 {
		CParserBT601::CParserBT601() : m_decode_count(0)
		{
			init();
		}


		CParserBT601::~CParserBT601()
		{
		}

		int CParserBT601::Process()
		{
			if ((m_length >= m_limit_left) && (m_length <= m_limit_right))  //if the frame doesnot lost any packet
			{
				m_offset = 0;
				//int activeline = 0;
				for (int i = 0; i < 625; ++i) {
					getActiveVideoCode();
					m_parserAncillaryData.Add(&(m_pBuffer[m_offset + 5]), m_width_ancillary_10 - 5 * 2);  //exclude EAV and SAV
					if (m_field_blanking == FIELD) {
						//m_parserAncillaryData.Add(&(m_pBuffer[m_offset + 5]), m_width_ancillary - 5*2);  //exclude EAV and SAV
						m_parserVideo.Add(&(m_pBuffer[m_offset + m_width_ancillary_10]), m_width_video_10);
						//activeline++;
					}
					m_offset += m_width_ancillary_10;
					m_offset += m_width_video_10;
				}
				m_parserVideo.Flush();
				m_parserAncillaryData.Flush(PAL);
				++m_decode_count;
			}
			return m_decode_count;
		}
	}
}