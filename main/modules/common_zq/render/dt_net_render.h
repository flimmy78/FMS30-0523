#pragma once
#include "render_base.h"
#include <tbb/atomic.h>
#include <boost/thread.hpp>
#include <DTAPI.h>

#include <../../../common/timer.h>

#define CHECK_FIFO_INTERVAL         6000  //ms
#define PROTECT_PERIOD             (10*5)
#define COMPUTE_TIME			(60*3)         //s
#define ADJUST_TIME             (60*10)        //s

#define BYTES_BASED188          (188*8)     //bit

struct dt_net_render_params
{
	std::string   protocol;
	std::string   destip;
	int32_t       destport; 

	int32_t  devtype;
	int32_t  devport;
	int64_t  tsbitrate;
	int64_t  txmode;
	int32_t  delaytime;//1000 ms
	int32_t  ttl;
	int32_t  pkt_size;

	dt_net_render_params()
	{
		devtype = 2162;
		devport = 1;
		tsbitrate = 0;
		txmode = DTAPI_TXMODE_188;
		delaytime = 1000;
		ttl = 64;
		pkt_size = 1316;
	}
	void set_params(std::map<std::string, std::string>& ops)
	{
		auto it = ops.begin();
		while (it != ops.end())
		{
			if (it->first == "devtype")
			{
				devtype = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "devport")
			{
				devport = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "bitrate")
			{
				tsbitrate = atoi((it->second).c_str());
				tsbitrate = (tsbitrate / BYTES_BASED188)*BYTES_BASED188;
				it = ops.erase(it);
			}
			else if (it->first == "txmode")
			{
				txmode = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "delaytime")
			{
				delaytime = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "ttl")
			{
				ttl = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else if (it->first == "pkt_size")
			{
				pkt_size = atoi((it->second).c_str());
				it = ops.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
};

struct dt_net_render:public render_base
{
public:
	dt_net_render();
	virtual ~dt_net_render();
	virtual bool init(std::string path, std::map<std::string, std::string>& ops);
	virtual bufstream_tt* getrenderinbufstrm();

private:
	bool pathparse(std::string path, dt_net_render_params& netparams);
	bool init(dt_net_render_params dtparams);
	void pushstream();
	void senddata(uint8_t* pbuffer, int32_t nbufferLen);
private:
	fifo_stream_tt* net_fifo;
	tbb::atomic<bool>						  is_running_;
	boost::thread							  thread_;

	tbb::atomic<bool>						is_adjust_running_;
	boost::thread							adjust_thread_;
	void Adjust();
	void ResetTimer();
private:
	bool SetDektecType(int32_t devtype);
	bool SetDevOutPort(int32_t devport);
	bool SetTxControl(int32_t txcontrol);
	bool SetTxMode(int32_t txmode, int32_t stuffmode);
	bool SetIpPars(dt_net_render_params dtparams);
	bool SetTsRateBps(int32_t tsbitrate);
	bool SetFifoSize(int32_t delaytime, int32_t tsbitrate);
private:
	DtDevice m_dev;
	DtOutpChannel m_tsOutPort;
	DtIpPars m_ipPars;

	bool m_bStartSend;

	int32_t m_nCurLoad;
	int32_t m_nFifoSize;
	int32_t m_nTsBitRate;

	int64_t m_nComputeBitRate;
	int64_t m_nsendBytes;
	int64_t m_nlastSendBytes;
	int64_t m_nAdjustBitRate;
	caspar::timer         cptBitrate_timer_;
	caspar::timer         adjust_timer_;
	bool				  m_bCanAdjust;
	int                   m_fifoSizeAdded;
};
