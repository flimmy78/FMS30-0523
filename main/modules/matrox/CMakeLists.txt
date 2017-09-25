cmake_minimum_required (VERSION 2.6)
project (matrox)

#set(CMAKE_C_COMPILER g++)	# 更规范c源代码

set(SOURCES
		matrox.cpp
		producer/matrox_producer.cpp
		consumer/matrox_consumer.cpp
		matrox_2022_capture.cpp	
		matrox_2022_playback.cpp
		matrox_sdi_capture.cpp	
		matrox_sdi_playback.cpp
		
		ErrorNotificationCallback.cpp
		GenlockStatusCallback.cpp
		MvErrorCallbackHandler.cpp
		SDIInConnectorStatusCallback.cpp
		SfpSdiStatusCallback.cpp
)
set(HEADERS
		matrox.h
		producer/matrox_producer.h
		consumer/matrox_consumer.h
		matrox_2022_capture.h		
		matrox_2022_playback.h
		matrox_sdi_capture.h	
		matrox_sdi_playback.h
		common.h
		cardinfo.h

		ErrorNotificationCallback.h
		GenlockStatusCallback.h
		MvErrorCallbackHandler.h
		SDIInConnectorStatusCallback.h
		SfpSdiStatusCallback.h		
)

add_library(matrox ${SOURCES} ${HEADERS})

include_directories(..)
include_directories(../..)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${FFMPEG_INCLUDE_PATH})
include_directories(${RXCPP_INCLUDE_PATH})
include_directories(${ASMLIB_INCLUDE_PATH})
include_directories(${MATROX_INCLUDE_PATH})
include_directories(${IPP_INCLUDE_PATH})
set_target_properties(matrox PROPERTIES FOLDER modules)
source_group(sources ./*)
if (MSVC)
	target_link_libraries(matrox
			common
			core
			ffmpeg
		 
			MVCOM.lib 
			MvCOMEntry.lib
			MvfFlexAPI.lib
			mvFileIO.lib
			MvfOpenGLHelper.lib
			mvsCommon.lib
			mvsCommonMFCDialogs.lib
			MvUtility.lib

	)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(matrox
			common
			core
			ffmpeg
			
			mvCOM 
			mvCOMEntry
			mvfFlexAPI
			mvfOpenGLHelper
			mvLinuxDefinitions
			mvUtility			
	)
endif ()

casparcg_add_include_statement("modules/matrox/matrox.h")
casparcg_add_init_statement("matrox::init" "matrox")
casparcg_add_module_project("matrox")

if(MSVC)
	casparcg_add_runtime_dependency("${DEPENDENCIES_FOLDER}/intel/ipp/bin/${PLATFORM_FOLDER_NAME}/ippcc.dll")
	casparcg_add_runtime_dependency("${DEPENDENCIES_FOLDER}/intel/ipp/bin/${PLATFORM_FOLDER_NAME}/ippccl9.dll")
	casparcg_add_runtime_dependency("${DEPENDENCIES_FOLDER}/intel/ipp/bin/${PLATFORM_FOLDER_NAME}/ippcore.dll")
else()
	casparcg_add_runtime_dependency("${DEPENDENCIES_FOLDER}/intel/ipp/lib/${PLATFORM_FOLDER_NAME}/libippcc.so")
	casparcg_add_runtime_dependency("${DEPENDENCIES_FOLDER}/intel/ipp/lib/${PLATFORM_FOLDER_NAME}/libippccl9.so")
	casparcg_add_runtime_dependency("${DEPENDENCIES_FOLDER}/intel/ipp/lib/${PLATFORM_FOLDER_NAME}/libippcore.so")
endif()
