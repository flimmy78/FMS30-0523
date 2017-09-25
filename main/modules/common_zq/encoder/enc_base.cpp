#include "enc_base.h"
#include "enc_mc_h264.h"
#include "enc_mc_mpeg2.h"
#include "enc_mc_mpa.h"
#include "enc_mc_aac.h"
#include "enc_mc_pcm.h"
#ifdef _MSC_VER
#include "enc_mc_ddpp.h"
#endif
enc_base::enc_base()
{
}

enc_base::~enc_base()
{
}

bool enc_base::init(std::map<std::string, std::string>&ops,bufstream_tt * bs)
{
	return false;
}

bool enc_base::encodevideo(uint8_t* src, uint32_t line_size, uint32_t fourcc)
{
	return false;
}

bool enc_base::encodeaudio(uint8_t* src, uint32_t nBytes)
{
	return false;
}

enc_base * enc_base::createvideo(ENC_TYPE etype, int32_t width, int32_t height)
{
	switch (etype)
	{
	case ENC_MC_H264:
		return new enc_mc_h264(width, height);
	case ENC_MC_MPEG2:
		return new enc_mc_mpeg2(width, height);
	}
	return nullptr;
}
enc_base * enc_base::createaudio(ENC_TYPE etype, int32_t samplerate, int32_t nchannels)
{
	switch (etype)
	{
	case ENC_MC_MPA:
		return new enc_mc_mpa(samplerate);
	case ENC_MC_PCM:
		return new enc_mc_pcm(samplerate, nchannels);
	case ENC_MC_AAC:
		return new enc_mc_aac(samplerate,nchannels);
#ifdef _MSC_VER
	case ENC_MC_DDPP:
		return new enc_mc_ddpp(samplerate, nchannels);
#endif
	}
	return nullptr;
}
