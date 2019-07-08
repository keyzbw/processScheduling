#pragma once
#include <String>
using namespace std;
class PCB
{
public:
	//进程名
	CString name;
	//生成时间
	int createtime;
	//优先级
	int prio_round;
	//时间片时长
	int timeSlice;
	//已占用CPU时间（本次）
	int cputime;
	//计数器
	int count;
	//还需要CPU执行的时间
	int needcputime;
	//还需要IO执行时间
	int neediotime;
	//所占用的IO资源类型（A或B）
	int iotype;
	//目前状态
	CString state;
	//指向下一个该状态的PCB
	PCB* next;


	PCB(CString name, int createtime, int prio_round, int timeSlice, int cputime, int count, int needcputime, int neediotime, int iotype, CString state, PCB* next);
	PCB();
	~PCB();
};

