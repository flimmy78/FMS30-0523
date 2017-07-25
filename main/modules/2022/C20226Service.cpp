
#include <string>
#include <stdio.h>
#include <mutex>
#include "common.h"
#include "C20226Service.h"

namespace caspar {
	namespace sdiopi_20226 {

		C20226Service::C20226Service(std::string localinterface, std::string addr, unsigned short port, FRAME frame) :
			m_socket(NULL), m_localinterface(localinterface), m_addr(addr), m_port(port), m_frame(frame)

		{
			if (frame == PAL)
				m_vSize = 720 * 576 * 4;
			else
				m_vSize = 1920 * 1080 * 4;

			//int aSize = 1920 * 2 * 2 * 2;
			m_aSize = 1920 * 2 * 2 * 2;

			m_socket = new CRTPSocket(localinterface, addr, port, frame);
			//m_socket = new UdpSocket(localinterface, addr, port, frame);
		}


		C20226Service::~C20226Service()
		{
			if (m_socket)
			{
				m_socket->Stop();
				delete m_socket;
				m_socket = NULL;
			}
		}
	}
}