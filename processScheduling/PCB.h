#pragma once
#include <String>
using namespace std;
class PCB
{
public:
	//������
	CString name;
	//����ʱ��
	int createtime;
	//���ȼ�orʱ��Ƭʱ��
	int prio_round;
	//��ռ��CPUʱ�䣨���Σ�
	int cputime;
	//������
	int count;
	//����ҪCPUִ�е�ʱ��
	int needcputime;
	//����ҪIOִ��ʱ��
	int neediotime;
	//��ռ�õ�IO��Դ���ͣ�A��B��
	int iotype;
	//Ŀǰ״̬
	CString state;
	//ָ����һ����״̬��PCB
	PCB* next;


	PCB(CString name, int createtime, int prio_round, int cputime, int count, int needcputime, int neediotime, int iotype, CString state, PCB* next);
	PCB();
	~PCB();
};
