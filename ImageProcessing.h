
// ImageProcessing.h : main header file for the ImageProcessing application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <memory>

// CImageProcessingApp:
// See ImageProcessing.cpp for the implementation of this class
//

class CImageProcessingApp : public CWinAppEx
{
public:
	CImageProcessingApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	CImage img;
	int img_count;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageProcessingApp theApp;
