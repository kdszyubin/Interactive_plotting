
// Interactive_plotting.h : Interactive_plotting Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CInteractive_plottingApp:
// �йش����ʵ�֣������ Interactive_plotting.cpp
//

class CInteractive_plottingApp : public CWinApp
{
public:
	CInteractive_plottingApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CInteractive_plottingApp theApp;
