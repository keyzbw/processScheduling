#pragma once
#include "PCB.h"
class PCBPointer
{
public:
	PCB* pend;
	PCB* ready;
	PCB* finish;
	PCB* ioa;
	PCB* iob;
	int cpuratio;
	int ioaratio;
	int iobratio;
	PCBPointer();
	PCBPointer(PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob,int cpuratio,int ioaratio,int iobratio);
	~PCBPointer();
};

