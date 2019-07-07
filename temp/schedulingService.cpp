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
		PCB *pcb = new PCB(_T("进程")+str+ _T("号"),createtime,0,0,0,needcputime,neediotime,(int)(rand()+0.5),_T("等待中"),NULL);
		add->next = pcb;
		add = add->next;
}
}

PCBPointer schedulingService::FIFO(int time, PCB * pend, PCB * ready, PCB * finish, PCB * ioa, PCB * iob)
{
	PCB * tmppend = pend;
	//ready尾指针
	PCB * tmpready = ready;
	while (tmpready->next != NULL) {
		tmpready = tmpready->next;
	}
	//ioa尾指针
	PCB * tmpioa = ioa;
	while (tmpioa->next != NULL) {
		tmpioa = tmpioa->next;
	}
	//iob尾指针
	PCB * tmpiob = iob;
	while (tmpiob->next != NULL) {
		tmpiob = tmpiob->next;
	}
	//finish尾指针
	PCB * tmpfinish = finish;
	while (tmpfinish->next != NULL) {
		tmpfinish = tmpfinish->next;
	}
	//pend到时间的加入ioa或iob
	while (pend!=NULL && pend->createtime == time) {
		tmppend = pend->next;
		pend->next = NULL;
		if (pend->iotype == 0) {
			pend->state = "等待进行A资源的IO";
			tmpioa->next = pend;
			pend = tmppend;
			tmpioa = tmpioa->next;
		}
		else {
			pend->state = "等待进行B资源的IO";
			tmpiob->next = pend;
			pend = tmppend;
			tmpiob = tmpiob->next;
		}
	//ioa或iob执行完io操作的进入ready
		ioa->neediotime -= 1;
		if (ioa->neediotime == 0) {
			tmpready->next = ioa;
			tmpready = tmpready->next;
			ioa = ioa->next;
			ioa->state = "进行A资源IO中";
			tmpready->next = NULL;
		}
		iob->neediotime -= 1;
		if (iob->neediotime == 0) {
			tmpready->next = iob;
			tmpready = tmpready->next;
			iob = iob->next;
			iob->state = "进行B资源IO中";
			tmpready->next = NULL;
		}
	//ready里执行完cpu操作的进入finish
		ready->needcputime -= 1;
		if (ready->needcputime == 0) {
			ready->state = "已完成";
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

