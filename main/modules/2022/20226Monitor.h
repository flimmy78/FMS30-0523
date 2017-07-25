
// 20226Monitor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy20226MonitorApp:
// See 20226Monitor.cpp for the implementation of this class
//

class CMy20226MonitorApp : public CWinApp
{
public:
	CMy20226MonitorApp();
	~CMy20226MonitorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CMy20226MonitorApp theApp;
