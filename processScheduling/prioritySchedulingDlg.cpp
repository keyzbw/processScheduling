// prioritySchedulingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "processScheduling.h"
#include "prioritySchedulingDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "schedulingService.h"
// prioritySchedulingDlg 对话框

IMPLEMENT_DYNAMIC(prioritySchedulingDlg, CDialogEx)

prioritySchedulingDlg::prioritySchedulingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRIORITYSCHEDULINGDLG, pParent)
	, clock(0)
	, cpuRate(_T(""))
	, ioRate(_T(""))
	, clockRate(1)
{

}

prioritySchedulingDlg::~prioritySchedulingDlg()
{
}

void prioritySchedulingDlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(prioritySchedulingDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &prioritySchedulingDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &prioritySchedulingDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &prioritySchedulingDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &prioritySchedulingDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// prioritySchedulingDlg 消息处理程序


void prioritySchedulingDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


BOOL prioritySchedulingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	GetClientRect(&rect);

	// 初始化列表1
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0, _T("队列"), LVCFMT_CENTER, (rect.Width()-30) / 6);
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


	//设置初始数据
	UpdateData(FALSE);//数据更新至窗口

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



//继续
void prioritySchedulingDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//数据从窗口更新
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//数据更新至窗口
}

//重建进程
void prioritySchedulingDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);//数据从窗口更新
	clock = 0;
	schedulingService ss;
	PP = ss.createPCB(5);
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//数据更新至窗口
	// TODO: 在此添加控件通知处理程序代码
}

//定时器函数
void prioritySchedulingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		//清除列表数据
		m_list2.DeleteAllItems();
		m_list3.DeleteAllItems();
		m_list4.DeleteAllItems();
		m_list5.DeleteAllItems();
		schedulingService ss;
		ss.PRIORITY(clock, PP);
		PCB* p = PP->ready;
		int i = 0;
		CString createTime, runTime,priority;

		//执行进程显示
		m_list2.InsertItem(0, _T(""));
		m_list2.SetItemText(0, 0, _T("执行进程"));
		if (p != NULL) {
			m_list2.SetItemText(0, 1, p->name);
			createTime.Format(_T("%d"), p->createtime);
			priority.Format(_T("%d"), p->prio_round);
			m_list2.SetItemText(0, 2, priority);
			m_list2.SetItemText(0, 3, createTime);
			runTime.Format(_T("%d"), p->needcputime);
			m_list2.SetItemText(0, 4, runTime);
			m_list2.SetItemText(0, 5, p->state);
			//就绪进程显示
			i = 1;
			m_list3.InsertItem(0, _T(""));
			m_list3.SetItemText(0, 0, _T("就绪进程"));
			while (p->next != NULL) {
				p = p->next;
				m_list3.InsertItem(i, _T(""));
				m_list3.SetItemText(i, 1, p->name);
				createTime.Format(_T("%d"), p->createtime);
				priority.Format(_T("%d"), p->prio_round);
				m_list3.SetItemText(i, 2, priority);
				m_list3.SetItemText(i, 3, createTime);
				runTime.Format(_T("%d"), p->needcputime);
				m_list3.SetItemText(i, 4, runTime);
				m_list3.SetItemText(i, 5, p->state);
				i++;
			}
		}
		//阻塞进程显示
		i = 1;
		m_list4.InsertItem(0, _T(""));
		m_list4.SetItemText(0, 0, _T("阻塞进程"));
		p = PP->ioa;
		while (p != NULL) {
			m_list4.InsertItem(i, _T(""));
			m_list4.SetItemText(i, 1, p->name);
			createTime.Format(_T("%d"), p->createtime);
			priority.Format(_T("%d"), p->prio_round);
			m_list4.SetItemText(i, 2, priority);
			m_list4.SetItemText(i, 3, createTime);
			runTime.Format(_T("%d"), p->neediotime);
			m_list4.SetItemText(i, 4, runTime);
			m_list4.SetItemText(i, 5, p->state);
			p = p->next;
			i++;
		}
		p = PP->iob;
		while (p != NULL) {
			m_list4.InsertItem(i, _T(""));
			m_list4.SetItemText(i, 1, p->name);
			createTime.Format(_T("%d"), p->createtime);
			priority.Format(_T("%d"), p->prio_round);
			m_list4.SetItemText(i, 2, priority);
			runTime.Format(_T("%d"), p->neediotime);
			m_list4.SetItemText(i, 3, createTime);
			m_list4.SetItemText(i, 4, runTime);
			m_list4.SetItemText(i, 5, p->state);
			p = p->next;
			i++;
		}
		//完成进程显示
		i = 1;
		m_list5.InsertItem(0, _T(""));
		m_list5.SetItemText(0, 0, _T("完成进程"));
		p = PP->finish;
		while (p != NULL) {
			m_list5.InsertItem(i, _T(""));
			m_list5.SetItemText(i, 1, p->name);
			priority.Format(_T("%d"), p->prio_round);
			m_list5.SetItemText(i, 2, priority);
			createTime.Format(_T("%d"), p->createtime);
			m_list5.SetItemText(i, 3, createTime);
			runTime.Format(_T("%d"), p->count);
			m_list5.SetItemText(i, 4, runTime);
			m_list5.SetItemText(i, 5, p->state);
			p = p->next;
			i++;
		}
		//cup利用率显示
		double cRate;
		cRate = (double)PP->cpuratio / (double)clock;
		cpuRate.Format(_T("%0.2lf"), cRate * 100);
		break;
	}
	UpdateData(FALSE);//数据更新至窗口
					  //时钟增加
	clock++;
	CDialogEx::OnTimer(nIDEvent);
}

//暂停
void prioritySchedulingDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}
