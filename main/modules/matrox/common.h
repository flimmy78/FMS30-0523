#pragma once

namespace caspar {	namespace matrox	{
	
	enum type_mid
	{
		IVLID,
		IP_TYPE,
		SDI_TYPE
	};
	struct producer_need {

		std::wstring		host = L"";//网卡信息 空表示无输入
		std::wstring		addr = L"";//组播网址
		short				port = 10001;//共用端口
		std::wstring		ratio=L"16:9";//画面比例
		short				card =0;//板卡序号
		short				sdi = 0;//sdi通道 
		type_mid			type = type_mid::IVLID;//无效
		
	};
	struct consumer_need {
		std::wstring		ratio = L"16:9";
		uint32_t			card = 0;
		uint32_t			sdi = 0;
		bool				key = false;
		bool				vanc = false;
		type_mid			type = type_mid::IVLID;//无效
		std::wstring        args = L"";
	};

	struct FrameforProducer {
		std::shared_ptr<uint8_t> pvideo;
		std::shared_ptr<uint8_t> paudio;
		unsigned int audiolen;
		unsigned int videolen;
		int afd_aspect_ratio_;//0 4:3  1 16:9
		int afd_command_;
		int interlaced_frame;
		int top_field_first;
		int width;
		int height;
		int usample;
	};
	struct FrameForConsumer {
		bool IsTop;//判断是否是顶场数据
		std::shared_ptr<uint8_t> pvideo;
		std::shared_ptr<uint8_t> paudio;
		int width;
		int height;
		int usample;

	};
}}