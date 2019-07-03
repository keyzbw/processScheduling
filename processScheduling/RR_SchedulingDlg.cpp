// RR_SchedulingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "processScheduling.h"
#include "RR_SchedulingDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// RR_SchedulingDlg 对话框

IMPLEMENT_DYNAMIC(RR_SchedulingDlg, CDialogEx)

RR_SchedulingDlg::RR_SchedulingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RRSCHEDULINGDLG, pParent)
	, clock(0)
	, cupRate(_T(""))
	, ioRate(_T(""))
	, timeSlice(1)
	, clockRate(1)
{

}

RR_SchedulingDlg::~RR_SchedulingDlg()
{
}

void RR_SchedulingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list1);
	DDX_Control(pDX, IDC_LIST3, m_list2);
	DDX_Control(pDX, IDC_LIST4, m_list3);
	DDX_Control(pDX, IDC_LIST1, m_list4);
	DDX_Control(pDX, IDC_LIST5, m_list5);
	DDX_Text(pDX, IDC_EDIT1, clock);
	DDX_Text(pDX, IDC_EDIT2, cupRate);
	DDX_Text(pDX, IDC_EDIT3, ioRate);
	DDX_Text(pDX, IDC_EDIT6, timeSlice);
	DDX_Text(pDX, IDC_EDIT4, clockRate);
}


BEGIN_MESSAGE_MAP(RR_SchedulingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &RR_SchedulingDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &RR_SchedulingDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &RR_SchedulingDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// RR_SchedulingDlg 消息处理程序


BOOL RR_SchedulingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CRect rect;
	GetClientRect(&rect);

	// 初始化列表1
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(2, _T("优先级"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(3, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(4, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(5, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 6);

	// 初始化列表2
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list2.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(2, _T("优先级"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(3, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(4, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(5, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertItem(0, _T(""));
	m_list2.SetItemText(0, 0, _T("执行进程"));

	// 初始化列表3
	m_list3.SetExtendedStyle(m_list3.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list3.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(2, _T("优先级"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(3, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(4, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(5, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertItem(0, _T(""));
	m_list3.SetItemText(0, 0, _T("就绪进程"));

	// 初始化列表4
	m_list4.SetExtendedStyle(m_list4.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list4.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(2, _T("优先级"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(3, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(4, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(5, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertItem(0, _T(""));
	m_list4.SetItemText(0, 0, _T("阻塞进程"));

	// 初始化列表5
	m_list5.SetExtendedStyle(m_list5.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list5.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(2, _T("优先级"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(3, _T("创建时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(4, _T("已运行时间"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(5, _T("进程状态"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertItem(0, _T(""));
	m_list5.SetItemText(0, 0, _T("完成进程"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//重建进程
void RR_SchedulingDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//数据从窗口更新
	clock = 0;
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//数据更新至窗口
}

//定时器
void RR_SchedulingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		clock++;
		break;
	}
	UpdateData(FALSE);//数据更新至窗口
	CDialogEx::OnTimer(nIDEvent);
}

//继续
void RR_SchedulingDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//数据从窗口更新
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//数据更新至窗口
}

//暂停
void RR_SchedulingDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}
