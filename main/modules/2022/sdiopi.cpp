//
// Created by zibj 2016/10/25.
//

#include "sdiopi.h"

//#include "consumer/sdiopi_consumer.h"
#include "producer/sdiopi_producer.h"
#include <core/consumer/frame_consumer.h>
namespace caspar {	namespace sdiopi_20226 {

	void init(core::module_dependencies dependencies)
	{
		//dependencies.consumer_registry->register_consumer_factory(L"NDI Consumer", create_consumer, describe_consumer);
		//dependencies.consumer_registry->register_preconfigured_consumer_factory(L"ndi", create_preconfigured_consumer);
		dependencies.producer_registry->register_producer_factory(L"Sdi2022 Producer", create_producer, describe_producer);
	}

}}