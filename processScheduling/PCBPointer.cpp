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
	PCB* tmp;
	while (pend != NULL) {
		tmp = pend;
		pend = pend->next;
		delete tmp;
	}
	while (ready != NULL) {
		tmp = ready;
		ready = ready->next;
		delete tmp;
	}
	while (ioa != NULL) {
		tmp = ioa;
		ioa = ioa->next;
		delete tmp;
	}
	while (iob != NULL) {
		tmp = iob;
		iob = iob->next;
		delete tmp;
	}
	while (finish != NULL) {
		tmp = finish;
		finish = finish->next;
		delete tmp;
	}
}
