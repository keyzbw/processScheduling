#pragma once
#include "PCB.h"
class PCBPointer
{
public:
	//Ԥ������
	PCB* pend;
	//��������
	PCB* ready;
	//��ɶ���
	PCB* finish;
	//�ȴ�ioa����
	PCB* ioa;
	//�ȴ�iob����
	PCB* iob;
	int cpuratio;
	int ioaratio;
	int iobratio;
	PCBPointer();
	PCBPointer(PCB* pend, PCB* ready, PCB* finish, PCB* ioa, PCB* iob);
	~PCBPointer();
};

