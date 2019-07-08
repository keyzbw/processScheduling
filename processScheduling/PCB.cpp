#include "stdafx.h"
#include "PCB.h"


PCB::PCB(CString name, int createtime, int prio_round,int timeSlice,int cputime, int count, int needcputime, int neediotime, int iotype, CString state, PCB * next)
{
	this->name = name;
	this->createtime = createtime;
	this->prio_round = prio_round;
	this->timeSlice = timeSlice;
	this->cputime = cputime;
	this->count = count;
	this->needcputime = needcputime;
	this->neediotime = neediotime;
	this->iotype = iotype;
	this->state = state;
	this->next = next;
}

PCB::PCB()
{
}


PCB::~PCB()
{
}
