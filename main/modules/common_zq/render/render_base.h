#pragma once
#include <map>
#include "../bufstream/buf_fifo.h"
enum RENDER_TYPE
{
	RENDER_MC_FILE, //record file
	RENDER_MC_NET, //mainconcept
	RENDER_DT_NET, //Dektec
	RENDER_UNKNOWN
};

class render_base
{
public:
	render_base();
	virtual ~render_base();
	virtual bool init(std::string path, std::map<std::string, std::string>& ops);
	virtual bufstream_tt* getrenderinbufstrm();

public:
	static render_base* create(RENDER_TYPE rtype);
};