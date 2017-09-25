#include "redlink.h"
#include "Omni_Api.h"
#include "consumer/redlink_consumer.h"
#include "producer/redlink_producer.h"
#include <core/consumer/frame_consumer.h>
namespace caspar {
	namespace redlink {
		void init(core::module_dependencies dependencies)
		{
			//[Omni_SDK]
			//初始化板卡SDK资源。使用Omni SDK开始时必须调用该函数。
			Om_HRESULT hr = Omn_Initialize();
			if (hr != Omn_SUCCESS)
			{
				CASPAR_LOG(error) << L"Cannot run Redlink.";
				return;
			}
			/*if (!NDIlib_initialize())
			{
			CASPAR_LOG(error) << L"Cannot run NDI.";
			return;
			}*/
			dependencies.consumer_registry->register_consumer_factory(L"redlink Consumer", create_consumer, describe_consumer);
			dependencies.consumer_registry->register_preconfigured_consumer_factory(L"redlink", create_preconfigured_consumer);
			dependencies.producer_registry->register_producer_factory(L"Redlink Producer", create_producer, describe_producer);
		}
	}
}