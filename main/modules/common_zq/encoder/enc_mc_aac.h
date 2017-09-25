#pragma once
#include "enc_base.h"
#include <enc_aac.h>
struct enc_mc_aac_params
{
	int32_t mpeg_version;
	//int32_t aac_object_type;
	int32_t header_type;
	int32_t he;
	int32_t vbr;
	int32_t bit_rate; 
	enc_mc_aac_params()
	{
		mpeg_version = MPEG4_AAC_AUDIO;
		//aac_object_type = AAC_LC;
		header_type = AAC_HEADER_ADTS;
		he = AAC_HE_NOTUSED;
		vbr = AAC_VBR_NOTUSED;
		bit_rate = 192;
	}
	~enc_mc_aac_params()
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
			else if (it->first == "aversion")
			{
				mpeg_version = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "aheader")
			{
				header_type = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "ahe")
			{
				he = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "avbr")
			{
				vbr = atol((it->second).c_str());
				it = ops.erase(it);
			}
 			//else if (it->first == "aobjtype")
 			//{
 			//	aac_object_type = atol((it->second).c_str());
			//  it = ops.erase(it);
 			//}
			else
			{
				it++;
			}
		}
	}
};


struct enc_mc_aac :public enc_base
{
public:
	enc_mc_aac(int32_t samplerate,int32_t nchannels);
	virtual ~enc_mc_aac();
	virtual bool init(std::map<std::string, std::string>& ops, bufstream_tt* bs);
	virtual bool encodeaudio(uint8_t* src, uint32_t nBytes);
	void convertbitrate(int32_t bitrate, uint32_t& bitrateindex);
private:
	int32_t samplerate_;
	int32_t num_channels_;

	aacaenc_tt* a_enc_;

};