#include "stdafx.h"
#include "schedulingService.h"
#include <stdlib.h>


schedulingService::schedulingService()
{
}

void schedulingService::PCBinit(int n, PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob)
{
	PCB* add= pend;
	int createtime;
	for (int i = 0; i < n; i++) {
		CString str;
		str.Format(_T("%d"), i);
		createtime += int(rand() * 4);
		int needcputime = int(rand() * 15 + 1);
		int neediotime = (int)((needcputime - 1)*rand());
		PCB *pcb = new PCB(_T("����")+str+ _T("��"),createtime,0,0,0,needcputime,neediotime,(int)(rand()+0.5),_T("�ȴ���"),NULL);
		add->next = pcb;
		add = add->next;
}
}

PCBPointer schedulingService::FIFO(int time, PCB * pend, PCB * ready, PCB * finish, PCB * ioa, PCB * iob)
{
	PCB * tmppend = pend;
	//readyβָ��
	PCB * tmpready = ready;
	while (tmpready->next != NULL) {
		tmpready = tmpready->next;
	}
	//ioaβָ��
	PCB * tmpioa = ioa;
	while (tmpioa->next != NULL) {
		tmpioa = tmpioa->next;
	}
	//iobβָ��
	PCB * tmpiob = iob;
	while (tmpiob->next != NULL) {
		tmpiob = tmpiob->next;
	}
	//finishβָ��
	PCB * tmpfinish = finish;
	while (tmpfinish->next != NULL) {
		tmpfinish = tmpfinish->next;
	}
	//pend��ʱ��ļ���ioa��iob
	while (pend!=NULL && pend->createtime == time) {
		tmppend = pend->next;
		pend->next = NULL;
		if (pend->iotype == 0) {
			pend->state = "�ȴ�����A��Դ��IO";
			tmpioa->next = pend;
			pend = tmppend;
			tmpioa = tmpioa->next;
		}
		else {
			pend->state = "�ȴ�����B��Դ��IO";
			tmpiob->next = pend;
			pend = tmppend;
			tmpiob = tmpiob->next;
		}
	//ioa��iobִ����io�����Ľ���ready
		ioa->neediotime -= 1;
		if (ioa->neediotime == 0) {
			tmpready->next = ioa;
			tmpready = tmpready->next;
			ioa = ioa->next;
			ioa->state = "����A��ԴIO��";
			tmpready->next = NULL;
		}
		iob->neediotime -= 1;
		if (iob->neediotime == 0) {
			tmpready->next = iob;
			tmpready = tmpready->next;
			iob = iob->next;
			iob->state = "����B��ԴIO��";
			tmpready->next = NULL;
		}
	//ready��ִ����cpu�����Ľ���finish
		ready->needcputime -= 1;
		if (ready->needcputime == 0) {
			ready->state = "�����";
			tmpfinish->next = ready;
			tmpfinish = tmpfinish->next;
			tmpfinish->next = NULL;
			ready = ready->next;
		}
	}
	return PCBPointer(pend, ready, finish, ioa, iob);
}


schedulingService::~schedulingService()
{
}

