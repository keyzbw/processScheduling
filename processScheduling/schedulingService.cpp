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
	//创建表头
	str.Format(_T("%d"), 0);
	createtime += int(rand() % 4);
	int prio_round = int(rand() % 20);
	int needcputime = int(rand() % 10 + 1);
	int neediotime = (int)(rand() % 10+1);
	PCB *pcb = new PCB(_T("进程") + str + _T("号"), createtime, prio_round, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("等待中"), NULL);
	PP->pend = pcb;
	PCB* add = PP->pend;
	for (int i = 1; i < n; i++) {
		str.Format(_T("%d"), i);
		createtime += int(rand() % 4);
		int prio_round = int(rand() % 20);
		int needcputime = int(rand() % 10 + 1);
		int neediotime = (int)(rand() % 10+1);
		PCB *pcb = new PCB(_T("进程") + str + _T("号"), createtime, prio_round, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("等待中"), NULL);
		add->next = pcb;
		add = add->next;
	}
	return PP;
}


void schedulingService::FIFO(int time,PCBPointer* PP)
{
	PCB * tmppend = PP->pend;
	//ready尾指针
	PCB * tmpready = PP->ready;
	if (PP->ready != NULL) {
		while (tmpready->next != NULL) {
			tmpready = tmpready->next;
		}
	}
	//ioa尾指针
	PCB * tmpioa = PP->ioa;
	if (PP->ioa != NULL) {
		while (tmpioa->next != NULL) {
			tmpioa = tmpioa->next;
		}
	}
	//iob尾指针
	PCB * tmpiob = PP->iob;
	if (PP->iob != NULL) {
		while (tmpiob->next != NULL) {
			tmpiob = tmpiob->next;
		}
	}
	//finish尾指针
	PCB * tmpfinish = PP->finish;
	if (PP->finish != NULL) {
		while (tmpfinish->next != NULL) {
			tmpfinish = tmpfinish->next;
		}
	}
	//pend到时间的加入ioa或iob
	while (PP->pend != NULL && PP->pend->createtime == time) {
		tmppend = PP->pend->next;
		if (PP->pend->iotype == 0) {
			PP->pend->state = "等待进行A资源的IO";
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
			PP->pend->state = "等待进行B资源的IO";
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
	//ioa或iob执行完io操作的进入ready
		if (PP->ioa != NULL) {
			PP->ioa->state = "进行A资源IO中";
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
				tmpready->state = "等待cpu中";
				PP->ioa = PP->ioa->next;
				tmpready->next = NULL;
			}
		}
		
		if (PP->iob != NULL) {
			PP->iob->state = "进行B资源IO中";
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
				tmpready->state = "等待cpu中";
				PP->iob = PP->iob->next;
				tmpready->next = NULL;
			}
		}
		
	//ready里执行完cpu操作的进入finish
		if (PP->ready != NULL) {
			PP->ready->state = "执行中";
			PP->ready->needcputime -= 1;
			PP->cpuratio++;
			if (PP->ready->needcputime == 0) {
				PP->ready->state = "已完成";
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
	//ready尾指针
	PCB * tmpready = PP->ready;
	if (PP->ready != NULL) {
		while (tmpready->next != NULL) {
			tmpready = tmpready->next;
		}
	}
	//ioa尾指针
	PCB * tmpioa = PP->ioa;
	if (PP->ioa != NULL) {
		while (tmpioa->next != NULL) {
			tmpioa = tmpioa->next;
		}
	}
	//iob尾指针
	PCB * tmpiob = PP->iob;
	if (PP->iob != NULL) {
		while (tmpiob->next != NULL) {
			tmpiob = tmpiob->next;
		}
	}
	//finish尾指针
	PCB * tmpfinish = PP->finish;
	if (PP->finish != NULL) {
		while (tmpfinish->next != NULL) {
			tmpfinish = tmpfinish->next;
		}
	}
	//pend到时间的加入ioa或iob
	while (PP->pend != NULL && PP->pend->createtime == time) {
		tmppend = PP->pend->next;
		if (PP->pend->iotype == 0) {
			PP->pend->state = "等待进行A资源的IO";
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
			PP->pend->state = "等待进行B资源的IO";
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
	//ioa或iob执行完io操作的进入ready
	if (PP->ioa != NULL) {
		PP->ioa->state = "进行A资源IO中";
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
			tmpready->state = "等待cpu中";
			PP->ioa = PP->ioa->next;
			tmpready->next = NULL;
		}
	}

	if (PP->iob != NULL) {
		PP->iob->state = "进行B资源IO中";
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
			tmpready->state = "等待cpu中";
			PP->iob = PP->iob->next;
			tmpready->next = NULL;
		}
	}

	//ready里执行完cpu操作的进入finish
	if (PP->ready != NULL) {
		PP->ready->state = "执行中";
		PP->ready->needcputime -= 1;
		PP->cpuratio++;
		PP->ready->prio_round++;
		if (PP->ready->needcputime == 0) {
			PP->ready->state = "已完成";
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
			PP->ready->state = "等待CPU中";
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

	//ioa尾指针
	PCB * tmpioa = PP->ioa;
	if (PP->ioa != NULL) {
		while (tmpioa->next != NULL) {
			tmpioa = tmpioa->next;
		}
	}
	//iob尾指针
	PCB * tmpiob = PP->iob;
	if (PP->iob != NULL) {
		while (tmpiob->next != NULL) {
			tmpiob = tmpiob->next;
		}
	}
	//finish尾指针
	PCB * tmpfinish = PP->finish;
	if (PP->finish != NULL) {
		while (tmpfinish->next != NULL) {
			tmpfinish = tmpfinish->next;
		}
	}
	//pend到时间的加入ioa或iob
	while (PP->pend != NULL && PP->pend->createtime == time) {
		tmppend = PP->pend->next;
		if (PP->pend->iotype == 0) {
			PP->pend->state = "等待进行A资源的IO";
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
			PP->pend->state = "等待进行B资源的IO";
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
	//ioa或iob执行完io操作的进入ready
	if (PP->ioa != NULL) {
		PP->ioa->state = "进行A资源IO中";
		PP->ioa->neediotime -= 1;
		PP->ioaratio++;
		if (PP->ioa->neediotime == 0) {
			PP->ioa->state = "等待cpu中";
			if (PP->ready == NULL) {
				PP->ready = PP->ioa;
			}
			else {
				if (PP->ioa->prio_round > PP->ready->prio_round) {
					PCB* tmpready = PP->ready;
					PP->ready = PP->ioa;
					PP->ioa = PP->ioa->next;
					PP->ready->next = tmpready;
				}
				PCB* tmpready = PP->ready;
				while (tmpready->next != NULL && tmpready->next->prio_round > PP->ioa->prio_round) {
					tmpready = tmpready->next;
				}
				PCB* tmptmpready = tmpready->next;
				PCB* tmptmpioa = PP->ioa;
				PP->ioa = PP->ioa->next;
				tmpready->next = tmptmpioa;
				tmptmpioa->next = tmptmpready;
			}
		}
	}

	if (PP->iob != NULL) {
		PP->iob->state = "进行B资源IO中";
		PP->iob->neediotime -= 1;
		PP->iobratio++;
		if (PP->iob->neediotime == 0) {
			PP->iob->state = "等待cpu中";
			if (PP->ready == NULL) {
				PP->ready = PP->iob;
			}
			else {
				if (PP->iob->prio_round > PP->ready->prio_round) {
					PCB* tmpready = PP->ready;
					PP->ready = PP->iob;
					PP->iob = PP->iob->next;
					PP->ready->next = tmpready;
				}
				PCB* tmpready = PP->ready;
				while (tmpready->next != NULL && tmpready->next->prio_round > PP->iob->prio_round) {
					tmpready = tmpready->next;
				}
				PCB* tmptmpready = tmpready->next;
				PCB* tmptmpiob = PP->iob;
				PP->iob = PP->iob->next;
				tmpready->next = tmptmpiob;
				tmptmpiob->next = tmptmpready;
			}
		}
	}

	//ready里执行完cpu操作的进入finish
	if (PP->ready != NULL) {
		PP->ready->state = "执行中";
		PP->ready->needcputime -= 1;
		PP->ready->prio_round -= 3;
		PP->cpuratio++;
		if (PP->ready->needcputime == 0) {
			PP->ready->state = "已完成";
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
		if (PP->ready->next != NULL&& PP->ready->prio_round < PP->ready->next->prio_round) {
			PP->ready->state = "等待cpu中";
			PP->ready->next->state = "执行中";
			PCB* tmpready = PP->ready;
			while (tmpready->next->prio_round > PP->ready->prio_round) {
				tmpready = tmpready->next;
			}
			PCB* tmptmpready = PP->ready;
			PCB* tmptmptmpready = tmpready->next;
			PP->ready = PP->ready->next;
			tmpready->next = tmptmpready;
			tmptmpready->next = tmptmptmpready;
		}
	
	}
}


schedulingService::~schedulingService()
{
}

