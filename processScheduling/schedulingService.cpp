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
	int prio_round = int(rand() % 20);
	int needcputime = int(rand() % 10 + 1);
	int neediotime = (int)(rand() % 10+1);
	PCB *pcb = new PCB(_T("����") + str + _T("��"), createtime, prio_round, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("�ȴ���"), NULL);
	PP->pend = pcb;
	PCB* add = PP->pend;
	for (int i = 1; i < n; i++) {
		str.Format(_T("%d"), i);
		createtime += int(rand() % 4);
		int prio_round = int(rand() % 20);
		int needcputime = int(rand() % 10 + 1);
		int neediotime = (int)(rand() % 10+1);
		PCB *pcb = new PCB(_T("����") + str + _T("��"), createtime, prio_round, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("�ȴ���"), NULL);
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
	//pend��ʱ��ļ���ready
	while (PP->pend != NULL && PP->pend->createtime == time) {
		if (PP->ready == NULL) {
			PP->ready = PP->pend;
			tmpready = PP->pend;
		}
		else {
			tmpready->next = PP->pend;
			tmpready = tmpready->next;
		}
		tmpready->state = "�ȴ�cpu��";
		PP->pend = PP->pend->next;
		tmpready->next = NULL;
	}
	//ִ�н������������ʱ��ת����������
	if (PP->ready != NULL) {
		if (PP->ready->neediotime > 0) {
			tmpready = PP->ready->next;
			if (PP->ready->iotype == 0) {
				PP->ready->state = "�ȴ�����A��Դ��IO";
				if (PP->ioa == NULL) {
					PP->ioa = PP->ready;
					tmpioa = PP->ready;
				}
				else {
					tmpioa->next = PP->ready;
					tmpioa = tmpioa->next;
				}
				tmpioa->next = NULL;
			}
			else {
				PP->ready->state = "�ȴ�����B��Դ��IO";
				if (PP->iob == NULL) {
					PP->iob = PP->ready;
					tmpiob = PP->ready;
				}
				else {
					tmpiob->next = PP->ready;
					tmpiob = tmpiob->next;
				}
				tmpiob->next = NULL;
			}
			PP->ready = tmpready;
		}
		
	}
	//ioa��iobִ����io�����Ľ���ready
		if (PP->ioa != NULL) {
			PP->ioa->state = "����A��ԴIO��";
			PP->ioa->neediotime -= 1;
			PP->ioaratio++;
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
			PP->iobratio++;
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
			PP->cpuratio++;
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

void schedulingService::RR2(int time, PCBPointer* PP)
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
		PP->ioaratio++;
		if (PP->ioa->neediotime == 0) {
			if (PP->ready == NULL) {
				PP->ready = PP->ioa;
				tmpready = PP->ioa;
			}
			else {
				tmpready->next = PP->ioa;
				tmpready = tmpready->next;
			}
			tmpready->prio_round = 0;
			tmpready->state = "�ȴ�cpu��";
			PP->ioa = PP->ioa->next;
			tmpready->next = NULL;
		}
	}

	if (PP->iob != NULL) {
		PP->iob->state = "����B��ԴIO��";
		PP->iob->neediotime -= 1;
		PP->iobratio++;
		if (PP->iob->neediotime == 0) {
			if (PP->ready == NULL) {
				PP->ready = PP->iob;
				tmpready = PP->iob;
			}
			else {
				tmpready->next = PP->iob;
				tmpready = tmpready->next;
			}
			tmpready->prio_round = 0;
			tmpready->state = "�ȴ�cpu��";
			PP->iob = PP->iob->next;
			tmpready->next = NULL;
		}
	}

	//ready��ִ����cpu�����Ľ���finish
	if (PP->ready != NULL) {
		PP->ready->state = "ִ����";
		PP->ready->needcputime -= 1;
		PP->cpuratio++;
		PP->ready->prio_round++;
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
		if (PP->ready->prio_round == 2&&PP->ready!=tmpready) {
			PP->ready->state = "�ȴ�CPU��";
			PP->ready->prio_round = 0;
			tmpready->next = PP->ready;
			PP->ready = PP->ready->next;
			tmpready = tmpready->next;
			tmpready->next = NULL;
		}
	}
}

