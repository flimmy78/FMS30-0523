#pragma once
#include "common.h"
#include <string>
#include <mutex>
#include <atomic>
#include "udpboost.h"
#include "RTPSocket.h"
namespace caspar {
	namespace sdiopi_20226 {
		class C20226Service
		{
		private:
			std::string m_localinterface;
			std::string m_addr;
			unsigned short   m_port;
			FRAME       m_frame;
		public:
			C20226Service(std::string localinterface, std::string addr, unsigned short port, FRAME frame);
			~C20226Service();
			void GetAudio(unsigned char* p, int channel) { if (m_socket) m_socket->GetAudio(p, channel); }
			void GetVideo(unsigned char* p) { if (m_socket) m_socket->GetVideo(p); }
			void GetFirstField(unsigned char* p) {
				//unrealized
			}
			void SetVideoNotify(RECEIVE_DATA rd, void* p)
			{
				if (m_socket)
					m_socket->SetVideoNotify(rd, p);
			}
			void SetAudioNotify(RECEIVE_DATA rd, void* p)
			{
				if (m_socket)
					m_socket->SetAudioNotify(rd, p);
			}

			void GetSecondField(unsigned char* p) {
				//unrealized
			}
			bool Run() {
				if (m_socket)
					return m_socket->Run();
				else
				{
					m_socket = new CRTPSocket(m_localinterface, m_addr, m_port, m_frame);
					//m_socket = new UdpSocket(m_localinterface, m_addr, m_port, m_frame);
					if (m_socket)
						return  m_socket->Run();
					return 0;
				}
			}
			void Stop() {
				if (m_socket)
					m_socket->Stop();
			}


		private:
			CRTPSocket* m_socket;
			//UdpSocket *m_socket;
			int m_buffer_offset;
			int m_vSize;   // for validation of the size of buffer
			int m_aSize;   // for validation of the size of buffer 

		public:   //for verify
			int  GetDecodeCount() {
				if (m_socket)
					return m_socket->GetDecodeCount();
				return 0;
			}
			int  GetDataCount() {
				if (m_socket)
					return m_socket->GetDataCount();
				return 0;
			}
		};

	}
}