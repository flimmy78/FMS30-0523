#pragma once
#include "render_base.h"

struct mc_file_render :public render_base
{
public:
	mc_file_render();
	virtual ~mc_file_render();
	virtual bool init(std::string path, std::map<std::string, std::string>& ops);
	virtual bufstream_tt* getrenderinbufstrm();
private:
	bufstream_tt* filebs;
};