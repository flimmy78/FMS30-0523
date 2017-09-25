#include "render_base.h"
#include "mc_file_render.h"
#include "mc_net_render.h"
#include "dt_net_render.h"

render_base::render_base()
{
}

render_base::~render_base()
{
}

bool render_base::init(std::string path, std::map<std::string, std::string>& ops)
{
	return true;
}

bufstream_tt * render_base::getrenderinbufstrm()
{
	return nullptr;
}

render_base * render_base::create(RENDER_TYPE rtype)
{
	switch (rtype)
	{
	case RENDER_MC_FILE:
		return new mc_file_render();
	case RENDER_MC_NET:
		return new mc_net_render();
	case RENDER_DT_NET:
		return new dt_net_render();
	}
	return nullptr;
}
