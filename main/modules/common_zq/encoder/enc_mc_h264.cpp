#include "enc_mc_h264.h"
#include "../mc_common.h"
#include <common/log.h>
enc_mc_h264::enc_mc_h264(int32_t width, int32_t height)
	:width_(width)
	,height_(height)
	,v_enc_(nullptr)
{
}

enc_mc_h264::~enc_mc_h264()
{
	if (v_enc_)
	{
		h264OutVideoDone(v_enc_, 0);
		h264OutVideoFree(v_enc_);
	}
}

bool enc_mc_h264::init(std::map<std::string, std::string>& ops, bufstream_tt * bs)
{
	h264_v_settings v_settings;
	enc_mc_h264_params v_enc_params;
	v_enc_params.set_params(ops);

	h264OutVideoDefaultSettings(v_enc_params.preset, width_, height_, v_enc_params.frame_rate, v_enc_params.frame_type, get_rc, &v_settings, nullptr);
	h264OutVideoPerformance(&v_settings, 0, v_enc_params.perf, 0);

	if (-1 != v_enc_params.profile)	v_settings.profile_id = v_enc_params.profile;
	if (-1 != v_enc_params.level)	v_settings.level_id = v_enc_params.level;
	v_settings.field_order = v_enc_params.field_order;
	v_settings.bit_rate_mode = v_enc_params.bit_rate_mode;
	v_settings.bit_rate = v_enc_params.bit_rate;
	v_settings.idr_interval = v_enc_params.gop_size;
	v_settings.reordering_delay = v_enc_params.b_frames + 1;
	
	v_settings.buffering = 3;
	v_settings.encoding_buffering = 2;

	if (h264OutVideoChkSettings(get_rc, &v_settings, H264_CHECK_AND_ADJUST | H264_CHECK_FOR_LEVEL, nullptr) == H264ERROR_FAILED)
	{
		CASPAR_LOG(error) << L"h264OutVideoChkSettings failed.";
		return false;
	}

	v_enc_ = h264OutVideoNew(get_rc, &v_settings, 0, 0xFFFFFFFF, 0, 0);
	if (!v_enc_)
	{
		CASPAR_LOG(error) << L"h264OutVideoNew failed.";
		return false;
	}

	int32_t init_options = 0;
	void *opt_list[10];
	if (h264OutVideoInit(v_enc_, bs, init_options, &opt_list[0]))
	{
		CASPAR_LOG(error) << L"h264OutVideoInit failed.";
		h264OutVideoFree(v_enc_);
		return false;
	}

	return true;
}

bool enc_mc_h264::encodevideo(uint8_t* src, uint32_t line_size, uint32_t fourcc)
{
	void *ext_info_stack[16] = { 0 };
	uint32_t option_flags = 0;
	void **ext_info = &ext_info_stack[0];
	h264OutVideoPutFrame(v_enc_, src, line_size, width_, height_, fourcc, option_flags, ext_info);
	return true;
}
