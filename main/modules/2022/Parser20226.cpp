
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "Parser20226.h"
#include "Parser292M.h"
#include "common.h"
#include <assert.h>
#include <common/timer.h>

namespace caspar {
	namespace sdiopi_20226 {
		LARGE_INTEGER g_PerfFreq;


		CParser20226::CParser20226() : m_writable_buffer(0),
			m_offset(0),
			m_FrameType(OTHER),
			m_bMarker(false),
			m_timestampRTPHeader(0),
			m_timestampPayloadHeader(0)

		{
			QueryPerformanceFrequency(&g_PerfFreq);
			for (int i = 0; i < BUFFERCOUNT; i++)
			{
				m_buffer[i] = NULL;
			}
		}


		CParser20226::~CParser20226()
		{
			for (int i = 0; i < BUFFERCOUNT; i++)
			{
				if (m_buffer[i] != NULL)
					delete m_buffer[i];
			}
		}

		void CParser20226::Start(FRAME frame)
		{
			if (frame == PAL) {
				m_border = (720 * 2 + 280 + 8)*(625 + 1) * 10 / 8;  //(2640+12)*(1125+1)*20/8
			}
			else {
				m_border = 2640 * (1125 + 1) * 20 / 8;  //(2640+12)*(1125+1)*20/8
			}

			for (int i = 0; i < BUFFERCOUNT; i++)
			{
				m_buffer[i] = new BufferRecord(m_border);
			}

			m_worker = std::make_shared<std::thread>((std::thread(CParser20226::ThreadFuncWrapper, this)));
			m_worker->detach();
		}

		void CParser20226::Stop()
		{
			m_thread_status = FALSE;
			std::future<int> fut = m_prom.get_future();
			int f = fut.get();
		}

		unsigned int CParser20226::ThreadFuncWrapper(void* p) {
			CParser20226* param = (CParser20226*)p;
			param->ThreadFunc();
			return 0;
		}

		void CParser20226::ProcessRTPHeader(unsigned char* p)
		{
			unsigned char charTemp = p[0];
			unsigned char charVersion = charTemp >> 6;  //2 for 20226
			unsigned char charPadding = (charTemp >> 5) & 0x1;  //0 no padding, 1 padding
			unsigned char charExtension = (charTemp >> 4) & 0x1;  //0 no header extension
			unsigned char charCSRCCount = charTemp & 0xF;   //no CSRC lists present in the Media Datagrams
			charTemp = p[1];
			unsigned char charMarker = charTemp >> 7;  //1  the last Media Datagram of the video frame
											  //0  all other Media Datagrams
			m_bMarker = (bool)charMarker;
			unsigned char charPayloadType = charTemp & 0x7F;  //98（0x62） – High bit rate media transport / 27-MHz Clock
													  //99 – High bit rate media transport FEC / 27-MHz Clock  
			m_seqnum = p[2] * 8 + p[3]; //increment by one for each RTP data datagram
			memcpy(&m_timestampRTPHeader, &p[4], 4);  //the sampling instant of the first octet in the RTP datagram
			unsigned int dwSSRC;      memcpy(&dwSSRC, &p[8], 4);  //synchronization source
		}


