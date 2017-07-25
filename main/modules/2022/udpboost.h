#pragma once
#include <core/video_format.h>
#include <core/monitor/monitor.h>
#include "common.h"
namespace caspar {
	namespace sdiopi_20226 {
		class UdpSocket
		{
		public:
			UdpSocket(std::string localinterface, std::string addr, unsigned short port,FRAME frametype);
			~UdpSocket();

			bool Run();
			void GetAudio(unsigned char* p, int channel); 
			void GetVideo(unsigned char* p);
			
			void SetVideoNotify(RECEIVE_DATA rd, void* p);
			
			void SetAudioNotify(RECEIVE_DATA rd, void* p);
			void Stop();
			int GetDecodeCount();
			long long GetDataCount();
		private:
		struct impl;
			spl::shared_ptr<impl> impl_;
		};


	}
}