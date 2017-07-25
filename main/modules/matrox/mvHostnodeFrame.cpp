//
// Created by zibj 2016/10/25.
//

#include "matrox.h"
#include "producer/matrox_producer.h"
#include "consumer/matrox_consumer.h"
#include <core/consumer/frame_consumer.h>
#include <mvHResult.h>
#include <MatroxDSXsdk.h>
#if !defined(_WIN32) && !defined(_WIN64)
#include "mvInitCOM.h"
#endif

namespace caspar {	namespace matrox	{
	
	void init(core::module_dependencies dependencies)
	{

#if defined(_WIN32)|| defined (_WIN64)
		CMvHResult oHr;
		oHr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		//������Ҫ��COM����ͷž��
		if (oHr.DidFail())
		{

			CASPAR_LOG(error) << L"init matrox CoInitializeEx :"<< mvErrorToString(oHr);
			CoUninitialize();
			return ;
		}

#else
		CMvInitCOM oComInit;

		if (FAILED(oComInit))
		{
			CASPAR_LOG(error) << L"matrox linux Unable to initialize the system";
			return;
		}
#endif
		//�����ļ��ķ�ʽ������consumer create_consumer
		dependencies.consumer_registry->register_consumer_factory(L"Matrox Consumer", create_consumer, describe_consumer);
		//����ķ�ʽ����̬����consumer create_preconfigured_consumer
		dependencies.consumer_registry->register_preconfigured_consumer_factory(L"matrox", create_preconfigured_consumer);
		//����ķ�ʽ������producer�����û��SDI�ź���������Ļ�����Ҫ����ʧ�� create_producer
		dependencies.producer_registry->register_producer_factory(L"Matrox Producer", create_producer, describe_producer);

		
	}

}}