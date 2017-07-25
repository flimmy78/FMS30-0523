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
		//出错需要将COM组件释放句柄
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
		//配置文件的方式来创建consumer create_consumer
		dependencies.consumer_registry->register_consumer_factory(L"Matrox Consumer", create_consumer, describe_consumer);
		//命令的方式来动态创建consumer create_preconfigured_consumer
		dependencies.consumer_registry->register_preconfigured_consumer_factory(L"matrox", create_preconfigured_consumer);
		//命令的方式来创建producer，如果没有SDI信号输出进来的话，需要返回失败 create_producer
		dependencies.producer_registry->register_producer_factory(L"Matrox Producer", create_producer, describe_producer);

		
	}

}}