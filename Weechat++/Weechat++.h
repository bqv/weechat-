
// Weechat++.h : main header file for the Weechat++ application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CWeechatApp:
// See Weechat++.cpp for the implementation of this class
//

class CWeechatApp : public CWinApp
{
public:
	CWeechatApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWeechatApp theApp;
