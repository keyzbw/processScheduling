#pragma once
#include "afxcmn.h"


// prioritySchedulingDlg 对话框

class prioritySchedulingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(prioritySchedulingDlg)

public:
	prioritySchedulingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~prioritySchedulingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRIORITYSCHEDULINGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	// 执行进程列表
	CListCtrl m_list1;
	virtual BOOL OnInitDialog();
	// 运行进程
	CListCtrl m_list2;
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	// 就绪进程
	CListCtrl m_list3;
	// 阻塞进程
	CListCtrl m_list4;
	afx_msg void OnEnChangeEdit3();
	// 完成进程
	CListCtrl m_list5;
};
