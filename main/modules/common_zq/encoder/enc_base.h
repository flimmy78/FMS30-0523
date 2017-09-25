#pragma once
#include <map>
#include "../bufstream/buf_fifo.h"
enum ENC_TYPE
{
	ENC_MC_H264,
	ENC_MC_MPEG2,
	ENC_MC_MPA,
	ENC_MC_PCM,
	ENC_MC_AAC,
	ENC_MC_DDPP, //AC3
	ENC_UNKNOWN
};

class enc_base
{
public:
	enc_base();
	virtual ~enc_base();
	virtual bool init(std::map<std::string, std::string>& ops,bufstream_tt* bs);
	virtual bool encodevideo(uint8_t* src, uint32_t line_size, uint32_t fourcc);
	virtual bool encodeaudio(uint8_t* src, uint32_t nBytes);
public:
	static enc_base* createvideo(ENC_TYPE etype, int32_t width = 0, int32_t height = 0);
	static enc_base* createaudio(ENC_TYPE etype, int32_t samplerate, int32_t nchannels = 2);

};