#include "mc_mpeg_muxer.h"
#include "../mc_common.h"
#include <common/log.h>

mc_mpeg_muxer_params::mc_mpeg_muxer_params()
{
	enabled_paddings = 0;
	required_bitrate = 0;
	PCR_repetition_rate = 30;
	PSI_repetition_rate = 100;
	v_delay = 0;
	a_delay = 0;
	video_pid = 1001;
}

mc_mpeg_muxer_params::~mc_mpeg_muxer_params()
{
	audio_pids.clear();
}

void mc_mpeg_muxer_params::set_params(std::map<std::string, std::string>& ops)
{
	auto it = ops.begin();
	while (it != ops.end())
	{
		if (it->first == "enpaddings")//enablepaddings
		{
			enabled_paddings = atol((it->second).c_str());
			it = ops.erase(it);
		}
		else if (it->first == "rbitrate")//requiredbitrate
		{
			required_bitrate = atol((it->second).c_str());
			it = ops.erase(it);
		}
		else if (it->first == "pcr")//pcrinterval
		{
			PCR_repetition_rate = atol((it->second).c_str());
			it = ops.erase(it);
		}
		else if (it->first == "psi")//psiinterval
		{
			PSI_repetition_rate = atol((it->second).c_str());
			it = ops.erase(it);
		}
		else if (it->first == "vdelay")//video delay ms
		{
			v_delay = atol((it->second).c_str());
			it = ops.erase(it);
		}
		else if (it->first == "adelay")//audio delay ms
		{
			a_delay = atol((it->second).c_str());
			it = ops.erase(it);
		}
		else if (it->first == "vpid")//videopid
		{
			video_pid = atol((it->second).c_str());
			it = ops.erase(it);
		}
		else if (it->first == "apids")//audiopids 以逗号分隔 eg:301,302,303
		{
			std::string apids = it->second;
			split_apids(apids, ",");
			it = ops.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void mc_mpeg_muxer_params::split_apids(std::string apids, std::string pattern)
{
	apids += pattern;
	std::string::size_type pos;
	int32_t size = apids.size();
	int32_t index = 0;
	for (int i = 0; i < size; i++)
	{
		pos = apids.find(pattern, i);
		if (pos < size)
		{
			std::string apid = apids.substr(i, pos - i);
			audio_pids[index++] = atol(apid.c_str());
			i = pos + pattern.size() - 1;
		}
	}
}

int32_t mc_mpeg_muxer_params::get_apid(int32_t index)
{
	std::map<int32_t, int32_t>::iterator iter = audio_pids.find(index);
	if (iter != audio_pids.end())
	{
		return iter->second;
	}
	return 0;
}

/////////////////////////////////////////////////////////

mc_mpeg_muxer::mc_mpeg_muxer()
{
}

mc_mpeg_muxer::~mc_mpeg_muxer()
{
	if (mp2muxer)
	{
		mpegOutMP2MuxDone(mp2muxer, 0);
		mpegOutMP2MuxFree(mp2muxer);
	}
	if (video_fifo)
	{
		free_fifo_buf(video_fifo);
	}

	for (std::map<int32_t,fifo_stream_tt*>::iterator iter = audio_fifos.begin();iter != audio_fifos.end();iter++)
	{
		fifo_stream_tt* audiofifo = iter->second;
		if (audiofifo)
		{
			free_fifo_buf(audiofifo);
		}
	}
	audio_fifos.clear();
}

bool mc_mpeg_muxer::init(std::map<std::string, std::string>& ops, bufstream_tt * bs)
{
	mux_params_.set_params(ops);//复用器参数
	mp2muxer_set_struct muxer_settings;
	mp2mux_ext_set_struct ext_muxer_settings;

	memset(&muxer_settings, 0, sizeof(muxer_settings));
	memset(&ext_muxer_settings, 0, sizeof(ext_muxer_settings));

	mpegOutMP2MuxDefaults(&muxer_settings, MPEG_TS);
	muxer_settings.VBR_multiplex = !mux_params_.enabled_paddings;
	if (muxer_settings.VBR_multiplex == 0) //constant bitrate
	{
		if (mux_params_.required_bitrate == 0)
		{
			CASPAR_LOG(error) << L"mpegOutMP2Mux must specifies required bitrate.";
			return false;
		}
		else
		{
			muxer_settings.user_mux_rate_bps = mux_params_.required_bitrate;
		}
	}
	muxer_settings.frame_timestamps = TIMESTAMPS_ALL;
	mp2muxer = mpegOutMP2MuxNew(get_rc, &muxer_settings);
	if (!mp2muxer)
	{
		CASPAR_LOG(error) << L"mpegOutMP2MuxNew failed.";
		return false;
	}

	ext_muxer_settings.PCR_LIMIT = mux_params_.PCR_repetition_rate;
	ext_muxer_settings.PSI_LIMIT = mux_params_.PSI_repetition_rate;
	if (mpegOutMP2MuxInitStream(mp2muxer, &ext_muxer_settings, bs) != MUX_OK)
	{
			CASPAR_LOG(error) << L"mpegOutMP2MuxInitStream failed.";
			mpegOutMP2MuxFree(mp2muxer);
			return false;
	}

	return true;
}

void mc_mpeg_muxer::addvideostream()
{
	mp2mux_stream_set_struct stream_settings;
	memset(&stream_settings, 0, sizeof(stream_settings));
 	stream_settings.flags = STREAM_FLAG_VIDEO_STREAM;
 	//stream_settings.align_in_flag = 1;
	stream_settings.delay_ms = mux_params_.v_delay;
 	if (mux_params_.video_pid != 0) stream_settings.PID = mux_params_.video_pid;
	video_fifo = new_fifo_buf(16 * 1024 * 1024, 4 * 1024 * 1024);
 	if (mpegOutMP2MuxAddStream(mp2muxer, &stream_settings, &(video_fifo->output)) != MUX_OK)
 	{
 	 	CASPAR_LOG(error) << L"mpegOutMP2MuxAddStream video failed.";
 	 	mpegOutMP2MuxFree(mp2muxer);
 	 	return;
 	}
}

void mc_mpeg_muxer::addaudiostream(int32_t index)
{
	mp2mux_stream_set_struct stream_settings;
	memset(&stream_settings, 0, sizeof(stream_settings));
	stream_settings.flags = STREAM_FLAG_AUDIO_STREAM;
	stream_settings.delay_ms = mux_params_.a_delay;

	int32_t apid = mux_params_.get_apid(index);
	if (0 != apid) stream_settings.PID = apid;
	
	fifo_stream_tt* audiofifo = new_fifo_buf(1024 * 1024, 4096 + 1);
	audio_fifos[index] = audiofifo;
	if (mpegOutMP2MuxAddStream(mp2muxer, &stream_settings, &(audiofifo->output)) != MUX_OK)
	{
	 	CASPAR_LOG(error) << L"mpegOutMP2MuxAddStream audio failed.";
	 	mpegOutMP2MuxFree(mp2muxer);
	 	return;
	}
}

bufstream_tt * mc_mpeg_muxer::getaudiobufstrm(int32_t index)
{
	std::map<int32_t, fifo_stream_tt*>::iterator iter = audio_fifos.find(index);
	if (iter != audio_fifos.end())
	{
		return &iter->second->input;
	}
	return nullptr;
}

bufstream_tt * mc_mpeg_muxer::getvideobufstrm()
{
	return &video_fifo->input;
}

