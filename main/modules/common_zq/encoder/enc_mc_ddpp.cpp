#include "enc_mc_ddpp.h"
#include "../mc_common.h"
#include <mcprofile.h>
#include <common/log.h>

enc_mc_ddpp::enc_mc_ddpp(int32_t samplerate, int32_t nchannels)
	:samplerate_(samplerate)
	, num_channels_(nchannels)
	, a_enc_(nullptr)
{
}

enc_mc_ddpp::~enc_mc_ddpp()
{
	if (a_enc_)
	{
		ddppOutAudioDone(a_enc_, 0);
		ddppOutAudioFree(a_enc_);
	}
}

bool enc_mc_ddpp::init(std::map<std::string, std::string>& ops, bufstream_tt* bs)
{
	dd_pp_settings a_settings;
	enc_mc_ddpp_params a_enc_params;
	a_enc_params.set_params(ops);

	ddppOutAudioDefaults(&a_settings, MCPROFILE_DEFAULT);
	a_settings.encoder_mode = a_enc_params.encoder_mode;
	a_settings.coding_mode = a_enc_params.coding_mode;
	switch (a_settings.coding_mode)
	{
	//case DD_AUDIOMODE_1_1: //该格式不支持
	case DD_AUDIOMODE_1_0:
	case DD_AUDIOMODE_2_0:
		a_settings.lfe_enabled = 0;
		break;
	}
	convertbitrate(a_enc_params.bit_rate, a_settings.data_rate);

	a_settings.num_input_channels = static_cast<int8_t>(num_channels_);

	if (ddppOutAudioChkSettings(get_rc, &a_settings, MCPROFILE_DEFAULT, CHECK_ALL, nullptr))
	{
		CASPAR_LOG(error) << L"ddppOutAudioChkSettings failed.";
		return false;
	}

	a_enc_ = ddppOutAudioNew(get_rc, &a_settings, DD_OPT_SI_PCM_SAMPLES, "DDPP-1002-FCDB-FA4A-F90F",0);
	if (!a_enc_)
	{
		CASPAR_LOG(error) << L"ddppOutAudioNew failed.";
		return false;
	}

	if (ddppOutAudioInit(a_enc_, bs))
	{
		CASPAR_LOG(error) << L"ddppOutAudioInit failed.";
		ddppOutAudioFree(a_enc_);
		return false;
	}
	return true;
}
bool enc_mc_ddpp::encodeaudio(uint8_t* src, uint32_t nBytes)
{
	ddppOutAudioPutBytes(a_enc_, src, nBytes);
	return true;
}

void enc_mc_ddpp::convertbitrate(int32_t bitrate, uint16_t& bitrateindex)
{
	switch (bitrate)
	{
	case 32:
		bitrateindex = DD_BITRATE_32;
		break;
	case 40:
		bitrateindex = DD_BITRATE_40;
		break;
	case 48:
		bitrateindex = DD_BITRATE_48;
		break;
	case 56:
		bitrateindex = DD_BITRATE_56;
		break;
	case 64:
		bitrateindex = DD_BITRATE_64;
		break;
	case 72:
		bitrateindex = DD_BITRATE_72;
		break;
	case 80:
		bitrateindex = DD_BITRATE_80;
		break;
	case 88:
		bitrateindex = DD_BITRATE_88;
		break;
	case 96:
		bitrateindex = DD_BITRATE_96;
		break;
	case 104:
		bitrateindex = DD_BITRATE_104;
		break;
	case 112:
		bitrateindex = DD_BITRATE_112;
		break;
	case 120:
		bitrateindex = DD_BITRATE_120;
		break;
	case 128:
		bitrateindex = DD_BITRATE_128;
		break;
	case 144:
		bitrateindex = DD_BITRATE_144;
		break;
	case 160:
		bitrateindex = DD_BITRATE_160;
		break;
	case 176:
		bitrateindex = DD_BITRATE_176;
		break;
	case 192:
		bitrateindex = DD_BITRATE_192;
		break;
	case 200:
		bitrateindex = DD_BITRATE_200;
		break;
	case 208:
		bitrateindex = DD_BITRATE_208;
		break;
	case 216:
		bitrateindex = DD_BITRATE_216;
		break;
	case 224:
		bitrateindex = DD_BITRATE_224;
		break;
	case 232:
		bitrateindex = DD_BITRATE_232;
		break;
	case 240:
		bitrateindex = DD_BITRATE_240;
		break;
	case 248:
		bitrateindex = DD_BITRATE_248;
		break;
	case 256:
		bitrateindex = DD_BITRATE_256;
		break;
	case 272:
		bitrateindex = DD_BITRATE_272;
		break;
	case 288:
		bitrateindex = DD_BITRATE_288;
		break;
	case 300:
		bitrateindex = DD_BITRATE_300;
		break;
	case 304:
		bitrateindex = DD_BITRATE_304;
		break;
	case 320:
		bitrateindex = DD_BITRATE_320;
		break;
	case 336:
		bitrateindex = DD_BITRATE_336;
		break;
	case 352:
		bitrateindex = DD_BITRATE_352;
		break;
	case 368:
		bitrateindex = DD_BITRATE_368;
		break;
	case 384:
		bitrateindex = DD_BITRATE_384;
		break;
	case 400:
		bitrateindex = DD_BITRATE_400;
		break;
	case 448:
		bitrateindex = DD_BITRATE_448;
		break;
	case 512:
		bitrateindex = DD_BITRATE_512;
		break;
	case 576:
		bitrateindex = DD_BITRATE_576;
		break;
	case 640:
		bitrateindex = DD_BITRATE_640;
		break;
	case 704:
		bitrateindex = DD_BITRATE_704;
		break;
	case 768:
		bitrateindex = DD_BITRATE_768;
		break;
	case 832:
		bitrateindex = DD_BITRATE_832;
		break;
	case 896:
		bitrateindex = DD_BITRATE_896;
		break;
	case 960:
		bitrateindex = DD_BITRATE_960;
		break;
	case 1008:
		bitrateindex = DD_BITRATE_1008;
		break;
	case 1024:
		bitrateindex = DD_BITRATE_1024;
		break;
	default:
		bitrateindex = DD_BITRATE_192;
		break;
	}

}
