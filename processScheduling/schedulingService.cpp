#include "stdafx.h"
#include "schedulingService.h"
#include <stdlib.h>


schedulingService::schedulingService()
{
}

PCBPointer* schedulingService::createPCB(int n)
{
	if (n <= 0)
		return NULL;
	PCBPointer* PP= new PCBPointer();
	int createtime = 0;
	CString str;
	//������ͷ
	str.Format(_T("%d"), 0);
	createtime += int(rand() % 4);
	int needcputime = int(rand() % 15 + 1);
	int neediotime = (int)(rand() % 15);
	PCB *pcb = new PCB(_T("����") + str + _T("��"), createtime, 0, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("�ȴ���"), NULL);
	PP->pend = pcb;
	
	PCB* add = PP->pend;
	for (int i = 1; i < n; i++) {
		str.Format(_T("%d"), i);
		createtime += int(rand() % 4);
		int needcputime = int(rand() % 15 + 1);
		int neediotime = (int)(rand() % 15);
		PCB *pcb = new PCB(_T("����") + str + _T("��"), createtime, 0, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("�ȴ���"), NULL);
		add->next = pcb;
		add = add->next;
	}
	return PP;
}

void schedulingService::FIFO(int time, PCBPointer& PP)
{
	PCB * tmppend = PP.pend;
	//readyβָ��
	PCB * tmpready = PP.ready;
	while (tmpready->next != NULL) {
		tmpready = tmpready->next;
	}
	//ioaβָ��
	PCB * tmpioa = PP.ioa;
	while (tmpioa->next != NULL) {
		tmpioa = tmpioa->next;
	}
	//iobβָ��
	PCB * tmpiob = PP.iob;
	while (tmpiob->next != NULL) {
		tmpiob = tmpiob->next;
	}
	//finishβָ��
	PCB * tmpfinish = PP.finish;
	while (tmpfinish->next != NULL) {
		tmpfinish = tmpfinish->next;
	}
	//pend��ʱ��ļ���ioa��iob
	while (PP.pend!=NULL && PP.pend->createtime == time) {
		tmppend = PP.pend->next;
		PP.pend->next = NULL;
		if (PP.pend->iotype == 0) {
			PP.pend->state = "�ȴ�����A��Դ��IO";
			tmpioa->next = PP.pend;
			PP.pend = tmppend;
			tmpioa = tmpioa->next;
		}
		else {
			PP.pend->state = "�ȴ�����B��Դ��IO";
			tmpiob->next = PP.pend;
			PP.pend = tmppend;
			tmpiob = tmpiob->next;
		}
	//ioa��iobִ����io�����Ľ���ready
		PP.ioa->neediotime -= 1;
		if (PP.ioa->neediotime == 0) {
			tmpready->next = PP.ioa;
			tmpready = tmpready->next;
			PP.ioa = PP.ioa->next;
			PP.ioa->state = "����A��ԴIO��";
			tmpready->next = NULL;
		}
		PP.iob->neediotime -= 1;
		if (PP.iob->neediotime == 0) {
			tmpready->next = PP.iob;
			tmpready = tmpready->next;
			PP.iob = PP.iob->next;
			PP.iob->state = "����B��ԴIO��";
			tmpready->next = NULL;
		}
	//ready��ִ����cpu�����Ľ���finish
		PP.ready->needcputime -= 1;
		if (PP.ready->needcputime == 0) {
			PP.ready->state = "�����";
			tmpfinish->next = PP.ready;
			tmpfinish = tmpfinish->next;
			tmpfinish->next = NULL;
			PP.ready = PP.ready->next;
		}
	}
}


schedulingService::~schedulingService()
{
}

