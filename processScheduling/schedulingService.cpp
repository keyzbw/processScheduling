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

void schedulingService::FIFO(int time, PCB * pend, PCB * ready, PCB * finish, PCB * ioa, PCB * iob)
{
	PCB * tmppend = pend;
	PCB * tmpready = ready;
	PCB * tmpioa = ioa;
	PCB * tmpiob = iob;
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
	//ready里执行完cpu操作的进入finish
	}
}


schedulingService::~schedulingService()
{
}

