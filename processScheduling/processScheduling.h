
// processScheduling.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CprocessSchedulingApp: 
// �йش����ʵ�֣������ processScheduling.cpp
//

class CprocessSchedulingApp : public CWinApp
{
public:
	CprocessSchedulingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CprocessSchedulingApp theApp;