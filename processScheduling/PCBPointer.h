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
	PCBPointer();
	PCBPointer(PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	~PCBPointer();
};

