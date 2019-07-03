// RR_SchedulingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "processScheduling.h"
#include "RR_SchedulingDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// RR_SchedulingDlg �Ի���

IMPLEMENT_DYNAMIC(RR_SchedulingDlg, CDialogEx)

RR_SchedulingDlg::RR_SchedulingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RRSCHEDULINGDLG, pParent)
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
}


BEGIN_MESSAGE_MAP(RR_SchedulingDlg, CDialogEx)
END_MESSAGE_MAP()


// RR_SchedulingDlg ��Ϣ�������


BOOL RR_SchedulingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect rect;
	GetClientRect(&rect);

	// ��ʼ���б�1
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0, _T("����"), LVCFMT_CENTER, (rect.Width() - 30) / 6);
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
