//
// Created by zibj 2016/10/25.
//

#pragma once

namespace caspar {	namespace matrox	{
	enum type_mid
	{
		IP_TYPE,
		SDI_TYPE,
		IVLID
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

		std::wstring		localhost = L"";
		std::wstring		addr = L"";
		short				port = 1001;
		std::wstring		ratio = L"16:9";
		short				card = 0;
		short				sdi = 0;
		type_mid			type = type_mid::IVLID;//��Ч
		bool				key = false;
		bool				vanc = false;
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
	struct Frame2022ForConsumer {
		bool IsTop;//�ж��Ƿ��Ƕ�������
		std::shared_ptr<uint8_t> pvideo;
		std::shared_ptr<uint8_t> paudio;
		int width;
		int height;
		int usample;

	};
}}