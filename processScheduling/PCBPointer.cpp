#include "stdafx.h"
#include "PCBPointer.h"


PCBPointer::PCBPointer()
{
}


PCBPointer::PCBPointer(PCB * pend, PCB * ready, PCB * finish, PCB * ioa, PCB * iob)
{
	this->pend = pend;
	this->ready = ready;
	this->finish = finish;
	this->ioa = ioa;
	this->iob = iob;
	this->cpuratio = 0;
	this->ioaratio = 0;
	this->iobratio = 0;
}

PCBPointer::~PCBPointer()
{
}
