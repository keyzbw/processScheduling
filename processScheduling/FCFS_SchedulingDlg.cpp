// FCFS_SchedulingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "processScheduling.h"
#include "FCFS_SchedulingDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "PCB.h"
#include "schedulingService.h"
// FCFS_SchedulingDlg 对话框

IMPLEMENT_DYNAMIC(FCFS_SchedulingDlg, CDialogEx)

FCFS_SchedulingDlg::FCFS_SchedulingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FCFSSCHEDULINGDLG, pParent)
	, clock(0)
	, cpuRate(_T(""))
	, ioRate(_T(""))
	, clockRate(1)
{

}

FCFS_SchedulingDlg::~FCFS_SchedulingDlg()
{
}

void FCFS_SchedulingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list1);
	DDX_Control(pDX, IDC_LIST3, m_list2);
	DDX_Control(pDX, IDC_LIST4, m_list3);
	DDX_Control(pDX, IDC_LIST1, m_list4);
	DDX_Control(pDX, IDC_LIST5, m_list5);
	DDX_Text(pDX, IDC_EDIT1, clock);
	DDX_Text(pDX, IDC_EDIT2, cpuRate);
	DDX_Text(pDX, IDC_EDIT3, ioRate);
	DDX_Text(pDX, IDC_EDIT4, clockRate);
}


BEGIN_MESSAGE_MAP(FCFS_SchedulingDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &FCFS_SchedulingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &FCFS_SchedulingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &FCFS_SchedulingDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// FCFS_SchedulingDlg 消息处理程序


BOOL FCFS_SchedulingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CRect rect;
	GetClientRect(&rect);

	// 初始化列表1
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list1.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list1.InsertColumn(2, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list1.InsertColumn(3, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list1.InsertColumn(4, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 5);

	// 初始化列表2
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list2.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertColumn(2, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertColumn(3, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertColumn(4, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertItem(0, _T(""));
	m_list2.SetItemText(0, 0, _T("执行进程"));

	// 初始化列表3
	m_list3.SetExtendedStyle(m_list3.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list3.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertColumn(2, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertColumn(3, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertColumn(4, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertItem(0, _T(""));
	m_list3.SetItemText(0, 0, _T("就绪进程"));

	// 初始化列表4
	m_list4.SetExtendedStyle(m_list4.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list4.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertColumn(2, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertColumn(3, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertColumn(4, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertItem(0, _T(""));
	m_list4.SetItemText(0, 0, _T("阻塞进程"));

	// 初始化列表5
	m_list5.SetExtendedStyle(m_list5.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list5.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertColumn(2, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertColumn(3, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertColumn(4, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertItem(0, _T(""));
	m_list5.SetItemText(0, 0, _T("完成进程"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void FCFS_SchedulingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		clock++;
		PCB* pend, ready, finish, ioa, iob;
		schedulingService ss;
		//执行进程显示
		m_list2.SetItemText(0, 1, _T("P1"));
		m_list2.SetItemText(0, 2, _T("P1"));
		//就绪进程显示

		//阻塞进程显示

		//完成进程显示
		break;
	}
	UpdateData(FALSE);//数据更新至窗口
	CDialogEx::OnTimer(nIDEvent);
}


void FCFS_SchedulingDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//数据从窗口更新
	clock = 0;
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//数据更新至窗口
}

//暂停
void FCFS_SchedulingDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}

//继续
void FCFS_SchedulingDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//数据从窗口更新
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//数据更新至窗口
}
