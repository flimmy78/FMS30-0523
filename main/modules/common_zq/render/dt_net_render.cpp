#include "dt_net_render.h"
#include <common/log.h>

dt_net_render::dt_net_render()
	:m_bStartSend(false)
	, m_nCurLoad(0)
	, net_fifo(nullptr)
{
	m_nComputeBitRate = 0;
	m_nsendBytes = 0;
	m_nlastSendBytes = 0;
	m_nAdjustBitRate = 0;
	m_bCanAdjust = false;
}

dt_net_render::~dt_net_render()
{
	is_adjust_running_ = false;
	adjust_thread_.join();

	is_running_ = false;
	thread_.join();
	if (net_fifo)
	{
		free_fifo_buf(net_fifo);
	}
	m_tsOutPort.SetTxControl(DTAPI_TXCTRL_IDLE);
	m_tsOutPort.Detach(DTAPI_INSTANT_DETACH);
	m_dev.Detach();
}

bool dt_net_render::init(std::string path, std::map<std::string, std::string>& ops)
{
	bool bret = false;
	net_fifo = new_fifo_buf(16 * 1024 * 1024, 4 * 1024 * 1024);
	if (net_fifo == nullptr)
	{
		return false;
	}
	dt_net_render_params netparams;
	netparams.set_params(ops);
	bret = pathparse(path, netparams);
	if (bret == false)
	{
		return false;
	}

	bret = init(netparams);
	if (bret == false)
	{
		return false;
	}

	//pushstream
	is_running_ = true;
	thread_ = boost::thread([this] {pushstream(); });
	return true;
}

bufstream_tt * dt_net_render::getrenderinbufstrm()
{
	if (net_fifo != nullptr)
	{
		return &net_fifo->input;
	}
	return nullptr;
}
void dt_net_render::pushstream()
{
	while (is_running_)
	{
		uint32_t uiMediaDataLength = net_fifo->output.usable_bytes(&net_fifo->output);
		if (uiMediaDataLength > 0/* 1500*/)
		{
			uint8_t* pMediaData = (uint8_t*)malloc(uiMediaDataLength);
			net_fifo->output.copybytes(&net_fifo->output, pMediaData, uiMediaDataLength);
			senddata(pMediaData, uiMediaDataLength);
			free(pMediaData);
			pMediaData = nullptr;
		}
		else
		{
			boost::this_thread::sleep_for(boost::chrono::milliseconds(2));
		}
	}
}

bool dt_net_render::pathparse(std::string path, dt_net_render_params& netparams)
{
    int32_t nIdx = static_cast<int32_t>(path.find(':'));
	if (nIdx < 0)
	{
		CASPAR_LOG(error) << L"Invalid path: " << path;
		return false;
	}
	std::string protocolstr = path.substr(0, nIdx + 3);
	if (protocolstr.compare("udp://"))
	{
		CASPAR_LOG(error) << L"Invalid path: " << path;
		return false;
	}
	netparams.protocol = path.substr(0, nIdx); //protocol

	path.erase(0, nIdx + 3);
	nIdx = static_cast<int32_t>(path.find(':'));
	if (nIdx < 0)
	{
		CASPAR_LOG(error) << L"Invalid path: " << path;
		return false;
	}

	netparams.destip = path.substr(0, nIdx); //ipAddr
	path.erase(0, nIdx + 1);
	netparams.destport = atoi(path.c_str()); //port
	return true;
}

bool dt_net_render::init(dt_net_render_params dtparams)
{
	bool bret = false;
	bret = SetDektecType(dtparams.devtype);
	if (!bret)
	{
		return bret;
	}

	bret = SetDevOutPort(dtparams.devport);
	if (!bret)
	{
		return bret;
	}

	bret = SetTxControl(DTAPI_TXCTRL_IDLE);
	if (!bret)
	{
		return bret;
	}

	bret = SetTxMode(static_cast<int32_t>(dtparams.txmode), static_cast<int32_t>(DTAPI_TXSTUFF_MODE_ON));
	if (!bret)
	{
		return bret;
	}

	bret = SetIpPars(dtparams);
	if (!bret)
	{
		return bret;
	}

	bret = SetTsRateBps(dtparams.tsbitrate);
	if (!bret)
	{
		return bret;
	}

	m_nTsBitRate = dtparams.tsbitrate;

	m_tsOutPort.ClearFifo();          // Clear FIFO (i.e. start with zero load)

	bret = SetFifoSize(dtparams.delaytime, dtparams.tsbitrate);
	if (!bret)
	{
		return bret;
	}

	bret = SetTxControl(DTAPI_TXCTRL_HOLD);
	if (!bret)
	{
		return bret;
	}
	is_adjust_running_ = true;
	adjust_thread_ = boost::thread([this] {Adjust(); }); //码率调整
	return true;
}

