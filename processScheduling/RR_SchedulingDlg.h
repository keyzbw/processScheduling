#pragma once
#include "afxcmn.h"


// RR_SchedulingDlg �Ի���

class RR_SchedulingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RR_SchedulingDlg)

public:
	RR_SchedulingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RR_SchedulingDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RRSCHEDULINGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �б�ͷ
	CListCtrl m_list1;
	// ִ���б�
	CListCtrl m_list2;
	// �����б�
	CListCtrl m_list3;
	virtual BOOL OnInitDialog();
	// ��������
	CListCtrl m_list4;
	// ��ɽ���
	CListCtrl m_list5;
};
