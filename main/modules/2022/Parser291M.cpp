

#include "Parser291M.h"
#include <algorithm>
#include <assert.h>
namespace caspar {
	namespace sdiopi_20226 {

#define Extract_Bits(p,x,y,z)   (p[x]&y)<<z+p[x+1]>>(8-z)    //(X)??? _From_WORD  
		//#define Extract_10_Bits(p,x,y)    (((p[x] << 8) + p[x + 1]) >> y) & 0x3FF
#define Extract_10_Bits(p,x,y)    (((p[x] << 8) + p[x + 1]) >> (y - 2)) & 0x3FF
#define Extract_3ANC(p,x,y)    (((((((p[x] << 8) + p[x+1]) << 8) + p[x+2])<<8) + p[x+3])<<8+p[x+4])>>y
		unsigned int extract_3ANC(unsigned char* p, int x, int y)
		{
			unsigned long long mid = 0;
			mid = p[x];      mid <<= 8;
			mid += p[x + 1];  mid <<= 8;
			mid += p[x + 2];  mid <<= 8;
			mid += p[x + 3];  mid <<= 8;
			mid += p[x + 4];
			mid >>= (32 + y - 30);
			unsigned int re = mid & 0x3FFFFFFF;
			return re;
		}

		CParser291M::CParser291M() : m_frametype(PAL)
		{
			m_frame = new unsigned char[1800 * 1080 * 2]; //1800 is the length of ancillary data at one Line
			m_offset = 0;
			//m_shrink = new unsigned char[sizeof(m_frame)*8/10];
			//m_shrink_offset = 0;
		}


		CParser291M::~CParser291M()
		{
			if (m_frame)
				delete[]m_frame;
			//if (m_shrink)
			//	delete []m_shrink;
		}

		//void CParser291M::Add(unsigned char d)
		//{
		//	m_frame[++m_offset] = d;
		//}

		void CParser291M::Add(unsigned char* d, int len)
		{
			memcpy(&(m_frame[m_offset]), d, len);
			m_offset += len;
		}

		////void CParserVideo::shrink()
		//void CParser291M::shrink()
		//{
		//	//A 1111 1111 
		//	//B 0011 1111 
		//	//C 1100 1111 
		//	//D 1111 0011 
		//	//E 1111 1100
		//
		//	//A 0011 1111 
		//	//B 1100 1111 
		//	//C 1111 0011 
		//	//D 1111 1100 
		//	//E 1111 1111 
		//	for (int i = 0; i < m_offset; i += 5)
		//	{
		//		int so = 4 * i / 5;
		//		m_shrink[so] = (m_frame[i] << 2) + ((m_frame[i + 1] & 0x0C0) >> 6);
		//		m_shrink[so + 1] = (m_frame[i + 1] << 4) + ((m_frame[i + 2] & 0x0F0) >> 4);
		//		m_shrink[so + 2] = (m_frame[i + 2] << 6) + ((m_frame[i + 3] & 0x0FC) >> 2);
		//		m_shrink[so + 3] = m_frame[i + 4];
		//	}
		//	m_shrink_offset = m_offset * 8 / 10;
		//}
		//
		//
		////AES3±»SMPTE´òÂÒ£¬²»ÄÜshrink
		//void CParser291M::Flush8()
		//{
		//	shrink();
		//	for (int i = 0; i < m_shrink_offset;)
		//	{
		//		i += 3;  //ADF(3)+DID(1)+SDID(1)
		//		unsigned short did = m_shrink[i];
		//		i += 2;
		//		unsigned short datacount = m_shrink[i];  //DC
		//		++i;  //the start of user data
		//		if (did == 0xFF){ //Group1
		//			m_parser272.Receive(m_frame, datacount * 10);  
		//			i += datacount;      //user data   
		//			++i;  //Checksum
		//		}
		//		else{
		//			i = (i / 280 + 1) * 280;    //null data
		//		}
		//
		//	}
		//	m_parser272.Flush();
		//	m_offset = 0;
		//}

