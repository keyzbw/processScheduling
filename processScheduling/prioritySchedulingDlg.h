#pragma once
#include "afxcmn.h"
#include "PCBPointer.h"

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
	// 时钟
	int clock;
	// CUP利用率
	CString cpuRate;
	// IO利用率
	CString ioRate;
	// 时钟速度
	double clockRate;
	//PCB队列指针
	PCBPointer* PP;
protected:
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
};
