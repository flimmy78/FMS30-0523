#include "enc_mc_aac.h"
#include "../mc_common.h"
#include <common/log.h>
enc_mc_aac::enc_mc_aac(int32_t samplerate, int32_t nchannels)
	:samplerate_(samplerate)
	,num_channels_(nchannels)
	,a_enc_(nullptr)
{
}

enc_mc_aac::~enc_mc_aac()
{
	if (a_enc_)
	{
		aacOutAudioDone(a_enc_, 0);
		aacOutAudioFree(a_enc_);
	}
}

bool enc_mc_aac::init(std::map<std::string, std::string>& ops, bufstream_tt * bs)
{
	aac_a_settings a_settings;
	enc_mc_aac_params a_enc_params;
	a_enc_params.set_params(ops);

	aacOutAudioDefaults(&a_settings, MCPROFILE_DEFAULT);
	a_settings.mpeg_version = a_enc_params.mpeg_version;
	//a_settings.aac_object_type = a_enc_params.aac_object_type;
	a_settings.header_type = a_enc_params.header_type;
	a_settings.he = a_enc_params.he;
	a_settings.vbr = a_enc_params.vbr;

	convertbitrate(a_enc_params.bit_rate, a_settings.audio_bitrate_index);

	a_settings.bits_per_sample = AAC_BITS_PER_SAMPLE_16;
	switch (num_channels_)
	{
	case 1:
		a_settings.input_channels = AAC_CHANNELS_1_MONO;
		break;
	case 2:
		a_settings.input_channels = AAC_CHANNELS_2_STEREO;
		break;
	case 3:
		a_settings.input_channels = AAC_CHANNELS_3_FL_FR_FC;
		break;
	case 4:
		a_settings.input_channels = AAC_CHANNELS_4_FL_FR_FC_BC;
		break;
	case 5:
		a_settings.input_channels = AAC_CHANNELS_5_FL_FR_FC_BL_BR;
		break;
	case 6:
		a_settings.input_channels = AAC_CHANNELS_6_FL_FR_FC_BL_BR_LF;
		break;
	case 8:
		a_settings.input_channels = AAC_CHANNELS_8_FL_FR_FC_LF_BL_BR_SL_SR;
		break;
	default:
		break;
	}

	if (aacOutAudioChkSettings(get_rc, &a_settings, MCPROFILE_DEFAULT, samplerate_, CHECK_ALL, nullptr))
	{
		CASPAR_LOG(error) << L"aacOutAudioChkSettings failed.";
		return false;
	}
	a_enc_ = aacOutAudioNew(get_rc, &a_settings, 0, 0xFFFFFFFF, samplerate_);
	if (!a_enc_)
	{
		CASPAR_LOG(error) << L"aacOutAudioNew failed.";
		return false;
	}

	if (aacOutAudioInit(a_enc_, bs))
	{
		CASPAR_LOG(error) << L"aacOutAudioInit failed.";
		aacOutAudioFree(a_enc_);
		return false;
	}
	return true;
}

bool enc_mc_aac::encodeaudio(uint8_t* src, uint32_t nBytes)
{
	aacOutAudioPutBytes(a_enc_, src, nBytes);
	return true;
}

void enc_mc_aac::convertbitrate(int32_t bitrate, uint32_t & bitrateindex)
{
	switch (bitrate)
	{
	case 6:
		bitrateindex = AAC_AUDIOBITRATE_006;
		break;
	case 7:
		bitrateindex = AAC_AUDIOBITRATE_007;
		break;
	case 8:
		bitrateindex = AAC_AUDIOBITRATE_008;
		break;
	case 10:
		bitrateindex = AAC_AUDIOBITRATE_010;
		break;
	case 12:
		bitrateindex = AAC_AUDIOBITRATE_012;
		break;
	case 14:		
		bitrateindex = AAC_AUDIOBITRATE_014;
		break;
	case 16:
		bitrateindex = AAC_AUDIOBITRATE_016;
		break;
	case 20:
		bitrateindex = AAC_AUDIOBITRATE_020;
		break;
	case 24:
		bitrateindex = AAC_AUDIOBITRATE_024;
		break;
	case 28:
		bitrateindex = AAC_AUDIOBITRATE_028;
		break;
	case 32:
		bitrateindex = AAC_AUDIOBITRATE_032;
		break;
	case 40:
		bitrateindex = AAC_AUDIOBITRATE_040;
		break;
	case 48:
		bitrateindex = AAC_AUDIOBITRATE_048;
		break;
	case 56:
		bitrateindex = AAC_AUDIOBITRATE_056;
		break;
	case 64:
		bitrateindex = AAC_AUDIOBITRATE_064;
		break;
	case 80:
		bitrateindex = AAC_AUDIOBITRATE_080;
		break;
	case 96:
		bitrateindex = AAC_AUDIOBITRATE_096;
		break;
	case 112:
		bitrateindex = AAC_AUDIOBITRATE_112;
		break;
	case 128:
		bitrateindex = AAC_AUDIOBITRATE_128;
		break;
	case 160:
		bitrateindex = AAC_AUDIOBITRATE_160;
		break;
	case 192:
		bitrateindex = AAC_AUDIOBITRATE_192;
		break;
	case 224:
		bitrateindex = AAC_AUDIOBITRATE_224;
		break;
	case 256:
		bitrateindex = AAC_AUDIOBITRATE_256;
		break;
	case 320:
		bitrateindex = AAC_AUDIOBITRATE_320;
		break;
	case 384:
		bitrateindex = AAC_AUDIOBITRATE_384;
		break;
	case 448:
		bitrateindex = AAC_AUDIOBITRATE_448;
		break;
	case 512:
		bitrateindex = AAC_AUDIOBITRATE_512;
		break;
	case 640:
		bitrateindex = AAC_AUDIOBITRATE_640;
		break;
	case 768:
		bitrateindex = AAC_AUDIOBITRATE_768;
		break;
	case 896:
		bitrateindex = AAC_AUDIOBITRATE_896;
		break;
	case 1024:
		bitrateindex = AAC_AUDIOBITRATE_1024;
		break;
	default:
		bitrateindex = AAC_AUDIOBITRATE_192;
		break;
	}
}
