cmake_minimum_required (VERSION 2.6)
project (common_zq)

#set(CMAKE_C_COMPILER g++)	# 更规范c源代码

set(SOURCES
		bufstream/buf_fifo.c
		bufstream/buf_file.c
		bufstream/sr_fifo.c

		encoder/enc_base.cpp 
		encoder/enc_mc_aac.cpp
		encoder/enc_mc_h264.cpp
		encoder/enc_mc_mpa.cpp
		encoder/enc_mc_mpeg2.cpp
		encoder/enc_mc_pcm.cpp
		
		muxer/mc_mpeg_muxer.cpp
		muxer/muxer_base.cpp
		
		render/dt_net_render.cpp
		render/mc_file_render.cpp
		render/mc_net_render.cpp
		render/render_base.cpp
		
		mc_common.cpp
)
set(HEADERS
		bufstream/buf_fifo.h
		bufstream/buf_file.h
		bufstream/sr_fifo.h
		bufstream/mc_os_common.h

		encoder/enc_base.h 
		encoder/enc_mc_aac.h
		encoder/enc_mc_h264.h
		encoder/enc_mc_mpa.h
		encoder/enc_mc_mpeg2.h
		encoder/enc_mc_pcm.h
		
		muxer/mc_mpeg_muxer.h
		muxer/muxer_base.h
		
		render/dt_net_render.h
		render/mc_file_render.h
		render/mc_net_render.h
		render/render_base.h
		
		mc_common.h
)

add_library(common_zq ${SOURCES} ${HEADERS})

include_directories(../..)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${RXCPP_INCLUDE_PATH})
include_directories(${DTAPI_INCLUDE_PATH})
include_directories(${MAINCONCEPT_INCLUDE_PATH})

set_target_properties(common_zq PROPERTIES FOLDER modules)
source_group(sources ./*)
source_group(sources\\bufstream bufstream/*)
source_group(sources\\encoder encoder/*)
source_group(sources\\muxer muxer/*)
source_group(sources\\render render/*)

if (MSVC)
	target_link_libraries(common_zq
			common
			
			bc_net_renderer.lib
			parser_sdp.lib
			net_tools.lib
			enc_avc.lib
			enc_mp2v.lib
			enc_mpa.lib
			enc_pcm.lib
			enc_aac.lib
			mux_mp2.lib
	)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(common_zq
			common

			dtapi64

			-Wl,--start-group
			demo_bc_net_renderer
			demo_parser_sdp
			demo_net_tools
			mc_config_avc
			mc_enc_avc
			demo_enc_mp2v
			demo_enc_mpa
			mc_enc_pcm
			mc_enc_aac
			mc_mux_mp2
			
			-Wl,--end-group

			pthread
			dl
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

casparcg_add_module_project("common_zq")
