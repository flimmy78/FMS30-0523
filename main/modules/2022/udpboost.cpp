#include "udpboost.h"
#include <boost/asio.hpp>
#include "Parser20226.h"

#include <boost/thread.hpp>
namespace caspar {
	namespace sdiopi_20226 {

		using boost::asio::ip::udp;
		using namespace boost::asio;
		struct UdpSocket::impl
		{
			boost::asio::io_service io_service;

			ip::udp::endpoint *romote_endpoint=nullptr; //this enpoint is used to store the endponit from remote-computer  
			FRAME  m_frameType;
			std::atomic<long long> m_data_count=0;
			int currentseqnum, lastseqnum = 0;
			ip::udp::socket *socket = nullptr;//(my_io_service, local_endpoint);//create socket and bind the endpoint  
			CParser20226  m_parser20226;
			unsigned char m_recvBuf[1500];
			ip::udp::endpoint sender_endpoint_;
			boost::thread										thread_;
			boost::thread										thread_recive;
			std::string						localinterface_;
			std::string						addr_;
			unsigned short					port_;
			impl(std::string localinterface, std::string addr, unsigned short port,FRAME frametype):m_frameType(frametype)
				,localinterface_(localinterface)
				,addr_(addr)
				,port_(port)
			{
				thread_recive = boost::thread([this] {init(); });
				boost::this_thread::sleep_for(boost::chrono::milliseconds(40));
				
				
			}
			void init()
			{
				SetThreadPriority(GetCurrentThread(), HIGH_PRIORITY_CLASS);//ABOVE_NORMAL_PRIORITY_CLASS  HIGH_PRIORITY_CLASS
				socket = new ip::udp::socket(io_service);
				udp::endpoint listen_endpoint(
					ip::address::from_string(localinterface_), port_);

				socket->open(listen_endpoint.protocol());
				socket->set_option(udp::socket::reuse_address(true));
				socket->bind(listen_endpoint);

				socket->set_option(
					ip::multicast::join_group(ip::address::from_string(addr_)));

				socket->async_receive_from(
					boost::asio::buffer(m_recvBuf, 1500), sender_endpoint_,
					boost::bind(&UdpSocket::impl::handle_receive_from, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			}
			void handle_receive_from(const boost::system::error_code& error,
				size_t bytes_recvd)
			{
				
				if (!error)
				{
					//get data

					if (bytes_recvd > 0)
					{
					//	printf("%d\n", bytes_recvd);
						m_data_count += bytes_recvd;
						//m_parser20226.Receive(m_recvBuf, bytes_recvd);
						currentseqnum = m_recvBuf[2] * 256 + m_recvBuf[3];
						if ((currentseqnum - lastseqnum != 1) & (currentseqnum != 0))	printf("drop %d packet(s).\n", currentseqnum - lastseqnum);
						lastseqnum = currentseqnum;
					}
					//////
				//	boost::this_thread::sleep_for(boost::chrono::milliseconds(0));
					socket->async_receive_from(
						boost::asio::buffer(m_recvBuf, 1500), sender_endpoint_,
						boost::bind(&UdpSocket::impl::handle_receive_from, this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred));
				}
			}

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

			bool Run()
			{
				//返回值
				thread_ = boost::thread([this] {io_run(); });
				return true;
				
			}
			void io_run()
			{
				m_parser20226.Start(m_frameType);
				io_service.run();
			}
			void Stop()
			{
				io_service.stop();
				m_parser20226.Stop();
			}
			~impl()
			{
				/*io_service.stop();
				m_parser20226.Stop();*/
				delete socket;
			}
		};

		UdpSocket::UdpSocket(std::string localinterface, std::string addr, unsigned short port,FRAME frametype) 
		:impl_(new impl(localinterface, addr, port, frametype))
		{

		}
		bool UdpSocket::Run()
		{
			return impl_->Run();
		}
		void UdpSocket::GetAudio(unsigned char* p, int channel)
		{
			impl_->GetAudio(p,channel);
		}
		void UdpSocket::GetVideo(unsigned char* p)
		{
			impl_->GetVideo(p);
		}
		
		void UdpSocket::SetVideoNotify(RECEIVE_DATA rd, void* p)
		{
			impl_->SetVideoNotify(rd, p);
		}

		void UdpSocket::SetAudioNotify(RECEIVE_DATA rd, void* p)
		{
			impl_->SetAudioNotify(rd, p);
		}
		void UdpSocket::Stop()
		{
			impl_->Stop();
		}

		int UdpSocket::GetDecodeCount()
		{ 
			return impl_->GetDecodeCount(); 
		}
		long long UdpSocket::GetDataCount() 
		{ 
			return impl_->GetDataCount();

		}
		UdpSocket::~UdpSocket()
		{
		}
	}
}