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
	int needcputime = int(rand() % 10 + 1);
	int neediotime = (int)(rand() % 10+1);
	PCB *pcb = new PCB(_T("进程") + str + _T("号"), createtime, 0, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("等待中"), NULL);
	PP->pend = pcb;
	PCB* add = PP->pend;
	for (int i = 1; i < n; i++) {
		str.Format(_T("%d"), i);
		createtime += int(rand() % 4);
		int needcputime = int(rand() % 10 + 1);
		int neediotime = (int)(rand() % 10+1);
		PCB *pcb = new PCB(_T("进程") + str + _T("号"), createtime, 0, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("等待中"), NULL);
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


schedulingService::~schedulingService()
{
}

