#include "enc_mc_mpa.h"
#include "../mc_common.h"
#include <common/log.h>

enc_mc_mpa::enc_mc_mpa(int32_t samplerate)
	:samplerate_(samplerate)
	,a_enc_(nullptr)
{
}

enc_mc_mpa::~enc_mc_mpa()
{
	if (a_enc_)
	{
		mpegOutAudioDone(a_enc_, 0);
		mpegOutAudioFree(a_enc_);
	}
}

bool enc_mc_mpa::init(std::map<std::string, std::string>& ops, bufstream_tt * bs)
{
	mpeg_a_settings a_settings;
	enc_mc_mpa_params a_enc_params;
	a_enc_params.set_params(ops);

	mpegOutAudioDefaults(&a_settings, MCPROFILE_DEFAULT);

	a_settings.audio_layer = a_enc_params.audio_layer;
	a_settings.audio_mode = a_enc_params.audio_mode;

	convertbitrate(a_enc_params.bit_rate, a_enc_params.audio_layer, a_settings.audio_bitrate);

	if (mpegOutAudioChkSettings(get_rc, &a_settings, MCPROFILE_DEFAULT, samplerate_, CHECK_ALL, nullptr))
	{
		CASPAR_LOG(error) << L"mpegOutAudioChkSettings failed.";
		return false;
	}
	// audio encoder instance
	a_enc_ = mpegOutAudioNew(get_rc, &a_settings, 0, 0, samplerate_);
	if (!a_enc_)
	{
		CASPAR_LOG(error) << L"mpegOutAudioNew failed.";
		return false;
	}

	// Attach previously created bufstream to new encoder instance
	if (mpegOutAudioInit(a_enc_, bs))
	{
		CASPAR_LOG(error) << L"mpegOutAudioInit failed.";
		mpegOutAudioFree(a_enc_);
		return false;
	}
	return true;
}

bool enc_mc_mpa::encodeaudio(uint8_t* src, uint32_t nBytes)
{
	mpegOutAudioPutBytes(a_enc_, src, nBytes);
	return true;
}

void enc_mc_mpa::convertbitrate(int32_t bitrate, int32_t alayer, int32_t & bitrateindex)
{ 
	if (MPEG_AUDIO_LAYER1 == alayer)
	{
		switch (bitrate)
		{
		case 32:
			bitrateindex = L1_AUDIOBITRATE32;
			break;
		case 64:
			bitrateindex = L1_AUDIOBITRATE64;
			break;
		case 96:
			bitrateindex = L1_AUDIOBITRATE96;
			break;
		case 128:
			bitrateindex = L1_AUDIOBITRATE128;
			break;
		case 160:
			bitrateindex = L1_AUDIOBITRATE160;
			break;
		case 192:
			bitrateindex = L1_AUDIOBITRATE192;
			break;
		case 224:
			bitrateindex = L1_AUDIOBITRATE224;
			break;
		case 256:
			bitrateindex = L1_AUDIOBITRATE256;
			break;
		case 288:
			bitrateindex = L1_AUDIOBITRATE288;
			break;
		case 320:
			bitrateindex = L1_AUDIOBITRATE320;
			break;
		case 352:
			bitrateindex = L1_AUDIOBITRATE352;
			break;
		case 384:
			bitrateindex = L1_AUDIOBITRATE384;
			break;
		case 416:
			bitrateindex = L1_AUDIOBITRATE416;
			break;
		case 448:
			bitrateindex = L1_AUDIOBITRATE448;
			break;
		default:
			bitrateindex = L1_AUDIOBITRATE192;
			break;
		}
	}
	else if (MPEG_AUDIO_LAYER2 == alayer)
	{
		switch (bitrate)
		{
		case 32:
			bitrateindex = L2_AUDIOBITRATE32;
			break;
		case 48:
			bitrateindex = L2_AUDIOBITRATE48;
			break;
		case 56:
			bitrateindex = L2_AUDIOBITRATE56;
			break;
		case 64:
			bitrateindex = L2_AUDIOBITRATE64;
			break;
		case 80:
			bitrateindex = L2_AUDIOBITRATE80;
			break;
		case 96:
			bitrateindex = L2_AUDIOBITRATE96;
			break;
		case 112:
			bitrateindex = L2_AUDIOBITRATE112;
			break;
		case 128:
			bitrateindex = L2_AUDIOBITRATE128;
			break;
		case 160:
			bitrateindex = L2_AUDIOBITRATE160;
			break;
		case 192:
			bitrateindex = L2_AUDIOBITRATE192;
			break;
		case 224:
			bitrateindex = L2_AUDIOBITRATE224;
			break;
		case 256:
			bitrateindex = L2_AUDIOBITRATE256;
			break;
		case 320:
			bitrateindex = L2_AUDIOBITRATE320;
			break;
		case 384:
			bitrateindex = L2_AUDIOBITRATE384;
			break;
		default:
			bitrateindex = L2_AUDIOBITRATE192;
			break;
		}
	}	
}
