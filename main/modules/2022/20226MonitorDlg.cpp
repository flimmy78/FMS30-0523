
// 20226MonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include <atomic>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "afxdialogex.h"
#include "Mmsystem.h"

#include "20226Monitor.h"
#include "20226MonitorDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMy20226MonitorDlg::CMy20226MonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY20226MONITOR_DIALOG, pParent)
	, m_drop(0), m_service(NULL), m_service_2(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy20226MonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_ADDR, m_text_addr);
	DDX_Control(pDX, IDC_TEXT_LOCAL, m_text_local);
	DDX_Control(pDX, IDC_TEXT_PORT, m_text_port);
	DDX_Control(pDX, IDC_TEXT_TYPE, m_text_type);
	DDX_Control(pDX, IDC_TV, m_tv);
	DDX_Control(pDX, IDC_TEXT_BITRATE, m_text_bitrate);
	DDX_Control(pDX, IDC_TEXT_DROP, m_text_drop);
}

BEGIN_MESSAGE_MAP(CMy20226MonitorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CMy20226MonitorDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMy20226MonitorDlg message handlers
void CMy20226MonitorDlg::ReadConf()
{
	boost::property_tree::ptree pt;
	try {
		boost::property_tree::read_xml("20226Monitor.xml", pt);
	}
	catch (...)
	{
		printf("No 20226Moniter.xml");
		return;
	}

	m_conf_pixel_w = 720;
	m_conf_pixel_h = 576;
	m_conf_type = pt.get<std::string>("conf.media.video", "SD");
	if (m_conf_type  == "HD")
	{
		m_conf_pixel_w = 1920;    m_conf_pixel_h = 1080;
	}


	m_conf_localinterface  = pt.get<std::string>("conf.network.localinterface", "");
	m_conf_udp_addr = pt.get<std::string>("conf.network.udp", "");
	m_conf_udp_port_string = pt.get<std::string>("conf.network.port", "");
	m_conf_udp_port = pt.get<int>("conf.network.port", 0);
	if (m_conf_localinterface.empty() | m_conf_udp_addr.empty() | m_conf_udp_port <= 0)
	{
		printf("No Network info");
		return;
	}

}


#define AUDIO_BUFFERSIZE  ( 1920 * 2)
unsigned char accAudio[AUDIO_BUFFERSIZE];
//This function is called when the audio device needs more data. 
//userdata: An application-specific parameter saved in the SDL_AudioSpec structure
//stream:   A pointer to the audio data buffer.
//len:      The length of that buffer in bytes.
//Once the callback returns, the buffer will no longer be valid.
//Stereo samples are stored in a LRLRLR ordering.
//You can choose to avoid callbacks and use SDL_QueueAudio() instead, if you like. Just open your audio device with a NULL callback.
void audio_callback(void*  userdata, Uint8* stream, int    len)
{
	C20226Service* p = ((CMy20226MonitorDlg*)userdata)->m_service;
	//OutputString("audio callback len = %d\n", len);
	p->GetAudio(accAudio, 1);
	SDL_memset(stream, 0, len);
	SDL_MixAudio(stream, accAudio, len/*AUDIO_BUFFERSIZE*/, SDL_MIX_MAXVOLUME);
}

void CALLBACK sdl_render(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	CMy20226MonitorDlg *p = (CMy20226MonitorDlg *)dwUser;
	SDL_Renderer       *sdlRenderer = p->m_sdl_renderer;
	SDL_Texture        *sdlTexture  = p->m_sdl_texture;
	SDL_AudioDeviceID   audio_dev   = p->m_sdl_audio_dev;
	int                 pixel_w     = p->m_conf_pixel_w;
	int                 pixel_h     = p->m_conf_pixel_h;
	unsigned char*      psdi        = p->m_sdi_video;;
	unsigned char*      pvideo      = p->m_render_video;;
	CRect rect;
	SDL_Rect sdlRect;
	p->GetWindowRect(&rect);
	sdlRect.x = 0;	sdlRect.y = 0;	sdlRect.w = rect.Width();	sdlRect.h = rect.Height();
	
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdlRenderer);

	{
		p->m_service->GetVideo(psdi);
		p->deinterlace();
		//p->swapuv();
		SDL_UpdateTexture(sdlTexture, NULL, pvideo, pixel_w * 2);
		SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);   // &sdlRect);
	}
	{
	//	memset(accAudio, 0, AUDIO_BUFFERSIZE);
	//	p->m_service->GetAudio(accAudio, 1);
	//	SDL_QueueAudio(audio_dev, accAudio, AUDIO_BUFFERSIZE);
	}
	SDL_RenderPresent(sdlRenderer);
	static int i = 0;
	if (++i % 10 == 0)
		p->SendMessage(WM_TIMER, 0, 0);   //SetTimer可能发不出WM_TIMER消息
}

void receive_video(void* p, int size, void* caller)
{
	OutputString("callback v  " );
}

void receive_audio(void* p, int size, void* caller)
{
	OutputString("callback a  \n");
}

