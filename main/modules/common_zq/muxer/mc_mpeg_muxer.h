#pragma once
#include "muxer_base.h"
#include <mux_mp2.h>

//muxer params
struct mc_mpeg_muxer_params
{
public:
	int32_t enabled_paddings;
	int32_t required_bitrate;
	int32_t PCR_repetition_rate;
	int32_t PSI_repetition_rate;
	int32_t v_delay;
	int32_t a_delay;
	int32_t video_pid;
	std::map<int32_t, int32_t> audio_pids;
	
	mc_mpeg_muxer_params();
	~mc_mpeg_muxer_params();
	void set_params(std::map<std::string, std::string>& ops);
	int32_t get_apid(int32_t index);
private:
	void split_apids(std::string apids, std::string pattern);
};

struct mc_mpeg_muxer:public muxer_base
{
public:
	mc_mpeg_muxer();
	virtual ~mc_mpeg_muxer();
	virtual bool init(std::map<std::string, std::string>& ops, bufstream_tt* bs);
	virtual void addvideostream();
	virtual void addaudiostream(int32_t index);
	virtual bufstream_tt* getaudiobufstrm(int32_t index);
	virtual bufstream_tt* getvideobufstrm();

private:
	mc_mpeg_muxer_params  mux_params_;
	mp2muxer_tt *mp2muxer = nullptr;
	//video
	fifo_stream_tt * video_fifo = nullptr;
	//audios
	std::map<int32_t,fifo_stream_tt*> audio_fifos;
};



