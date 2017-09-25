#pragma once
#include "enc_base.h"
#include <enc_ddpp.h>
#include <dd_def.h>
struct enc_mc_ddpp_params
{
	int32_t encoder_mode;
	int32_t coding_mode;
	int32_t bit_rate;
	enc_mc_ddpp_params()
	{
		encoder_mode = DD_ENC_MODE_DDP;
		coding_mode = DD_AUDIOMODE_2_0;
		bit_rate = 192;
	}
	~enc_mc_ddpp_params()
	{

	}
	void set_params(std::map<std::string, std::string>& ops)
	{
		auto it = ops.begin();
		while (it != ops.end())
		{
			if (it->first == "aencodermode")
			{
				encoder_mode = atol((it->second).c_str());
				it = ops.erase(it);
			}			
			else if (it->first == "acodingmode")
			{
				coding_mode = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "abitrate")
			{
				bit_rate = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else
			{
				it++;
			}

		}
	}
};


struct enc_mc_ddpp :public enc_base
{
public:
	enc_mc_ddpp(int32_t samplerate, int32_t nchannels);
	virtual ~enc_mc_ddpp();
	virtual bool init(std::map<std::string, std::string>& ops, bufstream_tt* bs);
	virtual bool encodeaudio(uint8_t* src, uint32_t nBytes);
	void convertbitrate(int32_t bitrate,uint16_t& bitrateindex);
private:
	int32_t samplerate_;
	int32_t num_channels_;

	ddppaenc_tt* a_enc_;
};