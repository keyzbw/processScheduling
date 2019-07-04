#pragma once
#include "PCB.h"
class PCBPointer
{
public:
	PCBPointer();
	PCBPointer(PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	~PCBPointer();
	PCB* pend;
	PCB* ready;
	PCB* finish;
	PCB* ioa;
	PCB* iob;
};

