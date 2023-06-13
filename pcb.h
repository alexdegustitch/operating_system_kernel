/*
 * pcb.h
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#ifndef ALEKS_PCB_H_
#define ALEKS_PCB_H_
#include "thread.h"
#include "queue.h"

enum state {READY, NEW, OVER, BLOCKED};

class Queue;

class PCB{
public:
	PCB(Thread*, StackSize, Time);
	~PCB();

	Time getTime();

	friend class Thread;
	friend class HandleThread;
	friend class System;
	friend class Queue;
	friend class KernelSem;
	friend class KernelEv;
	void createStack();

private:
	Queue *blockedPCB;
	unsigned sp, ss;
	Time timeSlice;
	Time startingTime;
	Time sleepTime;
	unsigned *stack;
	unsigned stackSize;
    volatile state State;
    Thread* myThread;
};




#endif /* ALEKS_PCB_H_ */