		int CParser20226::ProcessPayloadHeader(unsigned char* p)
		{
			int ibegin = m_writable_buffer % BUFFERCOUNT;

			unsigned char charTemp = p[12];
			unsigned char charExtension = charTemp >> 4;  //"0000" = No extension; "0001–1111" = Payload header is extended by this number x 4 octets
			unsigned char charVideoSourceFormat = (charTemp >> 3) & 0x1;  //0 Video source format is not present, 1 present
			unsigned char charVideoSourceID = charTemp & 0x3;  //000 – primary stream; 001 – protect stream; 010-111 – reserved

			unsigned char charFrameCount = p[13];  //increment to a new value for the next RTP sequence numbered datagram immediately after the end of video frame M marker

			charTemp = m_buffer[ibegin]->buffer[14];
			unsigned char charReferenceForTimestamp = charTemp >> 6;  //00 – not locked; 01 – reserved; 10 – UTC time/frequency reference; 11 – private time frequency reference
			unsigned char charVideoPayloadScrambling = (charTemp >> 4) & 0x3;  //00 – not scrambled; other  reserved
			unsigned char charFECusage = (charTemp >> 1) & 0x7; //000 = No FEC stream;001 = L (Column) FEC utilized;010 = L & D (Column & Row) FEC utilized;other reserved

			charTemp = p[15];
			unsigned char charClockFrequency = (charTemp >> 5) & 0x7;  //0000 = No time stamp; 0001 = 27 MHz; 0010 = 148.5 MHz;	0011 = 148.5 / 1.001 MHz;  0100 = 297 MHz;	0101 = 297 / 1.001MHz;	
															  //0110 - 1111 = Reserved; 四位的最高位在m_buffer[m_begin].buffer[14]的最低位，因为该位保留，所以没取!!!

			charTemp = p[16];
			unsigned char charMAP = charTemp >> 4;   //0x00 Direct sample structure as per SMPTE ST 292-1, SMPTE ST 425-1 Level A, etc
											//0x01	SMPTE ST 425 - 1 Level B - DL Mapping of ST 372 Dual - Link
											//0x02	SMPTE ST 425 - 1 Level B - DS Mapping of two ST 292 - 1 Streams
											//0x03-0x0F	Reserved
			unsigned char charFrame = charTemp & 0xF;

			charTemp = p[17];
			charFrame = (charFrame << 4) + (charTemp >> 4);  //0x00		Unknown / Unspecified Frame Structure
															 //0x11--720 576 625		Interlace		Interlace
															 //0x20--1920 1080 1125		Interlace		Interlace  
															 //other 参见 2022-6 p10
			if (charFrame == 0x11) m_FrameType = PAL;
			if (charFrame == 0x20) m_FrameType = PAL1080;
			assert(m_FrameType != OTHER);

			unsigned char charFRATE = charTemp & 0xF;
			charTemp = p[18];
			charFRATE = (charFRATE << 4) + (charTemp >> 4);   //0x12 50;  0x18 25; other 参见 2022-6 p11
			unsigned char charSAMPLE = charTemp & 0xF;    //0x01 4:2:2 10 bits; other 参见 2022-6 p11 

			charTemp = p[19];   //FMT-RESERVED

			int offset = 0;
			if (charClockFrequency > 0) {
				memcpy(&m_timestampPayloadHeader, &(m_buffer[ibegin]->buffer[20]), 4);
				offset += 4;
			}

			if (charExtension > 0) {
				//DWORD dwExtension;
				//memcpy(&dwExtension, &m_buffer[m_begin].buffer[20 + offset], 4);
				offset += 4 * charExtension;
			}

			m_offset = 20 + offset;

			return m_offset;
		}

		void CParser20226::ProcessMediaPayload()
		{
			BufferRecord* p = get_readable_buffer();
			//OutputString("buffer r=%d w=%d\n", p, get_writable_buffer());
			if (p) {
				caspar::timer										tick_timer;
				if (m_FrameType == PAL) {
					//OutputString("reading=%d\n", p);
					/*LARGE_INTEGER cur;
					QueryPerformanceCounter(&cur);*/

					m_parser601.Receive(p->buffer, p->count);
					m_decode_count = m_parser601.Process();

					/*LARGE_INTEGER cur2;
					QueryPerformanceCounter(&cur2);
					OutputString("1frame =%d\n", (cur2.QuadPart - cur.QuadPart) * 1000 / g_PerfFreq.QuadPart);*/
				}
				else {
					//printf("m_parser292M %d \n", p->count);
					m_parser292M.Receive(p->buffer, p->count);
					m_decode_count = m_parser292M.Process();
				}
				p->Reset();
				//printf("Process---- %f \n", tick_timer.elapsed());
				tick_timer.restart();

			}
			
		}

		void CParser20226::ThreadFunc()
		{
			SetThreadPriority(GetCurrentThread(), HIGH_PRIORITY_CLASS);
			m_thread_status = TRUE;
			while (m_thread_status)
			{
				ProcessMediaPayload();
			}
			OutputString("CParser20226::ThreadFunc stop\n");
			m_prom.set_value(1);
		}
		int packetc = 0;
		int packetc3 = 0;
		int CParser20226::Receive(unsigned char* p, int len)
		{
			/*packetc++;
			
			if (m_bMarker) {
				//get_writable_buffer()->m_filled = true;
				//printf("M c= %d\n", get_writable_buffer()->count);
				printf("M pc= %d\n", packetc);
				//++m_writable_buffer;
				packetc = 0;

			}
			return 0;*/
			ProcessRTPHeader(p);
			int headerlen = ProcessPayloadHeader(p);
			//if (headerlen != 24)
			//	printf("headerlen %d\n", headerlen);
			if (!get_writable_buffer()->CanReceive(len - headerlen))
			{
				//printf("overflow\n");
				get_writable_buffer()->Reset();
			}
			get_writable_buffer()->Receive(p + headerlen, len - headerlen);  //remove RTP and playload header
			//packetc3++;
			packetc++;
			if (m_bMarker) {
				get_writable_buffer()->m_filled = true;
				//printf("M c= %d\n", get_writable_buffer()->count);
				printf("M pc= %d\n", packetc);
				++m_writable_buffer;
				packetc = 0;
				
			}
			else {
			//	if ((packetc3 % 15000) == 0)
			//		printf("20226::Receiv %d\n", packetc3);
			}
			return 0;
		}
	}
}