void schedulingService::PRIORITY(int time, PCBPointer* PP)
{
	PCB * tmppend = PP->pend;

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
	//pend��ʱ��ļ���Ready����
	while (PP->pend != NULL && PP->pend->createtime == time) {
		tmppend = PP->pend->next;
		PP->pend->state = "�ȴ�cpu��";
		if (PP->ready == NULL) {
			PP->ready = PP->pend;
			PP->pend->next = NULL;
		}
		else {
			if (PP->pend->prio_round > PP->ready->prio_round) {
				PCB* tmpready = PP->ready;
				PP->ready = PP->pend;
				PP->pend = PP->pend->next;
				PP->ready->next = tmpready;
			}
			else {
				PCB* tmpready = PP->ready;
				while (tmpready->next != NULL && tmpready->next->prio_round > PP->pend->prio_round) {
					tmpready = tmpready->next;
				}
				PCB* tmptmpready = tmpready->next;
				tmpready->next = PP->pend;
				PP->pend->next = tmptmpready;
			}
		}
		PP->pend = tmppend;
	}
	//������������io����������������
	PCB * tmpready = PP->ready;
	if (PP->ready != NULL) {
		if (PP->ready->neediotime > 0) {
			tmpready = PP->ready->next;
			if (PP->ready->iotype == 0) {
				PP->ready->state = "�ȴ�����A��Դ��IO";
				if (PP->ioa == NULL) {
					PP->ioa = PP->ready;
					tmpioa = PP->ready;
				}
				else {
					tmpioa->next = PP->ready;
					tmpioa = tmpioa->next;
				}
				tmpioa->next = NULL;
			}
			else {
				PP->ready->state = "�ȴ�����B��Դ��IO";
				if (PP->iob == NULL) {
					PP->iob = PP->ready;
					tmpiob = PP->ready;
				}
				else {
					tmpiob->next = PP->ready;
					tmpiob = tmpiob->next;
				}
				tmpiob->next = NULL;
			}
			PP->ready = tmpready;
		}
	}
	//ioa��iobִ����io�����Ľ���ready
	if (PP->ioa != NULL) {
		PP->ioa->state = "����A��ԴIO��";
		PP->ioa->neediotime -= 1;
		PP->ioaratio++;
		if (PP->ioa->neediotime == 0) {
			tmpioa = PP->ioa->next;
			PP->ioa->state = "�ȴ�cpu��";
			if (PP->ready == NULL) {
				PP->ready = PP->ioa;
				PP->ready->next = NULL;
			}
			else {
				if (PP->ioa->prio_round > PP->ready->prio_round) {
					PCB* tmpready = PP->ready;
					PP->ready = PP->ioa;
					PP->ioa = PP->ioa->next;
					PP->ready->next = tmpready;
				}
				else {
					PCB* tmpready = PP->ready;
					while (tmpready->next != NULL && tmpready->next->prio_round > PP->ioa->prio_round) {
						tmpready = tmpready->next;
					}
					PCB* tmptmpready = tmpready->next;
					tmpready->next = PP->ioa;
					PP->ioa->next = tmptmpready;
				}
			}
			PP->ioa = tmpioa;
		}
	}

	if (PP->iob != NULL) {
		PP->iob->state = "����B��ԴIO��";
		PP->iob->neediotime -= 1;
		PP->iobratio++;
		if (PP->iob->neediotime == 0) {
			tmpiob = PP->iob->next;
			PP->iob->state = "�ȴ�cpu��";
			if (PP->ready == NULL) {
				PP->ready = PP->iob;
				PP->ready->next = NULL;
			}
			else {
				if (PP->iob->prio_round > PP->ready->prio_round) {
					PCB* tmpready = PP->ready;
					PP->ready = PP->iob;
					PP->iob = PP->iob->next;
					PP->ready->next = tmpready;
				}
				else {
					PCB* tmpready = PP->ready;
					while (tmpready->next != NULL && tmpready->next->prio_round > PP->iob->prio_round) {
						tmpready = tmpready->next;
					}
					PCB* tmptmpready = tmpready->next;
					tmpready->next = PP->iob;
					PP->iob->next = tmptmpready;
				}
			}
			PP->iob = tmpiob;
		}
	}

	//ready��ִ����cpu�����Ľ���finish
	if (PP->ready != NULL) {
		PP->ready->state = "ִ����";
		PP->ready->needcputime -= 1;
		PP->cpuratio++;
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

