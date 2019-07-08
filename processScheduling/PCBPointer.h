#pragma once
#include "PCB.h"
class PCBPointer
{
public:
	//预备队列
	PCB* pend;
	//就绪队列
	PCB* ready;
	//完成队列
	PCB* finish;
	//等待ioa队列
	PCB* ioa;
	//等待iob队列
	PCB* iob;
	int cpuratio;
	int ioaratio;
	int iobratio;
	PCBPointer();
	PCBPointer(PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	~PCBPointer();
};