		void CParser291M::flush_sd()
		{
			//10DID 8DID                             10DID 8DID
			//  2E8 E8                                1F8 F8 AES extended packet, Group 4
			//	1E9 E9                                2F9 F9 AES audio data, Group 4
			//	1EA EA                                2FA FA AES extended packet, Group 3
			//	2EB EB                                1FB FB AES audio data, Group 3
			//	1EC EC AES control packet, Group 4    2FC FC AES extended packet, Group 2
			//	2ED ED AES control packet, Group 3    1FD FD AES audio data, Group 2
			//	2EE EE AES control packet, Group 2    1FE FE AES extended packet, Group 1
			//	1EF EF AES control packet, Group 1    2FF FF AES audio data, Group 1
			int len = m_offset * 8;

			//may be FC-FF, the lowest 2 bit belong to DID    //ADF (291M 3.2.2) 000h 3FFh 3FFh 
			/*To maximize compatibility between 8 - and
			10 - bit equipment, equipment designers are advised to
			process data values of 000h -- 003h identically.Data
			values of 3FCh -- 3FFh should be processed identically
			as well.*/
			for (int i = 0; i < len;)
			{
				i += 30;  //ADF(3)
				unsigned short did = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);
				i += 20; //DID(1) + SDID(1)
				unsigned short datacount = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);
				datacount &= 0xFF;   //291M P6  b9-p/  b8-p
				i += 10;  //DC(1)
				if (did == 0x2FF) {       //Group1
					int endi = i + 10 * datacount;
					m_anc_count = 0;
					for (; i < endi;)
					{
						//short y = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);
						//y &= 6;
						//y >>= 1;
						//i += 10;  //preamble+AUX
						//m_audio[m_anc_count++] = extract_3ANC(m_frame, i / 8, 8 - i % 8);
						//i += 30;  //3 ANC words
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X
						i += 10;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X+1
						i += 10;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X+2
						i += 10;
						//AES Subframe 32bits, here we donot fetch last 8bits,  because that is the lowest 4 bit of 20bit and VUCP flags
					}
					m_parser272.Receive((unsigned char*)m_audio, 2 * m_anc_count, 1);
					i += 10;
					//debug_anc_count += m_anc_count;
				}
				else if (did == 0x1FD) {    //Group2
					int endi = i + 10 * datacount;
					m_anc_count = 0;
					for (; i < endi;)
					{
						int testcount = m_anc_count;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X
						i += 10;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X+1
						i += 10;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X+2
						i += 10;
					}
					m_parser272.Receive((unsigned char*)m_audio, 2 * m_anc_count, 2);
					i += 10;  //Checksum
				}
				else if (did == 0x1FB) {     //Group3
					int endi = i + 10 * datacount;
					m_anc_count = 0;
					for (; i < endi;)
					{
						int testcount = m_anc_count;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X
						i += 10;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X+1
						i += 10;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X+2
						i += 10;
					}
					m_parser272.Receive((unsigned char*)m_audio, 2 * m_anc_count, 3);                              //Group3
					i += 10;  //Checksum
				}
				else if (did == 0x2F9) {    //Group4
					int endi = i + 10 * datacount;
					m_anc_count = 0;
					for (; i < endi;)
					{
						int testcount = m_anc_count;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X
						i += 10;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X+1
						i += 10;
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //X+2
						i += 10;
					}
					m_parser272.Receive((unsigned char*)m_audio, 2 * m_anc_count, 4);                              //Group4
					i += 10;  //Checksum
				}
				else {
					i = (i / (350 * 8) + 1)*(350 * 8);    //null data
				}
			}
			//OutputString("debug_anc_count=%d\n", debug_anc_count);
			m_parser272.Flush();
			m_offset = 0;
		}

		int debug_datacount = 0;
		void CParser291M::flush_hd()
		{
			debug_datacount = 0;
			int len = m_offset * 8;
			for (int i = 0; i < len;)
			{
				i += 60;  //CbCr-ADF(3)+Y-ADF(3)
				unsigned short did = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);
				i += 40; //[DID(1) + SDID(1)] * 2 (Y-blanking)

				// datacount = 24
				// SMPTE 299M-2004 5.1.3 There are always 24 words in the UDW of an audio data packet; i.e., UDW0, UDW1 ... UDW22, UDW23.
				unsigned short datacount = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);
				datacount &= 0xFF;   //291M P6
				//OutputString("datacount: %d\n", datacount);
				i += 20;  //DC(1) * 2 (Y-blanking)
				i += 40;  //CLK * 2 (Y-blanking)
				if (did == 0x2E7) {
					int endi = i + 20 * 16;   // why isnot datacount?  because there 16UDW for 4 channel every packet, this is constant  // * 2 (Y-blanking)
					m_anc_count = 0;
					for (; i < endi;)
					{
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //UDW1
						i += 20;
					}
					m_parser299.Receive((unsigned char*)m_audio, 2 * m_anc_count, 1);
					i += (7 * 20);  //UDW18-UDW23，CS
					//OutputString("m_anc_count: %d\n", m_anc_count);
				}
				else if (did == 0x1E6) {
					int endi = i + 20 * 16;   // why isnot datacount?  because there 16UDW for 4 channel every packet, this is constant  // * 2 (Y-blanking)
					m_anc_count = 0;
					for (; i < endi;)
					{
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //UDW1
						i += 20;
					}
					m_parser299.Receive((unsigned char*)m_audio, 2 * m_anc_count, 2);
					i += (7 * 20);  //UDW18-UDW23，CS
									//OutputString("m_anc_count: %d\n", m_anc_count);
				}
				else if (did == 0x1E5) {
					int endi = i + 20 * 16;   // why isnot datacount?  because there 16UDW for 4 channel every packet, this is constant  // * 2 (Y-blanking)
					m_anc_count = 0;
					for (; i < endi;)
					{
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //UDW1
						i += 20;
					}
					m_parser299.Receive((unsigned char*)m_audio, 2 * m_anc_count, 3);
					i += (7 * 20);  //UDW18-UDW23，CS
									//OutputString("m_anc_count: %d\n", m_anc_count);
				}
				else if (did == 0x2E4) {
					int endi = i + 20 * 16;   // why isnot datacount?  because there 16UDW for 4 channel every packet, this is constant  // * 2 (Y-blanking)
					m_anc_count = 0;
					for (; i < endi;)
					{
						m_audio[m_anc_count++] = Extract_10_Bits(m_frame, i / 8, 8 - i % 8);  //UDW1
						i += 20;
					}
					m_parser299.Receive((unsigned char*)m_audio, 2 * m_anc_count, 4);
					i += (7 * 20);  //UDW18-UDW23，CS
									//OutputString("m_anc_count: %d\n", m_anc_count);
				}
				else {
					i = (i / (m_width_ancillary_10 * 8) + 1) * m_width_ancillary_10 * 8;
				}
			}
			m_parser299.Flush();
			m_offset = 0;
		}


		void CParser291M::Flush(FRAME f)
		{
			m_frametype = f;
			if (f == PAL)
				flush_sd();
			else
				flush_hd();

		}
	}
}