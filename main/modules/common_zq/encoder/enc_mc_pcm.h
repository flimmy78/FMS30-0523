#pragma once
#include "enc_base.h"
#include <enc_pcm.h>
struct enc_mc_pcm :public enc_base
{
public:
	enc_mc_pcm(int32_t samplerate, int32_t nchannels);
	virtual ~enc_mc_pcm();
	virtual bool init(std::map<std::string, std::string>& ops, bufstream_tt* bs);
	virtual bool encodeaudio(uint8_t* src, uint32_t nBytes);
private:
	int32_t samplerate_;
	int32_t num_channels_;

	pcmaenc_tt* a_enc_;

};