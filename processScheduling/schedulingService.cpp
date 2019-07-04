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
	//创建表头
	str.Format(_T("%d"), 0);
	createtime += int(rand() % 4);
	int needcputime = int(rand() % 15 + 1);
	int neediotime = (int)(rand() % 15);
	PCB *pcb = new PCB(_T("进程") + str + _T("号"), createtime, 0, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("等待中"), NULL);
	PP->pend = pcb;
	PCB* add = PP->pend;
	for (int i = 1; i < n; i++) {
		str.Format(_T("%d"), i);
		createtime += int(rand() % 4);
		int needcputime = int(rand() % 15 + 1);
		int neediotime = (int)(rand() % 15);
		PCB *pcb = new PCB(_T("进程") + str + _T("号"), createtime, 0, 0, 0, needcputime, neediotime, (int)(rand() % 2), _T("等待中"), NULL);
		add->next = pcb;
		add = add->next;
	}
	return PP;
}


PCBPointer* schedulingService::FIFO(int time, PCB * pend, PCB * ready, PCB * finish, PCB * ioa, PCB * iob)
{
	PCB * tmppend = pend;
	//ready尾指针
	PCB * tmpready = ready;
	if (ready != NULL) {
		while (tmpready->next != NULL) {
			tmpready = tmpready->next;
		}
	}
	//ioa尾指针
	PCB * tmpioa = ioa;
	if (ioa != NULL) {
		while (tmpioa->next != NULL) {
			tmpioa = tmpioa->next;
		}
	}
	//iob尾指针
	PCB * tmpiob = iob;
	if (iob != NULL) {
		while (tmpiob->next != NULL) {
			tmpiob = tmpiob->next;
		}
	}
	//finish尾指针
	PCB * tmpfinish = finish;
	if (finish != NULL) {
		while (tmpfinish->next != NULL) {
			tmpfinish = tmpfinish->next;
		}
	}
	//pend到时间的加入ioa或iob
	while (pend != NULL && pend->createtime == time) {
		tmppend = pend->next;
		pend->next = NULL;
		if (pend->iotype == 0) {
			pend->state = "等待进行A资源的IO";
			if (ioa == NULL) {
				ioa = pend;
				tmpioa = pend;
			}
			else {
				tmpioa->next = pend;
				tmpioa = tmpioa->next;
			}
			pend = tmppend;
		}
		else {
			pend->state = "等待进行B资源的IO";
			if (iob == NULL) {
				iob = pend;
				tmpiob = pend;
			}
			else {
				tmpiob->next = pend;
				tmpiob = tmpiob->next;
			}
			pend = tmppend;
		}
	}
	//ioa或iob执行完io操作的进入ready
		if (ioa != NULL) {
			ioa->neediotime -= 1;
			if (ioa->neediotime == 0) {
				if (ready == NULL) {
					ready = ioa;
					tmpready = ioa;
				}
				ioa = ioa->next;
				ioa->state = "进行A资源IO中";
				tmpready->next = NULL;
			}
		}
		
		if (iob != NULL) {
			iob->neediotime -= 1;
			if (iob->neediotime == 0) {
				if (ready == NULL) {
					ready = iob;
					tmpready = iob;
				}
				iob = iob->next;
				iob->state = "进行B资源IO中";
				tmpready->next = NULL;
			}
		}
		
	//ready里执行完cpu操作的进入finish
		if (ready != NULL) {
			ready->needcputime -= 1;
			if (ready->needcputime == 0) {
				ready->state = "已完成";
				if (finish == NULL) {
					finish = ready;
					tmpfinish = ready;
				}
				else {
					tmpfinish->next = ready;
					tmpfinish = tmpfinish->next;
				}
				tmpfinish->next = NULL;
				ready = ready->next;
			}
		}
PCBPointer* pointer = new PCBPointer(pend, ready, finish, ioa, iob);
return pointer;
}


schedulingService::~schedulingService()
{
}

