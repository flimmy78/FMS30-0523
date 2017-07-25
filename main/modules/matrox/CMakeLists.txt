cmake_minimum_required (VERSION 2.6)
project (matrox2)

#set(CMAKE_C_COMPILER g++)	# 更规范c源代码

set(SOURCES
		matrox.cpp
		producer/matrox_producer.cpp
		consumer/matrox_consumer.cpp
		matrox_interface_consumer.cpp
		SfpSdiStatusCallback.cpp
		ErrorNotificationCallback.cpp
		MvErrorCallbackHandler.h
)
set(HEADERS
		matrox.h
		producer/matrox_producer.h
		consumer/matrox_consumer.h
		matrox_interface_consumer.h
		SfpSdiStatusCallback.h
		ErrorNotificationCallback.h
		MvErrorCallbackHandler.h
)

add_library(matrox2 ${SOURCES} ${HEADERS})

include_directories(..)
include_directories(../..)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${FFMPEG_INCLUDE_PATH})
include_directories(${RXCPP_INCLUDE_PATH})
include_directories(${ASMLIB_INCLUDE_PATH})
include_directories(${DTAPI_INCLUDE_PATH})
include_directories(${MATROX_INCLUDE_PATH})
set_target_properties(matrox2 PROPERTIES FOLDER modules)
source_group(sources ./*)
if (MSVC)
	target_link_libraries(matrox
			common
			core
			ffmpeg
	)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(matrox2
			common
			core
			ffmpeg
			mvfFlexAPI 
			mvUtility 
			mvCOM 
			mvCOMEntry
			mvdAPI
			mvfOpenGLHelper
			mvfTopologyHelpers
			mvLinuxDefinitions		
			dl 
			rt 
			
	)
endif ()
add_definitions( -Wno-unknown-pragmas )
add_definitions( -DLINUX_PLATFORM=1 )
add_definitions( -fpic)

casparcg_add_include_statement("modules/matrox2/matrox.h")
casparcg_add_init_statement("matrox_2::init" "matrox")
casparcg_add_module_project("matrox2")