void dt_net_render::senddata(uint8_t* pbuffer, int32_t nbufferLen)
{
	DTAPI_RESULT dr;
	if (!m_bStartSend)
	{
		if (m_nCurLoad < m_nFifoSize)
		{
			dr = m_tsOutPort.Write((char*)pbuffer, nbufferLen);
			if (dr != DTAPI_OK)
			{
				CASPAR_LOG(error) << L"Write failed, ERROR:" << DtapiResult2Str(dr);
				return;
			}
			m_nCurLoad += nbufferLen;
			return;
		}
		else
		{
			m_bStartSend = true;
			dr = m_tsOutPort.SetTxControl(DTAPI_TXCTRL_SEND);	// Start transmission
			if (dr != DTAPI_OK)
			{
				CASPAR_LOG(error) << L"SetTxControl failed,ERROR:" << DtapiResult2Str(dr);
			}
			cptBitrate_timer_.restart();
			adjust_timer_.restart();
		}
	}

	//判断当前缓存
	int nFifoLoad = 0;
	m_tsOutPort.GetFifoLoad(nFifoLoad);
	while ((nFifoLoad + nbufferLen) >= (m_nFifoSize + FIFOSIZE_OFFSET / 2))
	{
		boost::this_thread::sleep_for(boost::chrono::milliseconds(40));
		CASPAR_LOG(info) << L"Wait for  nFifoLoad have space current nFifoLoad " << nFifoLoad;
		m_tsOutPort.GetFifoLoad(nFifoLoad);		
	}

	dr = m_tsOutPort.Write((char*)pbuffer, nbufferLen);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"Write failed, ERROR:" << DtapiResult2Str(dr);
	}

	m_nsendBytes += nbufferLen;

	if (cptBitrate_timer_.elapsed() >= COMPUTE_TIME)
	{
		m_nAdjustBitRate = (m_nsendBytes - m_nlastSendBytes) * 8 / cptBitrate_timer_.elapsed();
		CASPAR_LOG(debug) << L"COMPUTE_TIME  " << COMPUTE_TIME << L" Computebitrate  " << m_nAdjustBitRate;
		m_nlastSendBytes = m_nsendBytes;
		cptBitrate_timer_.restart();
	}

	if (adjust_timer_.elapsed() >= ADJUST_TIME)
	{
		m_nAdjustBitRate = m_nsendBytes * 8 / adjust_timer_.elapsed();
		ResetTimer();
		m_bCanAdjust = true;
		CASPAR_LOG(debug) << L"ADJUST_TIME  " << ADJUST_TIME << L" Computebitrate  " << m_nAdjustBitRate;
	}
}

void dt_net_render::Adjust()
{
	int nFifoLoad = 0;
	int nFifoSize = 0;
	int nTsRate = 0;
	int64_t adjustSafetyPeriod = 0;
	while (is_adjust_running_)
	{
		if (m_bStartSend)
		{
			m_tsOutPort.GetFifoLoad(nFifoLoad);
			m_tsOutPort.GetFifoSize(nFifoSize);
			m_tsOutPort.GetTsRateBps(nTsRate);

			if (m_nAdjustBitRate == 0 || m_nAdjustBitRate > m_nTsBitRate)
				m_nAdjustBitRate = m_nTsBitRate;
			adjustSafetyPeriod++;
			if (nFifoLoad >= m_nFifoSize)
			{
				if (nFifoLoad >= (m_nFifoSize+FIFOSIZE_OFFSET/4))
				{
					m_tsOutPort.SetTsRateBps(m_nTsBitRate);
					CASPAR_LOG(debug) << L"adjust up : " << m_nTsBitRate;
					CASPAR_LOG(debug) << L"After adjust GetFifoLoad: " << nFifoLoad;
				}
				else
				{
					//码流太小
					int bitrate = (m_nTsBitRate + m_nAdjustBitRate) / 2;
					if (bitrate <= nTsRate)
						bitrate = nTsRate + nTsRate*0.0001;
					if (adjustSafetyPeriod > PROTECT_PERIOD)
					{
						bitrate = bitrate <= m_nTsBitRate ? bitrate : m_nTsBitRate;
						nTsRate = bitrate;
						m_tsOutPort.SetTsRateBps(bitrate);
						adjustSafetyPeriod = 0;
						ResetTimer();
						m_bCanAdjust = false;
						CASPAR_LOG(debug) << L"adjust up : " << bitrate;
						CASPAR_LOG(debug) << L"After adjust GetFifoLoad: " << nFifoLoad;
					}
				}
			}else if (nFifoLoad < m_nFifoSize*0.7)
			{
				//码流过大
				int bitrate = (nTsRate + m_nAdjustBitRate) / 2;
				if (bitrate >= nTsRate)
					bitrate = nTsRate*0.9999;
				if (adjustSafetyPeriod > PROTECT_PERIOD)
				{
					nTsRate = bitrate;
					m_tsOutPort.SetTsRateBps(bitrate);
					adjustSafetyPeriod = 0;
					ResetTimer();
					m_bCanAdjust = false;
					CASPAR_LOG(debug) << L"adjust down : " << bitrate;
					CASPAR_LOG(debug) << L"After adjust GetFifoLoad: " << nFifoLoad;
				}
			}
			
			//一般情况下的调整
			if (m_bCanAdjust)
			{				
				int bitrate = (nTsRate + m_nAdjustBitRate) / 2;
				nTsRate = bitrate;
				m_tsOutPort.SetTsRateBps(bitrate);
				m_bCanAdjust = false;
				CASPAR_LOG(debug) << L" After adjust GetFifoLoad: " << nFifoLoad;
			}

			CASPAR_LOG(debug) << L"GetTsRateBps:  " << nTsRate << L" GetFifoLoad: " << nFifoLoad << L" m_nAdjustBitRate: " << m_nAdjustBitRate;
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(CHECK_FIFO_INTERVAL));
	}
}


