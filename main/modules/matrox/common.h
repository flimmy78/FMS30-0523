#pragma once

namespace caspar {	namespace matrox	{
	
	enum type_mid
	{
		IVLID,
		IP_TYPE,
		SDI_TYPE
	};
	struct producer_need {

		std::wstring		host = L"";//������Ϣ �ձ�ʾ������
		std::wstring		addr = L"";//�鲥��ַ
		short				port = 10001;//���ö˿�
		std::wstring		ratio=L"16:9";//�������
		short				card =0;//�忨���
		short				sdi = 0;//sdiͨ�� 
		type_mid			type = type_mid::IVLID;//��Ч
		
	};
	struct consumer_need {
		std::wstring		ratio = L"16:9";
		uint32_t			card = 0;
		uint32_t			sdi = 0;
		bool				key = false;
		bool				vanc = false;
		type_mid			type = type_mid::IVLID;//��Ч
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
		bool IsTop;//�ж��Ƿ��Ƕ�������
		std::shared_ptr<uint8_t> pvideo;
		std::shared_ptr<uint8_t> paudio;
		int width;
		int height;
		int usample;

	};
}}