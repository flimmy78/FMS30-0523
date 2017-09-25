#include "mc_net_render.h"
#include "../mc_common.h"
#include "../bufstream/mc_os_common.h"

#include <tools.h>
#include <parser_sdp.h>
#include <common/log.h>

mc_net_render::mc_net_render()
	:m_iFirstSystemTime(LLONG_MAX)
	, m_iLastSystemTime(LLONG_MAX)
	, m_i64NewSegmentTime(0)
	, m_pSender(nullptr)
	, net_fifo(nullptr)
{
}
mc_net_render::~mc_net_render()
{
	is_running_ = false;
	thread_.join();

	if (m_pSender)
	{
		m_pSender->Stop();
		m_pSender->Flush();
		delete m_pSender;
		m_pSender = nullptr;
	}
	if (net_fifo)
	{
		free_fifo_buf(net_fifo);
	}
}
bool mc_net_render::init(std::string path, std::map<std::string, std::string>& ops)
{
	bool bret = false;
	net_fifo = new_fifo_buf(16 * 1024 * 1024, 4 * 1024 * 1024);
	if (net_fifo == nullptr)
	{
		return false;
	}
	mc_net_render_params netparams;
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

bufstream_tt* mc_net_render::getrenderinbufstrm()
{
   if (net_fifo != nullptr)
   {
	   return &net_fifo->input;
   }
   return nullptr;
}

void mc_net_render::OnConfigChanged(void *pData, uint32_t *uiDataLen)
{

}
void mc_net_render::OnPacketSend(bool bMarker, uint32_t aBytesSent, int64_t i64TimeStamp, uint32_t uiSamplesCount)
{
	if (m_iFirstSystemTime == LLONG_MAX)
	{
		m_iFirstSystemTime = timeGetTime();
	}
	int32_t timeout = (int32_t)((i64TimeStamp / 10000LL) - (timeGetTime() - m_iFirstSystemTime));
	boost::this_thread::sleep_for(boost::chrono::milliseconds(timeout));
}

void mc_net_render::pushstream()
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

bool mc_net_render::pathparse(std::string path, mc_net_render_params& netparams)
{
	//eg. udp://236.0.0.2:10002
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

	netparams.ipAddr = path.substr(0, nIdx); //ipAddr
	path.erase(0, nIdx + 1);
	netparams.port = atoi(path.c_str()); //port
	return true;
}

bool mc_net_render::init(mc_net_render_params netparams)
{
	char* ipAddr = nullptr;
	char* localAddr = nullptr;
	if (!netparams.ipAddr.empty())
	{
		ipAddr = new char[netparams.ipAddr.length() + 1];
		strcpy(ipAddr, netparams.ipAddr.c_str());
	}

	if (!netparams.localAddr.empty())
	{
		localAddr = new char[netparams.localAddr.length() + 1];
		strcpy(localAddr, netparams.localAddr.c_str());
	}

	// Create streaming engine
	INetRendererEngine* pEngine = GetRtpRendererInterface(get_rc);

	// Create sender inctance
	SENDERINFO sSenderInfo;
	memset(&sSenderInfo, 0, sizeof(SENDERINFO));   // Clear fields
	if (0==netparams.protocol.compare("udp"))
	{
		sSenderInfo.aConnectionType = protocolUdp;        // Streaming protocol
	}
	sSenderInfo.aStreamType = isMPEG2TransportStream;          // Stream format accordingly RTP specs, use STREAMTYPE values
	sSenderInfo.mediaType = mediaVideo;     // Specified content format, ASF(wma, wmv) must be mediaApplication, MPEG multiplexed streams are mediaVideo
	sSenderInfo.uiSampleRate = 90000;        // Clock coefficient, samplerate for audio streams, for video use standart value 90000
											 //sSenderInfo.pDescriptor = pClockProvider;
											 //sSenderInfo.cbDescriptor = pClockProvider ? sizeof(pClockProvider) : 0;			
	m_pSender = pEngine->CreateSenderInstance(&sSenderInfo);
	m_pSender->SetDiscontinuity();

	//set nework params
	SENDERCONNECTIONPARAMS sSenderParams;
	memset(&sSenderParams, 0, sizeof(SENDERCONNECTIONPARAMS)); //ResetSenderConnectionParams(&senderparams); // Clear fields
	sSenderParams.aDstPort = netparams.port;             // Destination port, even value  
	sSenderParams.aSrcPort = 0;           // Local port, may be 0 to random port, or used from RTP tranport params
	sSenderParams.iMtu = 1500;                  // Maximum Transmission Unit, 1500 is default value for Ethernet networks
	if (0 == netparams.protocol.compare("udp"))
	{
		sSenderParams.iProtocol = IPPROTO_UDP;      // Transport layer protocol: IPPROTO_TCP or IPPROTO_UDP
	}
	sSenderParams.iTtl = netparams.ttl;                    // Time to live for packet, default for IP network is 64  
												//sSenderParams.pRtcpNotifier = m_pRtcp;
	sSenderParams.pSenderNotifier = this;
	sSenderParams.ucPayloadType = isMPEG2TransportStream;       // RTP payload type, use STREAMTYPE value to do not be confused                
	sSenderParams.bIsRawMode = true;           // Enable/disable RTP packing media data, may be true only for MPEG Multiplexed streams and not for RTP mode        
	sSenderParams.uiBurstnessValue = 0;         // Burstness value for each packet, time in millisecond to sleep on each packet
	sSenderParams.aNIC = localAddr;                  // Sender Local Network interface, or NULL for system default
	sSenderParams.aRemoteName = ipAddr;            // Destination address: client network address or multicast group
	NETRENDERERERRORS bret = m_pSender->Init(&sSenderParams);
	if (ipAddr)
	{
		delete[]ipAddr;
		ipAddr = nullptr;
	}
	if (localAddr)
	{
		delete[]localAddr;
		localAddr = nullptr;
	}
	if (bret != NwrOk)
	{
		CASPAR_LOG(error) << L"MCNetRender init error";
		return false;
	}
	return true;
}


void mc_net_render::senddata(uint8_t* pMediaData, uint32_t uiMediaDataLength)
{
	uint32_t uiSendedOffset = 0;           // Count of sended bytes 		 
										   // Use this flag to send last sample
	bool bForcedSend = true;// false;              // Flag forces sending immediately			 
	do {
		uint32_t uiConsumedBytes = 0;          // Count of consumed bytes in each iteration
		NETRENDERERERRORS err = m_pSender->SendPacket(pMediaData + uiSendedOffset, uiMediaDataLength - uiSendedOffset, &uiConsumedBytes, 0, bForcedSend);
		uiSendedOffset += uiConsumedBytes;     // Moved data pointer to unsended part
		switch (err)
		{
		case NwrOk:// Data chunk successful consumed
			break;
		case NwrNotEnoughData:
			// Data successfull consumed but not sended
			// Not enough data to fill network packet
			// Repeat sending with next data chunk from current media sample or start sending next sample
			break;
		case NwrDataChunkNotRecognized:
			// Data successfull consumed but not sended
			// Not enough to detect chunk boundaries
			// Repeat sending with next data chunk from current media sample or start sending next sample 
			break;
		case NwrWrongState:
			// Data is unexpected, engine not ready to send it
			break;
		default:
			// Sending error
			break;
		}
	} while (uiSendedOffset != uiMediaDataLength);

}
