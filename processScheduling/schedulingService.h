#include "PCB.h"
#include "PCBPointer.h"
#pragma once
class schedulingService
{
public:
	schedulingService();
	PCBPointer* createPCB(int n);
	PCBPointer* FIFO(int time,PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	~schedulingService();
};

