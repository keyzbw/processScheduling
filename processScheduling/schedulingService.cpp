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

void schedulingService::FIFO(int time, PCBPointer& PP)
{
	PCB * tmppend = PP.pend;
	//ready尾指针
	PCB * tmpready = PP.ready;
	while (tmpready->next != NULL) {
		tmpready = tmpready->next;
	}
	//ioa尾指针
	PCB * tmpioa = PP.ioa;
	while (tmpioa->next != NULL) {
		tmpioa = tmpioa->next;
	}
	//iob尾指针
	PCB * tmpiob = PP.iob;
	while (tmpiob->next != NULL) {
		tmpiob = tmpiob->next;
	}
	//finish尾指针
	PCB * tmpfinish = PP.finish;
	while (tmpfinish->next != NULL) {
		tmpfinish = tmpfinish->next;
	}
	//pend到时间的加入ioa或iob
	while (PP.pend!=NULL && PP.pend->createtime == time) {
		tmppend = PP.pend->next;
		PP.pend->next = NULL;
		if (PP.pend->iotype == 0) {
			PP.pend->state = "等待进行A资源的IO";
			tmpioa->next = PP.pend;
			PP.pend = tmppend;
			tmpioa = tmpioa->next;
		}
		else {
			PP.pend->state = "等待进行B资源的IO";
			tmpiob->next = PP.pend;
			PP.pend = tmppend;
			tmpiob = tmpiob->next;
		}
	//ioa或iob执行完io操作的进入ready
		PP.ioa->neediotime -= 1;
		if (PP.ioa->neediotime == 0) {
			tmpready->next = PP.ioa;
			tmpready = tmpready->next;
			PP.ioa = PP.ioa->next;
			PP.ioa->state = "进行A资源IO中";
			tmpready->next = NULL;
		}
		PP.iob->neediotime -= 1;
		if (PP.iob->neediotime == 0) {
			tmpready->next = PP.iob;
			tmpready = tmpready->next;
			PP.iob = PP.iob->next;
			PP.iob->state = "进行B资源IO中";
			tmpready->next = NULL;
		}
	//ready里执行完cpu操作的进入finish
		PP.ready->needcputime -= 1;
		if (PP.ready->needcputime == 0) {
			PP.ready->state = "已完成";
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

