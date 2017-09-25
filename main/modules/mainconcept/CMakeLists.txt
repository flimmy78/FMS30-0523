cmake_minimum_required (VERSION 2.6)
project (mainconcept)

#set(CMAKE_C_COMPILER g++)	# 更规范c源代码

set(SOURCES
		consumer/mainconcept_consumer.cpp

		mainconcept.cpp
)
set(HEADERS
		consumer/mainconcept_consumer.h

		mainconcept.h
)

add_library(mainconcept ${SOURCES} ${HEADERS})

include_directories(..)
include_directories(../..)
include_directories(../common_zq)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${FFMPEG_INCLUDE_PATH})
include_directories(${RXCPP_INCLUDE_PATH})
include_directories(${ASMLIB_INCLUDE_PATH})
include_directories(${DTAPI_INCLUDE_PATH})
include_directories(${MAINCONCEPT_INCLUDE_PATH})

set_target_properties(mainconcept PROPERTIES FOLDER modules)
source_group(sources ./*)
source_group(sources\\consumer consumer/*)

if (MSVC)
	target_link_libraries(mainconcept
			common_zq
			common
			core
			
	)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(mainconcept
			common_zq
			common
			core
	)
endif ()

if(MSVC)
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_bc_net_renderer.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_config_avc.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_config_mp2v.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_config_mpa.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_net_tools.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_aac.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_avc.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_mp2v.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_mpa.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_pcm.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_mux_mp2.dll")
else ()
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_bc_net_renderer.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_enc_mp2v.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_enc_mpa.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_net_tools.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_parser_sdp.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_config_avc.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_enc_aac.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_enc_avc.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_enc_pcm.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_mux_mp2.so")
endif ()

casparcg_add_include_statement("modules/mainconcept/mainconcept.h")
casparcg_add_init_statement("mainconcept::init" "mainconcept")
casparcg_add_module_project("mainconcept")
