#include "stdafx.h"
#include "schedulingService.h"
#include <stdlib.h>


schedulingService::schedulingService()
{
}

void schedulingService::PCBinit(int n, PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob)
{
	PCB* add= pend;
	for (int i = 0; i < n; i++) {
		CString str;
		str.Format(_T("%d"), i);
		int createtime = int(rand() * 15 + 1);
		int needcputime = int(rand() * 15 + 1);
		int neediotime = (int)((needcputime - 1)*rand());
		PCB *pcb = new PCB(_T("进程")+str+ _T("号"),createtime,0,0,0,needcputime,neediotime,(int)(rand()+0.5),_T("等待中"),NULL);
		add->next = pcb;
		add = add->next;
}
}


schedulingService::~schedulingService()
{
}