BOOL CMy20226MonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically 
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return FALSE;
	}


	ReadConf();
	int vSize = m_conf_pixel_w * m_conf_pixel_h * 2;
	m_render_video = new unsigned char[vSize];
	memset(m_render_video, 0x80, vSize);
	m_sdi_video = new unsigned char[vSize];
	memset(m_sdi_video, 0x80, vSize);

	
	m_service = new C20226Service(m_conf_localinterface, m_conf_udp_addr, m_conf_udp_port, (m_conf_pixel_w <= 720) ? PAL : PAL1080);

	//m_service_2 = new C20226Service(m_conf_localinterface, m_conf_udp_addr, m_conf_udp_port, (m_conf_pixel_w <= 720) ? PAL : PAL1080);

	if (m_service <= 0) return FALSE;
	m_service->SetVideoNotify(receive_video, (void*)this);
	m_service->SetAudioNotify(receive_audio, (void*)this);

	//Video
	try {
		m_sdl_window = SDL_CreateWindowFrom(m_tv.GetSafeHwnd());
		if (m_sdl_window == NULL) {
			SDL_Delay(300);
			SDL_Quit();
			return FALSE;
		}
	}
	catch (...)
	{

	}
	m_sdl_renderer = SDL_CreateRenderer(m_sdl_window, -1, 0);
	Uint32 pixformat = SDL_PIXELFORMAT_UYVY;   //!@#$  // SDL_PIXELFORMAT_YUY2;   // SDL_PIXELFORMAT_UYVY;   // SDL_PIXELFORMAT_YVYU;   // SDL_PIXELFORMAT_YVYU;   //SDL_PIXELFORMAT_BGRA8888;   // SDL_PIXELFORMAT_YVYU;  // SDL_PIXELFORMAT_YUY2;  // SDL_PIXELFORMAT_UYVY;//SDL_PIXELFORMAT_BGRA8888;  // SDL_PIXELFORMAT_IYUV;  //SDL_PIXELFORMAT_UYVY;
	m_sdl_texture = SDL_CreateTexture(m_sdl_renderer, pixformat, SDL_TEXTUREACCESS_STREAMING, m_conf_pixel_w, m_conf_pixel_h);

	//Audio
	SDL_AudioSpec want;
	SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
	want.freq = 48000;
	want.format = AUDIO_S16LSB;   // AUDIO_S16LSB;   // AUDIO_S16LSB;    //AUDIO_F32;
	want.channels = 1;
	want.samples = AUDIO_SAMPLES_PER_FRAME_CHANNEL;  //can be other value(no power 2)
	want.callback = audio_callback;   // NULL;
	want.userdata = (void*)this;
	m_sdl_audio_dev = SDL_OpenAudio(&want, NULL);
	SDL_PauseAudio(0);

	m_text_local.SetWindowTextA(m_conf_localinterface.data());
	m_text_addr.SetWindowTextA(m_conf_udp_addr.data());
	m_text_port.SetWindowTextA(m_conf_udp_port_string.data());
	m_text_type.SetWindowTextA(("as " + m_conf_type).data());

	m_last_data_count = 0;
	m_first_time = timeGetTime();
	m_last_time  = m_first_time;

	m_time_event = timeSetEvent(40, 1, sdl_render, (DWORD)this, TIME_PERIODIC);
	
	if (m_service <= 0) return FALSE;
	m_service->Run();

	if (m_service_2)
		m_service_2->Run();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy20226MonitorDlg::OnPaint()
{
	if (IsIconic())
	{
	}
	else
	{
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy20226MonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy20226MonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	DWORD now   = timeGetTime();
	long long c = m_service->GetDataCount() - m_last_data_count;
	DWORD interval = now - m_last_time;
	if (interval == 0) interval = 1;
	int br = (c / interval ) * 8 / 1000;   //kbps
	m_last_data_count = m_service->GetDataCount();
	m_last_time = now;

	std::stringstream ss;
	std::string str;
	ss << br;
	ss >> str;
	m_text_bitrate.SetWindowTextA(str.data());
	
	int frames = (now - m_first_time) / 40;
	ss.clear();  // .str("");
	br = frames - m_service->GetDecodeCount();
	ss << br;
	ss >> str;
	m_text_drop.SetWindowTextA(str.data());

	CDialogEx::OnTimer(nIDEvent);
}


void CMy20226MonitorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	timeKillEvent(m_time_event);

	SDL_Delay(200);  // let the audio callback play some sound for 1 second.
	SDL_CloseAudio();
	SDL_DestroyRenderer(m_sdl_renderer);
	SDL_DestroyTexture(m_sdl_texture);
	SDL_Quit();

	
	if (m_service != NULL)
	{
		m_service->Stop();
		delete m_service;
		m_service = NULL;
	}

	/*if (m_service_2 != NULL)
	{
		m_service_2->Stop();
		delete m_service_2;
		m_service = NULL;
	}*/

	
	if (m_render_video != NULL)     delete []m_render_video;
	if (m_sdi_video != NULL)        delete []m_sdi_video;
}


void CMy20226MonitorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

