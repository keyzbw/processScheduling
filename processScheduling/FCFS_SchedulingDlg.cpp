// FCFS_SchedulingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "processScheduling.h"
#include "FCFS_SchedulingDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "schedulingService.h"
// FCFS_SchedulingDlg �Ի���

IMPLEMENT_DYNAMIC(FCFS_SchedulingDlg, CDialogEx)

FCFS_SchedulingDlg::FCFS_SchedulingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FCFSSCHEDULINGDLG, pParent)
	, clock(0)
	, cpuRate(_T("100.00"))
	, ioRate(_T("100.00"))
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


// FCFS_SchedulingDlg ��Ϣ�������


BOOL FCFS_SchedulingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect rect;
	GetClientRect(&rect);

	// ��ʼ���б�1
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list1.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list1.InsertColumn(2, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list1.InsertColumn(3, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list1.InsertColumn(4, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 5);

	// ��ʼ���б�2
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list2.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertColumn(2, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertColumn(3, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertColumn(4, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list2.InsertItem(0, _T(""));
	m_list2.SetItemText(0, 0, _T("ִ�н���"));

	// ��ʼ���б�3
	m_list3.SetExtendedStyle(m_list3.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list3.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertColumn(2, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertColumn(3, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertColumn(4, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list3.InsertItem(0, _T(""));
	m_list3.SetItemText(0, 0, _T("��������"));

	// ��ʼ���б�4
	m_list4.SetExtendedStyle(m_list4.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list4.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertColumn(2, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertColumn(3, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertColumn(4, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list4.InsertItem(0, _T(""));
	m_list4.SetItemText(0, 0, _T("��������"));

	// ��ʼ���б�5
	m_list5.SetExtendedStyle(m_list5.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list5.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertColumn(2, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertColumn(3, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertColumn(4, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 5);
	m_list5.InsertItem(0, _T(""));
	m_list5.SetItemText(0, 0, _T("��ɽ���"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void FCFS_SchedulingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		//����б�����
		m_list2.DeleteAllItems();
		m_list3.DeleteAllItems();
		m_list4.DeleteAllItems();
		m_list5.DeleteAllItems();
		schedulingService ss;
		ss.FIFO(clock, PP);
		PCB* p = PP->ready;
		int i = 0;
		CString createTime,runTime;

		//ִ�н�����ʾ
		m_list2.InsertItem(0, _T(""));
		m_list2.SetItemText(0, 0, _T("ִ�н���"));
		if (p != NULL) {
			m_list2.SetItemText(0, 1, p->name);
			createTime.Format(_T("%d"), p->createtime);
			m_list2.SetItemText(0, 2, createTime);
			runTime.Format(_T("%d"), p->needcputime);
			m_list2.SetItemText(0, 3, runTime);
			m_list2.SetItemText(0, 4, p->state);
			//����������ʾ
			i = 1;
			m_list3.InsertItem(0, _T(""));
			m_list3.SetItemText(0, 0, _T("��������"));
			while (p->next != NULL) {
				p = p->next;
				m_list3.InsertItem(i, _T(""));
				m_list3.SetItemText(i, 1, p->name);
				createTime.Format(_T("%d"), p->createtime);
				m_list3.SetItemText(i, 2, createTime);
				runTime.Format(_T("%d"), p->needcputime);
				m_list3.SetItemText(i, 3, runTime);
				m_list3.SetItemText(i, 4, p->state);
				i++;
			}
		}
		//����������ʾ
		i = 1;
		m_list4.InsertItem(0, _T(""));
		m_list4.SetItemText(0, 0, _T("��������"));
		p = PP->ioa;
		while (p != NULL) {
			m_list4.InsertItem(i, _T(""));
			m_list4.SetItemText(i, 1, p->name);
			createTime.Format(_T("%d"), p->createtime);
			m_list4.SetItemText(i, 2, createTime);
			runTime.Format(_T("%d"), p->neediotime);
			m_list4.SetItemText(i, 3, runTime);
			m_list4.SetItemText(i, 4, p->state);
			p = p->next;
			i++;
		}
		p = PP->iob;
		while (p != NULL) {
			m_list4.InsertItem(i, _T(""));
			m_list4.SetItemText(i, 1, p->name);
			createTime.Format(_T("%d"), p->createtime);
			m_list4.SetItemText(i, 2, createTime);
			runTime.Format(_T("%d"), p->neediotime);
			m_list4.SetItemText(i, 3, runTime);
			m_list4.SetItemText(i, 4, p->state);
			p = p->next;
			i++;
		}
		//��ɽ�����ʾ
		i = 1;
		m_list5.InsertItem(0, _T(""));
		m_list5.SetItemText(0, 0, _T("��ɽ���"));
		p = PP->finish;
		while (p != NULL) {
			m_list5.InsertItem(i, _T(""));
			m_list5.SetItemText(i, 1, p->name);
			createTime.Format(_T("%d"), p->createtime);
			m_list5.SetItemText(i, 2, createTime);
			runTime.Format(_T("%d"), p->count);
			m_list5.SetItemText(i, 3, runTime);
			m_list5.SetItemText(i, 4, p->state);
			p = p->next;
			i++;
		}
		//cup��������ʾ
		double cRate;
		cRate = (double)PP->cpuratio / (double)clock;
		cpuRate.Format(_T("%0.2lf"),cRate*100);
		break;
	}
	UpdateData(FALSE);//���ݸ���������
	//ʱ������
	clock++;
	CDialogEx::OnTimer(nIDEvent);
}


void FCFS_SchedulingDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//���ݴӴ��ڸ���
	clock = 0;
	schedulingService ss;
	PP=ss.createPCB(5);

	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//���ݸ���������
}

//��ͣ
void FCFS_SchedulingDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
}

//����
void FCFS_SchedulingDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//���ݴӴ��ڸ���
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//���ݸ���������
}
