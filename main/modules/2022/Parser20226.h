#pragma once
#include "ParserBT601.h"
#include "Parser292M.h"
#include <thread>
#include <mutex>
#include <future>
#include <atomic>
#include <windows.h>
#include "common.h"
namespace caspar {
	namespace sdiopi_20226 {
#define  BUFFERCOUNT  2

		extern LARGE_INTEGER g_PerfFreq;

		class CParser20226
		{
		public:
			CParser20226();
			~CParser20226();

		public:
			void Start(FRAME frame);
			void Run();
			void Stop();
			virtual int Receive(unsigned char* p, int len);

		public:
			void GetVideo(unsigned char* p) {
				switch (m_FrameType) {
				case PAL: return m_parser601.GetVideo(p);
				case PAL1080: return m_parser292M.GetVideo(p);
				default: break;
				}
			};
			void GetAudio(unsigned char* p, int channel) {
				switch (m_FrameType) {
				case PAL: return m_parser601.GetAudio(p, channel);
				case PAL1080: return m_parser292M.GetAudio(p, channel);
				default: break;
				}
			};
			void SetVideoNotify(RECEIVE_DATA rd, void* p)
			{
				m_parser601.SetVideoNotify(rd, p);
				m_parser292M.SetVideoNotify(rd, p);
			}
			void SetAudioNotify(RECEIVE_DATA rd, void* p)
			{
				m_parser601.SetAudioNotify(rd, p);
				m_parser292M.SetAudioNotify(rd, p);
			}
			int GetDecodeCount() { return m_decode_count; };

		private:
			std::atomic<int> m_decode_count;

			std::promise<int> m_prom;

		private:
			void ProcessRTPHeader(unsigned char* p);
			int  ProcessPayloadHeader(unsigned char* p);
			void ProcessMediaPayload();

		private:
			static unsigned int ThreadFuncWrapper(void* p);
			void ThreadFunc();
			std::shared_ptr<std::thread> m_worker;
			std::mutex   m_mutexWrite;
			unsigned int m_offset;
			int          m_border;

			//
			bool         m_bMarker;
			unsigned int m_seqnum;
			unsigned int m_timestampRTPHeader;
			unsigned int m_timestampPayloadHeader;
			FRAME        m_FrameType;

			struct BufferRecord {
				BufferRecord(int border) {
					count = 0;
					m_border = border;
					buffer = new unsigned char[m_border];
				}
				~BufferRecord() {
					delete[]buffer;
				}
				bool CanReceive(int len)
				{
					if (count + len > m_border) {
						//LARGE_INTEGER cur;
						//QueryPerformanceCounter(&cur);
						//printf("full: count=%d, len=%d, time=%d\n", count, len, cur.QuadPart * 1000000 / g_PerfFreq.QuadPart);
						return false;
					}
					return true;
				}
				void Receive(unsigned char* p, int len)
				{
					memcpy(buffer + count, p, len);
					count += len;
				}
				void Reset()
				{
					count = 0;
					m_filled = false;
				}
				int     count;
				unsigned char*   buffer;
				bool    m_filled;
				int     m_border;
			}*m_buffer[BUFFERCOUNT];
			BufferRecord* get_writable_buffer() { return m_buffer[m_writable_buffer%BUFFERCOUNT]; };
			BufferRecord* get_readable_buffer()
			{
				for (int i = 0; i < BUFFERCOUNT; ++i)
				{
					if (m_buffer[i]->m_filled)
					{
						return m_buffer[i];
					}
				}
				return nullptr;
			};
			int m_writable_buffer;

		private:
			CParserBT601 m_parser601;
			CParser292M  m_parser292M;
			std::atomic_bool     m_thread_status;
		};
	}
}