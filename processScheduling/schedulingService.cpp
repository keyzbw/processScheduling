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
	PCBPointer* PP = new PCBPointer();
	int createtime = 0;
	CString str;
	//srand((unsigned int)(time(NULL)));
	//������ͷ
	str.Format(_T("%d"), 0);
	createtime += int(rand() % 4);
	int needcputime = int(rand() % 10 + 1);
	int neediotime = (int)(rand() % 10+1);
	PCB *pcb = new PCB(_T("����") + str + _T("��"), createtime, 0, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("�ȴ���"), NULL);
	PP->pend = pcb;
	PCB* add = PP->pend;
	for (int i = 1; i < n; i++) {
		str.Format(_T("%d"), i);
		createtime += int(rand() % 4);
		int needcputime = int(rand() % 10 + 1);
		int neediotime = (int)(rand() % 10+1);
		PCB *pcb = new PCB(_T("����") + str + _T("��"), createtime, 0, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("�ȴ���"), NULL);
		add->next = pcb;
		add = add->next;
	}
	return PP;
}


void schedulingService::FIFO(int time,PCBPointer* PP)
{
	PCB * tmppend = PP->pend;
	//readyβָ��
	PCB * tmpready = PP->ready;
	if (PP->ready != NULL) {
		while (tmpready->next != NULL) {
			tmpready = tmpready->next;
		}
	}
	//ioaβָ��
	PCB * tmpioa = PP->ioa;
	if (PP->ioa != NULL) {
		while (tmpioa->next != NULL) {
			tmpioa = tmpioa->next;
		}
	}
	//iobβָ��
	PCB * tmpiob = PP->iob;
	if (PP->iob != NULL) {
		while (tmpiob->next != NULL) {
			tmpiob = tmpiob->next;
		}
	}
	//finishβָ��
	PCB * tmpfinish = PP->finish;
	if (PP->finish != NULL) {
		while (tmpfinish->next != NULL) {
			tmpfinish = tmpfinish->next;
		}
	}
	//pend��ʱ��ļ���ioa��iob
	while (PP->pend != NULL && PP->pend->createtime == time) {
		tmppend = PP->pend->next;
		if (PP->pend->iotype == 0) {
			PP->pend->state = "�ȴ�����A��Դ��IO";
			if (PP->ioa == NULL) {
				PP->ioa = PP->pend;
				tmpioa = PP->pend;
			}
			else {
				tmpioa->next = PP->pend;
				tmpioa = tmpioa->next;
			}
			tmpioa->next = NULL;
		}
		else {
			PP->pend->state = "�ȴ�����B��Դ��IO";
			if (PP->iob == NULL) {
				PP->iob = PP->pend;
				tmpiob = PP->pend;
			}
			else {
				tmpiob->next = PP->pend;
				tmpiob = tmpiob->next;
			}
			tmpiob->next = NULL;
		}
		PP->pend = tmppend;
	}
	//ioa��iobִ����io�����Ľ���ready
		if (PP->ioa != NULL) {
			PP->ioa->state = "����A��ԴIO��";
			PP->ioa->neediotime -= 1;
			if (PP->ioa->neediotime == 0) {
				if (PP->ready == NULL) {
					PP->ready = PP->ioa;
					tmpready = PP->ioa;
				}
				else {
					tmpready->next = PP->ioa;
					tmpready = tmpready->next;
				}
				tmpready->state = "�ȴ�cpu��";
				PP->ioa = PP->ioa->next;
				tmpready->next = NULL;
			}
		}
		
		if (PP->iob != NULL) {
			PP->iob->state = "����B��ԴIO��";
			PP->iob->neediotime -= 1;
			if (PP->iob->neediotime == 0) {
				if (PP->ready == NULL) {
					PP->ready = PP->iob;
					tmpready = PP->iob;
				}
				else {
					tmpready->next = PP->iob;
					tmpready = tmpready->next;
				}
				tmpready->state = "�ȴ�cpu��";
				PP->iob = PP->iob->next;
				tmpready->next = NULL;
			}
		}
		
	//ready��ִ����cpu�����Ľ���finish
		if (PP->ready != NULL) {
			PP->ready->state = "ִ����";
			PP->ready->needcputime -= 1;
			if (PP->ready->needcputime == 0) {
				PP->ready->state = "�����";
				if (PP->finish == NULL) {
					PP->finish = PP->ready;
					tmpfinish = PP->ready;
				}
				else {
					tmpfinish->next = PP->ready;
					tmpfinish = tmpfinish->next;
				}
				PP->ready = PP->ready->next;
				tmpfinish->next = NULL;
			}
		}
}


schedulingService::~schedulingService()
{
}

