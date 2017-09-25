#pragma once
#include "render_base.h"
#include <net_renderer.h>
#include <tbb/atomic.h>
#include <boost/thread.hpp>

using namespace MainConcept::NetworkStreaming;

struct mc_net_render_params
{
	std::string protocol;
	std::string ipAddr;
	int32_t port;
	std::string localAddr;
	int32_t ttl;
	mc_net_render_params()
	{
		protocol = "";
		ipAddr = "";
		localAddr = "";
		ttl = 64;
	}
	void set_params(std::map<std::string, std::string>& ops)
	{
		auto it = ops.begin();
		while (it != ops.end())
		{
			if (it->first == "localaddr")
			{
				localAddr = it->second;
				it = ops.erase(it);
			}
			else if (it->first == "ttl")
			{
				ttl = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
};
struct mc_net_render : public ISenderNotifier,public render_base
{
public:
	mc_net_render();
	virtual ~mc_net_render();
	virtual bool init(std::string path, std::map<std::string, std::string>& ops);
	virtual bufstream_tt* getrenderinbufstrm();
private:
	bool pathparse(std::string path, mc_net_render_params& netparams);
	bool init(mc_net_render_params netparams);	
	void pushstream();
	void senddata(uint8_t* pMediaData, uint32_t uiMediaDataLength);

public:
	virtual void OnConfigChanged(void *pData, uint32_t *uiDataLen);
	virtual void OnPacketSend(bool bMarker, uint32_t aBytesSent, int64_t i64TimeStamp, uint32_t uiSamplesCount);

private:
	int64_t m_iFirstSystemTime;
	int64_t m_iLastSystemTime;
	int64_t m_i64NewSegmentTime;
	IBaseSender* m_pSender;

	fifo_stream_tt* net_fifo;
	tbb::atomic<bool>						  is_running_;
	boost::thread							  thread_;
};
