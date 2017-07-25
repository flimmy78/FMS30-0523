
// 20226MonitorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "sdl.h"
#include "C20226Service.h"



// CMy20226MonitorDlg dialog
class CMy20226MonitorDlg : public CDialogEx
{
// Construction
public:
	CMy20226MonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY20226MONITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_tv;

public:    //sdl
	SDL_Window         *m_sdl_window;
	SDL_Renderer       *m_sdl_renderer;
	SDL_Texture        *m_sdl_texture;
	SDL_AudioDeviceID  m_sdl_audio_dev;
	int                m_time_event;

public:    //socket
	C20226Service* m_service, *m_service_2;

public:     //gui
	CStatic m_text_addr;
	CStatic m_text_local;
	CStatic m_text_port;
	CStatic m_text_type;
	CStatic m_text_bitrate;
	int     m_drop;
	long long m_data_count;
	long long m_last_data_count;
	DWORD     m_first_time;
	DWORD     m_last_time;

public:   //configuration
	void         ReadConf();
	int          m_conf_pixel_w;
	int          m_conf_pixel_h;
	std::string  m_conf_localinterface;
	std::string  m_conf_udp_addr;
	std::string  m_conf_type;
	std::string  m_conf_udp_port_string;
	int          m_conf_udp_port;


public:
	afx_msg void OnDestroy();
	afx_msg void OnClickedTv();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_text_drop;

public:
	void deinterlace() {
		for (int i = 0; i < m_conf_pixel_h / 2 ; i++) {
			int pdst = (i * 2 ) * m_conf_pixel_w * 2;
			memcpy(m_render_video + pdst, m_sdi_video + i * m_conf_pixel_w * 2, m_conf_pixel_w * 2) ;
		}
		for (int i = m_conf_pixel_h / 2; i < m_conf_pixel_h; i++) {
			int base = i - m_conf_pixel_h / 2;
			int pdst = (base * 2 + 1) * m_conf_pixel_w * 2;
			memcpy(m_render_video + pdst, m_sdi_video + i * m_conf_pixel_w * 2, m_conf_pixel_w * 2);
		}

	}
	void swapuv()
	{
		for (int i = 0; i < m_conf_pixel_w * m_conf_pixel_h * 2; i += 4)
		{
			/*unsigned char u = m_sdi_video[i];
			m_sdi_video[i] = m_sdi_video[i+2];
			m_sdi_video[i+2] = u;
		*/	unsigned char u = m_render_video[i+1];
			m_render_video[i+1] = m_render_video[i+3];
			m_render_video[i+3] = u;

		}

	}
	unsigned char* m_sdi_video;      //interlace image
	unsigned char* m_render_video;   //deinterlace image for render


};
