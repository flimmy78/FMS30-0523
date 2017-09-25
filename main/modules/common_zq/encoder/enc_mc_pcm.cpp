#include "enc_mc_pcm.h"
#include "../mc_common.h"
#include <common/log.h>

enc_mc_pcm::enc_mc_pcm(int32_t samplerate, int32_t nchannels)
	:samplerate_(samplerate)
	, num_channels_(nchannels)
	, a_enc_(nullptr)
{
}

enc_mc_pcm::~enc_mc_pcm()
{
	if (a_enc_)
	{
		pcmOutAudioDone(a_enc_, 0);
		pcmOutAudioFree(a_enc_);
	}
}

bool enc_mc_pcm::init(std::map<std::string, std::string>& ops, bufstream_tt * bs)
{
	pcm_a_settings a_settings;
	pcmOutAudioDefaults(&a_settings, MCPROFILE_DEFAULT);

	a_settings.num_channels = static_cast<int16_t>(num_channels_);
	a_settings.pcm_quantization = PCM_16BITS;
	a_settings.audio_layer = AES3_302M_AUDIO;

	if (pcmOutAudioChkSettings(get_rc, &a_settings, 0, samplerate_, CHECK_ALL, nullptr))
	{
		CASPAR_LOG(error) << L"pcmOutAudioChkSettings failed.";
		return false;
	}

	a_enc_ = pcmOutAudioNew(get_rc, &a_settings, 0, FRAMERATE25, samplerate_);
	if (!a_enc_)
	{
		CASPAR_LOG(error) << L"pcmOutAudioNew failed.";
		return false;
	}

	if (pcmOutAudioInit(a_enc_, bs))
	{
		CASPAR_LOG(error) << L"pcmOutAudioInit failed.";
		pcmOutAudioFree(a_enc_);
		return false;
	}
	return true;
}

bool enc_mc_pcm::encodeaudio(uint8_t* src, uint32_t nBytes)
{
	pcmOutAudioPutBytes(a_enc_, src, nBytes);
	return true;
}
