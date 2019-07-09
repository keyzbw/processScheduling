#pragma once
#include "afxcmn.h"
#include "PCBPointer.h"

// FCFS_SchedulingDlg �Ի���

class FCFS_SchedulingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FCFS_SchedulingDlg)

public:
	FCFS_SchedulingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FCFS_SchedulingDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FCFSSCHEDULINGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// �б�ͷ
	CListCtrl m_list1;
	// //ִ�н���
	CListCtrl m_list2;
	// ���������б�
	CListCtrl m_list3;
	// ���������б�
	CListCtrl m_list4;
	// ��ɽ���
	CListCtrl m_list5;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	// ʱ��
	int clock;
	// cpu������
	CString cpuRate;
	// IOA������
	CString ioaRate;
	// ʱ���ٶ�
	double clockRate;
	//���̿��ƿ��б�
	PCBPointer* PP;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	// IOBRate
	CString iobRate;
};
