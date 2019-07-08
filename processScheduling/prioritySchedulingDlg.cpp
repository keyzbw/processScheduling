// prioritySchedulingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "processScheduling.h"
#include "prioritySchedulingDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "schedulingService.h"
// prioritySchedulingDlg �Ի���

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


// prioritySchedulingDlg ��Ϣ�������


void prioritySchedulingDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL prioritySchedulingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	GetClientRect(&rect);

	// ��ʼ���б�1
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width()-30) / 6);
	m_list1.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(2, _T("���ȼ�"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(3, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(4, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list1.InsertColumn(5, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 6);

	// ��ʼ���б�2
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list2.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(2, _T("���ȼ�"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(3, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(4, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertColumn(5, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list2.InsertItem(0, _T(""));
	m_list2.SetItemText(0, 0, _T("ִ�н���"));

	// ��ʼ���б�3
	m_list3.SetExtendedStyle(m_list3.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list3.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(2, _T("���ȼ�"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(3, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(4, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertColumn(5, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list3.InsertItem(0, _T(""));
	m_list3.SetItemText(0, 0, _T("��������"));

	// ��ʼ���б�4
	m_list4.SetExtendedStyle(m_list4.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list4.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(2, _T("���ȼ�"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(3, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(4, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertColumn(5, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list4.InsertItem(0, _T(""));
	m_list4.SetItemText(0, 0, _T("��������"));

	// ��ʼ���б�5
	m_list5.SetExtendedStyle(m_list5.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list5.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(1, _T("������"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(2, _T("���ȼ�"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(3, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(4, _T("������ʱ��"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertColumn(5, _T("����״̬"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
	m_list5.InsertItem(0, _T(""));
	m_list5.SetItemText(0, 0, _T("��ɽ���"));


	//���ó�ʼ����
	UpdateData(FALSE);//���ݸ���������

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



//����
void prioritySchedulingDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//���ݴӴ��ڸ���
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//���ݸ���������
}

//�ؽ�����
void prioritySchedulingDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);//���ݴӴ��ڸ���
	clock = 0;
	schedulingService ss;
	PP = ss.createPCB(5);
	SetTimer(1, 1000 / clockRate, NULL);
	UpdateData(FALSE);//���ݸ���������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//��ʱ������
void prioritySchedulingDlg::OnTimer(UINT_PTR nIDEvent)
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
		ss.PRIORITY(clock, PP);
		PCB* p = PP->ready;
		int i = 0;
		CString createTime, runTime,priority;

		//ִ�н�����ʾ
		m_list2.InsertItem(0, _T(""));
		m_list2.SetItemText(0, 0, _T("ִ�н���"));
		if (p != NULL) {
			m_list2.SetItemText(0, 1, p->name);
			createTime.Format(_T("%d"), p->createtime);
			priority.Format(_T("%d"), p->prio_round);
			m_list2.SetItemText(0, 2, priority);
			m_list2.SetItemText(0, 3, createTime);
			runTime.Format(_T("%d"), p->needcputime);
			m_list2.SetItemText(0, 4, runTime);
			m_list2.SetItemText(0, 5, p->state);
			//����������ʾ
			i = 1;
			m_list3.InsertItem(0, _T(""));
			m_list3.SetItemText(0, 0, _T("��������"));
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
		//����������ʾ
		i = 1;
		m_list4.InsertItem(0, _T(""));
		m_list4.SetItemText(0, 0, _T("��������"));
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
		//��ɽ�����ʾ
		i = 1;
		m_list5.InsertItem(0, _T(""));
		m_list5.SetItemText(0, 0, _T("��ɽ���"));
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
		//cup��������ʾ
		double cRate;
		cRate = (double)PP->cpuratio / (double)clock;
		cpuRate.Format(_T("%0.2lf"), cRate * 100);
		break;
	}
	UpdateData(FALSE);//���ݸ���������
					  //ʱ������
	clock++;
	CDialogEx::OnTimer(nIDEvent);
}

//��ͣ
void prioritySchedulingDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
}
