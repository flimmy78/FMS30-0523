
#include <WINSOCK2.h>
#include <stdio.h>
#include <Ws2tcpip.h>
#include <atomic>
#include "Parser20226.h"
#include "RTPSocket.h"

#pragma comment(lib,"ws2_32")
namespace caspar {
	namespace sdiopi_20226 {
		CRTPSocket::CRTPSocket(std::string localinterface, std::string addr, u_short port, FRAME frame) : m_thread_status(false), m_data_count(0)
		{
			WSADATA	ws;
			int	ret;

			m_frameType = frame;

			SOCKADDR_IN		localAddr;
			int	len = sizeof(SOCKADDR);
			ip_mreq		mcast;

			ret = WSAStartup(MAKEWORD(2, 2), &ws);
			if (0 != ret)
			{
				printf("WSAStartupÊ§°Ü\n");
			}

			if ((m_sock = WSASocketW(AF_INET, SOCK_DGRAM, 0, NULL, 0,
				WSA_FLAG_MULTIPOINT_C_LEAF | WSA_FLAG_MULTIPOINT_D_LEAF | WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
			{
				printf("socket failed with: %d\n", WSAGetLastError());
				WSACleanup();
				return;
			}

			//supporting multi instance
			int on = 1;
			ret = setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
			//on = 1000000;
			//ret = setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (char *)&on, sizeof(on));

			localAddr.sin_family = AF_INET;
			localAddr.sin_port = htons(port);
			inet_pton(AF_INET, localinterface.data(), (void *)&localAddr.sin_addr.S_un.S_addr);
			ret = bind(m_sock, (SOCKADDR*)&localAddr, len);
			if (SOCKET_ERROR == ret)
			{
				closesocket(m_sock);
				printf("bind error\n");
			}

			memset(&m_remoteAddr, 0x00, len);
			m_remoteAddr.sin_family = AF_INET;
			m_remoteAddr.sin_port = htons(port);
			inet_pton(AF_INET, addr.data(), (void *)&m_remoteAddr.sin_addr.s_addr);
			if ((m_sockM = WSAJoinLeaf(m_sock, (SOCKADDR*)&m_remoteAddr, sizeof(m_remoteAddr), NULL, NULL, NULL, NULL, JL_BOTH)) == INVALID_SOCKET)
			{
				printf("WSAJoinLeaf() failed: %d\n", WSAGetLastError());
				closesocket(m_sock);
				WSACleanup();
				return;
			}

			int iMode = 0; //1,nonblock；0, block
			ioctlsocket(m_sockM, FIONBIO, (u_long FAR*) &iMode);

		}



		//for Linux
		/*CRTPSocket::CRTPSocket(std::string localinterface, std::string addr, u_short port, FRAME frame) : m_thread_status(false), m_data_count(0)
		{
		int sockfd;
		struct sockaddr_in servaddr, cliaddr;


		sockfd = socket(AF_INET, SOCK_DGRAM, 0); // create a socket


		// init servaddr
		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		inet_pton(AF_INET, localinterface.data(), (void *)&servaddr.sin_addr.S_un.S_addr);
		servaddr.sin_port = htons(port);


		// bind address and port to socket
		if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
		{
		perror("bind error");
		exit(1);
		}

		int iMode = 1; //1,nonblock；0, block
		ioctlsocket(m_sockM, FIONBIO, (u_long FAR*) &iMode);
		}*/


		CRTPSocket::~CRTPSocket()
		{
		}


		bool CRTPSocket::Run()
		{
			m_worker = std::make_shared<std::thread>((std::thread(CRTPSocket::ThreadFuncWrapper, this)));
			if (m_worker) {
				m_worker->detach();
				return true;
			}
			return false;
		}

		void CRTPSocket::Stop()
		{
			if (!m_thread_status) return;
			m_thread_status = false;
			std::future<int> fut = m_prom.get_future();
			int f = fut.get();
			closesocket(m_sockM);
			m_parser20226.Stop();
		}

		unsigned int CRTPSocket::ThreadFuncWrapper(void* p) {
			CRTPSocket* param = (CRTPSocket*)p;
			param->start();
			return 0;
		}
		//int packetc2 = 0;
		void CRTPSocket::start()
		{
			int	ret;
			memset(m_recvBuf, 0x00, sizeof(m_recvBuf));
			int currentseqnum, lastseqnum = 0;
			m_parser20226.Start(m_frameType);
			int sz = sizeof(SOCKADDR);
			m_thread_status = true;
			while (m_thread_status)
			{
				try {
					ret = recvfrom(m_sock, (char*)m_recvBuf, sizeof(m_recvBuf), 0, (SOCKADDR*)&m_remoteAddr, &sz);
					if (ret > 0)
					{
						//if (((packetc2++) % 15000) == 0)
						//	printf("recvfrom %d\n", packetc2);
						m_data_count += ret;
						m_parser20226.Receive(m_recvBuf, ret);
						currentseqnum = m_recvBuf[2] * 256 + m_recvBuf[3];
						if ((currentseqnum - lastseqnum != 1) & (currentseqnum != 0))	printf("drop %d packet(s).\n", currentseqnum - lastseqnum);
						//if (currentseqnum - lastseqnum != 1)	printf("drop %d packet(s).\n", currentseqnum - lastseqnum);
						lastseqnum = currentseqnum;
					}
				}
				catch (...)
				{
					break;
				}
			}
			m_prom.set_value(1);
		}
	}
}