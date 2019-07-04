#include "PCB.h"
#pragma once
class schedulingService
{
public:
	schedulingService();
	void PCBinit(int n,PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	void FIFO(int time,PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	~schedulingService();
};

