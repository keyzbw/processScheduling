#pragma once
#include "afxcmn.h"


// prioritySchedulingDlg �Ի���

class prioritySchedulingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(prioritySchedulingDlg)

public:
	prioritySchedulingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~prioritySchedulingDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRIORITYSCHEDULINGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	// ִ�н����б�
	CListCtrl m_list1;
	virtual BOOL OnInitDialog();
	// ���н���
	CListCtrl m_list2;
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	// ��������
	CListCtrl m_list3;
	// ��������
	CListCtrl m_list4;
	afx_msg void OnEnChangeEdit3();
	// ��ɽ���
	CListCtrl m_list5;
};
