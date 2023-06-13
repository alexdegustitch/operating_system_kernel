/*
 * thread.h
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#ifndef ALEKS_THREAD_H_
#define ALEKS_THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time;
const Time defaultTimeSlice=2;
typedef int ID;

class PCB;

class Thread {
public:

	void start();
	void waitToComplete();
	virtual ~Thread();

	static void sleep(Time timeToSleep);

protected:

	friend class PCB;
	friend class System;
	friend class HandleThread;
	Thread(StackSize stackSize =defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run();

private:
	PCB *myPCB;
};

void dispatch();

#endif /* ALEKS_THREAD_H_ */
