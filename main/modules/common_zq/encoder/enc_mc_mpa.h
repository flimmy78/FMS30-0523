#pragma once
#include "enc_base.h"
#include <enc_mpa.h>

struct enc_mc_mpa_params
{
	int32_t audio_layer;
	int32_t audio_mode;
	int32_t bit_rate;
	enc_mc_mpa_params()
	{
		audio_layer = MPEG_AUDIO_LAYER2;
		audio_mode = MPG_MD_STEREO;
		bit_rate= 192;
	}
	~enc_mc_mpa_params()
	{
	}
	void set_params(std::map<std::string, std::string>& ops)
	{
		auto it = ops.begin();
		while (it != ops.end())
		{
			if (it->first == "abitrate")
			{
				bit_rate = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "amode")
			{
				audio_mode = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "alayer")
			{
				audio_layer = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

};

struct enc_mc_mpa :public enc_base
{
public:
	enc_mc_mpa(int32_t samplerate);
	virtual ~enc_mc_mpa();
	virtual bool init(std::map<std::string, std::string>& ops, bufstream_tt* bs);
	virtual bool encodeaudio(uint8_t* src, uint32_t nBytes);
	void convertbitrate(int32_t bitrate, int32_t alayer, int32_t& bitrateindex);
private:
	int32_t samplerate_;
	mpegaenc_tt* a_enc_;
};