#include "PCB.h"
#include "PCBPointer.h"
#pragma once
class schedulingService
{
public:
	schedulingService();
	void PCBinit(int n,PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	PCBPointer FIFO(int time,PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	~schedulingService();
};

