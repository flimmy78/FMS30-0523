#pragma once
#include <core/video_format.h>
#include <core/monitor/monitor.h>

namespace caspar {	namespace sdiopi_20226	{

	struct Sdi2022Frame
	{
		std::shared_ptr<uint8_t> pvideo;
		std::shared_ptr<uint8_t> paudio;
	};
	struct SdiOpineed 
	{
		core::video_format format;
		int width;
		int higth;
		int channel;
		int port;
		std::string addr;
		std::string host;//±¾µØip
	};
	class sdiopi_interface_20226
	{
	public:
		sdiopi_interface_20226(SdiOpineed pneed);
		~sdiopi_interface_20226() {}
		bool get_frame(std::shared_ptr<Sdi2022Frame>  & frame);
	private:
		struct impl;
		spl::shared_ptr<impl> impl_;
	};
}}