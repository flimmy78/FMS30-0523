#include "mc_file_render.h"
#include "../bufstream/buf_file.h"
#include <common/utf.h>
#include <common/log.h>

using namespace caspar;
mc_file_render::mc_file_render()
{
	filebs = nullptr;
}

mc_file_render::~mc_file_render()
{
 	if (filebs)
 	{
 		close_file_buf(filebs, 0);
 	}
}

bool mc_file_render::init(std::string path, std::map<std::string, std::string>& ops)
{
	filebs = open_file_buf_write(u16(path).c_str(), 1024 * 1024 * 100, nullptr);

	if (filebs == nullptr)
	{
		CASPAR_LOG(error) << "init mcfile render fail,path:" << path;
		return false;
	}
	return true;
}

 bufstream_tt * mc_file_render::getrenderinbufstrm()
 {
 	return filebs;
 }
