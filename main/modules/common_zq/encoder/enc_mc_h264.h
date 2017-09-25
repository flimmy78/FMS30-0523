#pragma once
#include "enc_base.h"
#include <enc_avc.h>

struct enc_mc_h264_params
{
public:
	int32_t     preset; //2-H264_MAIN 5-H264_HIGH
	int32_t		profile;
	int32_t     level;
	int32_t     perf; //0-H264_PERF_FASTEST    9-H264_PERF_BALANCED   15-H264_PERF_BEST_Q, default 9
	int32_t     frame_type;  //0-H264_PROGRESSIVE  1-H264_INTERLACED  2-H264_MBAFF
	int32_t     field_order;	// 0-top field first    1-bottom field first
	double      frame_rate;
	int32_t     gop_size;
	int32_t     b_frames;
	int32_t     bit_rate_mode;	//0-H264_CBR 1-H264_CQT  2-H264_VBR  3-H264_TQM  4-H264_INTRARC
	int32_t     bit_rate;
	enc_mc_h264_params()
	{
		preset = H264_MAIN;
		profile = -1;
		level = -1;
		perf = H264_PERF_BALANCED;
		frame_type = H264_INTERLACED;
		field_order = H264_TOPFIELD_FIRST;
		frame_rate = 25;
		gop_size = 33;
		b_frames = 2;
		bit_rate_mode = H264_CBR;
		bit_rate = 6000000;
	}
	~enc_mc_h264_params()
	{
	}
	void set_params(std::map<std::string, std::string>& ops)
	{
		auto it = ops.begin();
		while (it != ops.end())
		{
			//video
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


struct enc_mc_h264:public enc_base
{
public:
	enc_mc_h264(int32_t width,int32_t height);
	virtual ~enc_mc_h264();
	virtual bool init(std::map<std::string, std::string>& ops, bufstream_tt* bs);
	virtual bool encodevideo(uint8_t* src, uint32_t line_size, uint32_t fourcc);
private:
	int32_t width_;
	int32_t height_;
	h264venc_tt*   v_enc_;

};