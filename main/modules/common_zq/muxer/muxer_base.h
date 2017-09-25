#pragma once
#include <map>
#include "../bufstream/buf_fifo.h"
enum MUXER_TYPE
{
	MUXER_MC_MPEG, //mpeg mux
	MUXER_MC_MXF, //mxf mux
	MUXER_MC_MP4, //mp4 mux
	MUXER_UNKNOWN
};

class muxer_base
{
public:
	muxer_base();
	virtual ~muxer_base();
	virtual bool init(std::map<std::string, std::string>& ops, bufstream_tt* bs);
	virtual void addvideostream();
	virtual void addaudiostream(int32_t index);
	virtual bufstream_tt* getaudiobufstrm(int32_t index);
	virtual bufstream_tt* getvideobufstrm();
public:
	static muxer_base* create(MUXER_TYPE mtype);
};