void dt_net_render::ResetTimer()
{
	adjust_timer_.restart();
	cptBitrate_timer_.restart();
	m_nsendBytes = 0;
	m_nlastSendBytes = 0;
}

bool dt_net_render::SetDektecType(int32_t devtype)
{
	DTAPI_RESULT dr;
	m_dev.Detach();
	dr = m_dev.AttachToType(devtype);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"Failed to attach to the DTA-" << devtype << L", ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}
bool dt_net_render::SetDevOutPort(int32_t devport)
{
	DTAPI_RESULT dr;
	m_tsOutPort.Detach(DTAPI_INSTANT_DETACH);
	dr = m_tsOutPort.AttachToPort(&m_dev, devport);
	if (dr != DTAPI_OK && dr != DTAPI_OK_FAILSAFE)
	{
		CASPAR_LOG(error) << L"Can't attach to the channel " << devport << L", ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}

bool dt_net_render::SetTxControl(int32_t txcontrol)
{
	DTAPI_RESULT dr;
	dr = m_tsOutPort.SetTxControl(txcontrol);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"SetTxControl failed, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}

bool dt_net_render::SetTxMode(int32_t txmode, int32_t stuffmode)
{
	DTAPI_RESULT dr;
	dr = m_tsOutPort.SetTxMode(txmode, stuffmode);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"SetTxMode failed, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}

bool dt_net_render::SetIpPars(dt_net_render_params dtparams)
{
	DTAPI_RESULT dr;
	DtapiInitDtIpParsFromIpString(m_ipPars, dtparams.destip.c_str(), NULL);
	m_ipPars.m_Port = static_cast<unsigned short>(dtparams.destport);
	if (0 == dtparams.protocol.compare("udp"))
	{
		m_ipPars.m_Protocol = DTAPI_PROTO_UDP;
	}
	m_ipPars.m_TimeToLive = dtparams.ttl;//64;
	switch (dtparams.txmode)
	{
	case DTAPI_TXMODE_188:
		m_ipPars.m_NumTpPerIp = dtparams.pkt_size / 188;
		break;
	default:
		m_ipPars.m_NumTpPerIp = 7;
		break;
	}
	m_ipPars.m_Flags = DTAPI_IP_V4;
	dr = m_tsOutPort.SetIpPars(&m_ipPars);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"SetIpPars failed, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}


bool dt_net_render::SetTsRateBps(int32_t tsbitrate)
{
	DTAPI_RESULT dr;
	dr = m_tsOutPort.SetTsRateBps(tsbitrate);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"SetTsrateBps failed, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}

bool dt_net_render::SetFifoSize(int32_t delaytime, int32_t tsbitrate)
{
	DTAPI_RESULT dr;
	m_nFifoSize = static_cast<int32_t>(double(delaytime) / 1000 * tsbitrate / 8);
	int maxFifosize;
	m_tsOutPort.GetMaxFifoSize(maxFifosize);
	if (maxFifosize < (m_nFifoSize + FIFOSIZE_OFFSET))
		m_nFifoSize = maxFifosize - FIFOSIZE_OFFSET;

	m_nFifoSize = static_cast<int32_t>(m_nFifoSize+FIFOSIZE_OFFSET);
	m_nFifoSize = m_nFifoSize / 16 * 16; //16的倍数
	dr = m_tsOutPort.SetFifoSize(m_nFifoSize);
	m_nFifoSize -= FIFOSIZE_OFFSET;                   //我们要缓存的字节数
	CASPAR_LOG(info) << L"SetFifoSize : " << m_nFifoSize;
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"Failed to set Fifo size, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}
