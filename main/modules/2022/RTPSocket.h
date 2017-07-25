#pragma once
#include "Parser20226.h"
namespace caspar {
	namespace sdiopi_20226 {
		class CRTPSocket
		{
		public:
			CRTPSocket(std::string localinterface, std::string addr, u_short port, FRAME frame);
			~CRTPSocket();
			bool Run();
			void Stop();
			void GetVideo(unsigned char* p) {
				return m_parser20226.GetVideo(p);
			};
			void GetAudio(unsigned char* p, int channel) {
				return m_parser20226.GetAudio(p, channel);
			};
			void SetVideoNotify(RECEIVE_DATA rd, void* p)
			{
				m_parser20226.SetVideoNotify(rd, p);
			}
			void SetAudioNotify(RECEIVE_DATA rd, void* p)
			{
				m_parser20226.SetAudioNotify(rd, p);
			}
			int GetDecodeCount() { return m_parser20226.GetDecodeCount(); };
			long long GetDataCount() { return m_data_count; };
			void start();

		private:
			static unsigned int ThreadFuncWrapper(void* p);
			std::shared_ptr<std::thread> m_worker;
			std::promise<int> m_prom;


		private:
			CParser20226  m_parser20226;
			unsigned char m_recvBuf[1500];
			SOCKET	m_sock, m_sockM;
			SOCKADDR_IN		m_remoteAddr;
			std::atomic_bool     m_thread_status;
			FRAME  m_frameType;

		private:
			std::atomic<long long> m_data_count;


		};



	}
}