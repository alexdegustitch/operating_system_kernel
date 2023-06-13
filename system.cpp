/*
 * system.cpp
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */


#include "system.h"
#include "thread.h"
#include "SCHEDULE.H"
#include <dos.h>

void tick(); //prototip

void interrupt (*System::oldRoutine)(...) = NULL;

volatile int System::counter=0;
unsigned System::dispatchFlag=0;//static volatile char dispatched;
volatile unsigned lockFlag=1;//bez zabrane prekida

Thread *System::startingThread = 0;
HandleThread *System::handler = 0;
volatile PCB* System::running = 0;

Queue *System::sleepQueue = new Queue();
Queue *System::blockedSem = new Queue();

void interrupt System::timer(...){
	static unsigned tsp, tss;
	static PCB* newPCB;

	if(!dispatchFlag){
		tick();
		(*oldRoutine)();
	}

	if (!dispatchFlag)  System::sleepQueue->decrementSleepTimeAndRelease();

	if(!dispatchFlag && running->timeSlice != 0)
		running->startingTime--;

	if (!dispatchFlag && (running->startingTime > 0 || running->timeSlice == 0) ) return;

	if (lockFlag) {
		dispatchFlag=0;

		if(running->State==READY && running!=handler->myPCB)
			Scheduler::put((PCB*)running);

			 newPCB = Scheduler::get();
			 if(newPCB==0)
				 newPCB=handler->myPCB; //jel onda newThread treba da bude tipa Thread

			 asm{
				 mov tsp, sp
				 mov tss, ss

			 }

			 running->sp=tsp;
			 running->ss=tss;
			 running=newPCB;
			 tsp=running->sp;
			 tss=running->ss;

			 asm{
				 mov sp, tsp
				 mov ss, tss
			 }

			running->startingTime = running->timeSlice;
	} else {
		dispatchFlag = 1;
	}
}

void System::wrapper(){

	running->myThread->run();

	lock();
	running->State=OVER;
	PCB *temp;
	while(running->blockedPCB->getSize()>0){

		temp=running->blockedPCB->get();
		temp->State=READY;
		Scheduler::put(temp);

	}
	unlock();
	dispatch();
}

void System::myDispatch(){
	//lock();
	dispatchFlag=1;
	timer();
	//dispatchFlag=0;
	//unlock();
}

void System::start(){

	lockasm();

	oldRoutine=getvect(0x08);
	setvect(0x08, timer);
	startingThread=new Thread(defaultStackSize, 1);
	startingThread->myPCB->State=READY;
	running=(volatile PCB*)startingThread->myPCB;
	handler=new HandleThread();
	handler->start();

	unlockasm();
}

void System::stop(){
	lockasm();
	setvect(0x08, oldRoutine);
	unlockasm();
	delete startingThread;
	delete handler;
}

