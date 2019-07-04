#pragma once
#include "PCB.h"
class PCBPointer
{
	PCB* pend;
	PCB* ready;
	PCB* finish;
	PCB* ioa;
	PCB* iob;
public:
	PCBPointer(PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	~PCBPointer();
};

