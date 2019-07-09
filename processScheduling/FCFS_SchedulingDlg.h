#pragma once
#include "afxcmn.h"
#include "PCBPointer.h"

// FCFS_SchedulingDlg 对话框

class FCFS_SchedulingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FCFS_SchedulingDlg)

public:
	FCFS_SchedulingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FCFS_SchedulingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FCFSSCHEDULINGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 列表头
	CListCtrl m_list1;
	// //执行进程
	CListCtrl m_list2;
	// 就绪进程列表
	CListCtrl m_list3;
	// 阻塞进程列表
	CListCtrl m_list4;
	// 完成进程
	CListCtrl m_list5;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	// 时钟
	int clock;
	// cpu利用率
	CString cpuRate;
	// IOA利用率
	CString ioaRate;
	// 时钟速度
	double clockRate;
	//进程控制块列表
	PCBPointer* PP;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	// IOBRate
	CString iobRate;
};
