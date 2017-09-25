#pragma once
#include <core/module_dependencies.h>

namespace caspar {
	namespace redlink {
		void init(core::module_dependencies dependencies);
		void describe_producer(core::help_sink& sink, const core::help_repository& repo);
		spl::shared_ptr<core::frame_producer> create_producer(const core::frame_producer_dependencies& dependencies, const std::vector<std::wstring>& params);
	}
}