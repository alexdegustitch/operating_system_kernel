/*
 * thread.cpp
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#include "thread.h"
#include "queue.h"
#include "SCHEDULE.H"
#include "system.h"
#include <dos.h>
#include <stdlib.h>


Thread::Thread(StackSize stackSize, Time timeSlice){
	lock();
	myPCB=new PCB(this, stackSize, timeSlice);
	unlock();
}

void Thread::start(){

	lock();
	myPCB->createStack();
	myPCB->State=READY;
	Scheduler::put(myPCB);
	unlock();

}

void Thread::run() {}

Thread::~Thread(){

	waitToComplete();
	lock();
	//unlock();
	delete myPCB;
	unlock();
}

void dispatch(){
	//lock();
	System::myDispatch();
	//unlock();
}

void Thread::waitToComplete(){
	lock();
	if (myPCB->State==OVER || myPCB->State==NEW){unlock();return;}
	if (myPCB==(PCB*)System::running){unlock();return;}
	if (this==System::startingThread){unlock();return;}
	if(this==System::handler){unlock();return;}

	System::running->State=BLOCKED;
	myPCB->blockedPCB->put((PCB*)System::running);

	unlock();
	System::myDispatch();



}

void Thread::sleep(Time timeToSleep) {
	lock();
	System::running->State = BLOCKED;
	System::running->sleepTime = timeToSleep;
	System::sleepQueue->put((PCB*)System::running);
	unlock();
	dispatch();

}
