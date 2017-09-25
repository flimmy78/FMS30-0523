#include "enc_mc_mpeg2.h"
#include "../mc_common.h"
#include <common/log.h>

enc_mc_mpeg2::enc_mc_mpeg2(int32_t width, int32_t height)
	:width_(width)
	, height_(height)
	, v_enc_(nullptr)
{
}

enc_mc_mpeg2::~enc_mc_mpeg2()
{
	if (v_enc_)
	{
		mpegOutVideoDone(v_enc_, 0);
		mpegOutVideoFree(v_enc_);
	}
}

bool enc_mc_mpeg2::init(std::map<std::string, std::string>& ops, bufstream_tt * bs)
{
	mpeg_v_settings v_settings;
	enc_mc_mpeg2_params v_enc_params;
	v_enc_params.set_params(ops);

	mpegOutVideoDefaults(&v_settings, v_enc_params.preset, VM_PAL);

	if (-1 != v_enc_params.profile)	v_settings.profile = v_enc_params.profile;
	if (-1 != v_enc_params.level)	v_settings.level = v_enc_params.level;

	v_settings.frame_rate = v_enc_params.frame_rate;
	v_settings.prog_frame = v_enc_params.frame_type;
	v_settings.topfirst = v_enc_params.field_order;
	v_settings.constant_bitrate = v_enc_params.bit_rate_mode;
	v_settings.bit_rate = v_enc_params.bit_rate;
	v_settings.N = v_enc_params.gop_size;
	v_settings.M = v_enc_params.b_frames + 1;
	v_settings.def_horizontal_size = width_;
	v_settings.def_vertical_size = height_;

	if (width_ >= 1920)
		v_settings.level = LEVEL_HIGH;

	if (v_settings.constant_bitrate == VBR_CONSTANT)
		v_settings.fixed_vbv_delay = 0;

	mpegOutVideoPerformance(&v_settings, PERF_ONLINE, v_enc_params.perf, 0);
	if (mpegOutVideoChkSettings(get_rc, &v_settings, CHECK_ALL, nullptr))
	{
		CASPAR_LOG(error) << L"mpegOutVideoChkSettings failed.";
		return false;
	}

	v_enc_ = mpegOutVideoNew(get_rc, &v_settings, 0, 0xFFFFFFFF, 0, 0);
	if (!v_enc_)
	{
		CASPAR_LOG(error) << L"mpegOutVideoNew failed.";
		return false;
	}

	int32_t init_options = 0;
	if (mpegOutVideoInit(v_enc_, bs, init_options))
	{
		CASPAR_LOG(error) << L"mpegOutVideoInit failed.";
		mpegOutVideoFree(v_enc_);
		return false;
	}

	return true;
}

bool enc_mc_mpeg2::encodevideo(uint8_t* src, uint32_t line_size, uint32_t fourcc)
{
	uint32_t option_flags = 0;
	mpegOutVideoPutFrame(v_enc_, src, line_size, width_, height_, fourcc, option_flags);
	return true;
}
