#pragma once
#include "enc_base.h"
#include <enc_mp2v.h>
struct enc_mc_mpeg2_params
{
public:
	int32_t     preset; //2-MPEG_MPEG2
	int32_t		profile;
	int32_t     level;
	int32_t     perf; //0~31,  default 15
	int32_t     frame_type;  // 0-interlaced        1-progressive
	int32_t     field_order;	//1-top field first      0-bottom field first
	double      frame_rate;
	int32_t     gop_size;
	int32_t     b_frames;
	int32_t     bit_rate_mode;	//0-VBR_VARIABLE1  1-VBR_CONSTANT  2-VBR_CQT   3-VBR_CQT_STRICT
	int32_t     bit_rate;
	enc_mc_mpeg2_params()
	{
		preset = MPEG_MPEG2;
		profile = -1;
		level = -1;
		perf = 15;
		frame_type = 0;
		field_order = 1;
		frame_rate = 25;
		gop_size = 15;
		b_frames = 2;
		bit_rate_mode = VBR_CONSTANT;
		bit_rate = 6000000;
	}
	~enc_mc_mpeg2_params()
	{
	}
	void set_params(std::map<std::string, std::string>& ops)
	{
		auto it = ops.begin();
		while (it != ops.end())
		{
			if (it->first == "vpreset")
			{
				preset = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vprof")
			{
				profile = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vlevel")
			{
				level = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vperf") //performance
			{
				perf = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vframetype") //frame type
			{
				frame_type = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vfieldorder") //field order
			{
				field_order = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vframerate") //frame rate
			{
				frame_rate = atof((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vratemode") //rate-mode CBR VBR
			{
				bit_rate_mode = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vbitrate")
			{
				bit_rate = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vgop")
			{
				gop_size = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "vbframes")
			{
				b_frames = atol((it->second).c_str());
				it = ops.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
};

struct enc_mc_mpeg2 :public enc_base
{
public:
	enc_mc_mpeg2(int32_t width, int32_t height);
	virtual ~enc_mc_mpeg2();
	virtual bool init(std::map<std::string, std::string>& ops, bufstream_tt* bs);
	virtual bool encodevideo(uint8_t* src, uint32_t line_size, uint32_t fourcc);
private:
	int32_t width_;
	int32_t height_;
	mpegvenc_tt*   v_enc_;

};