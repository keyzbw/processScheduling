#include "PCB.h"
#include "PCBPointer.h"
#pragma once
class schedulingService
{
public:
	schedulingService();
	PCBPointer* createPCB(int n);
	void FIFO(int time,PCBPointer* PP);
	~schedulingService();
};

