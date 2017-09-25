#include "muxer_base.h"
#include "mc_mpeg_muxer.h"
muxer_base::muxer_base()
{
}

muxer_base::~muxer_base()
{
}

bool muxer_base::init(std::map<std::string, std::string>& ops, bufstream_tt* bs)
{
	return false;
}

void muxer_base::addvideostream()
{
}

void muxer_base::addaudiostream(int32_t index)
{
}

bufstream_tt * muxer_base::getaudiobufstrm(int32_t index)
{
	return nullptr;
}

bufstream_tt * muxer_base::getvideobufstrm()
{
	return nullptr;
}

muxer_base * muxer_base::create(MUXER_TYPE mtype)
{
	switch (mtype)
	{
	case MUXER_MC_MPEG:
		return new mc_mpeg_muxer();
	case MUXER_MC_MXF:
	case MUXER_MC_MP4:
		return nullptr;
	}
	return nullptr;
}
