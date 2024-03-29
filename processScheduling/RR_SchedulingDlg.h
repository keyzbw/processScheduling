#pragma once
#include "afxcmn.h"


// RR_SchedulingDlg 对话框

class RR_SchedulingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RR_SchedulingDlg)

public:
	RR_SchedulingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RR_SchedulingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RRSCHEDULINGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 列表头
	CListCtrl m_list1;
	// 执行列表
	CListCtrl m_list2;
	// 就绪列表
	CListCtrl m_list3;
	virtual BOOL OnInitDialog();
	// 阻塞进程
	CListCtrl m_list4;
	// 完成进程
	CListCtrl m_list5;
	// 时钟
	int clock;
	// CPU利用率
	CString cupRate;
	// io利用率
	CString ioRate;
	// 时间片
	int timeSlice;
	// 时钟速率
	double clockRate;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};
