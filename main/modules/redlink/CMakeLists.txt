cmake_minimum_required (VERSION 2.6)
project (redlink)

set(SOURCES
		consumer/redlink_consumer.cpp
		producer/redlink_producer.cpp
		redlink.cpp
		buffermng.cpp
		os_supports.cpp
		StdAfx.c
		StdAfx.cpp
		buffermng.cpp
)
set(HEADERS
		consumer/redlink_consumer.h
		producer/redlink_producer.h
		redlink.h
		buffermng.h
		os_supports.h
		StdAfx.h
		buffermng.h
)

add_library(redlink ${SOURCES} ${HEADERS})
add_precompiled_header(redlink StdAfx.h FORCEINCLUDE)

include_directories(..)
include_directories(../..)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${FFMPEG_INCLUDE_PATH})
include_directories(${RXCPP_INCLUDE_PATH})
include_directories(${ASMLIB_INCLUDE_PATH})
include_directories(${REDLINK_INCLUDE_PATH})

set_target_properties(redlink PROPERTIES FOLDER modules)
source_group(sources ./*)
source_group(sources\\consumer consumer/*)
source_group(sources\\producer producer/*)

if (MSVC)
	add_definitions( -WIN64 )
	target_link_libraries(redlink
			common
			core
			ffmpeg
			Omni_SDK
	)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions( -LINUX64 )
	target_link_libraries(redlink
			common
			core
			ffmpeg
			Omni_SDK
			dl
	)
endif ()
if (MSVC)
casparcg_add_runtime_dependency("${REDLINK_BIN_PATH}/x64/Omni_SDK.dll")
elseif(CMAKE_COMPILER_IS_GNUCXX)
casparcg_add_runtime_dependency("${REDLINK_BIN_PATH}/libOmni_SDK.so")
endif()


casparcg_add_include_statement("modules/redlink/redlink.h")
casparcg_add_init_statement("redlink::init" "redlink")
casparcg_add_module_project("redlink")
