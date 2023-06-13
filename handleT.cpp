/*
 * handleThread.cpp
 *
 *  Created on: May 12, 2018
 *      Author: OS1
 */

#include "handleT.h"
#include "system.h"

int syncPrintf(const char *format, ...);

HandleThread::HandleThread() : Thread(defaultStackSize, 1) {

	//myPCB->timeSlice=myPCB->startingTime=1;
	//myPCB->stackSize=defaultStackSize;
}

void HandleThread::start(){

	lock();
	myPCB->State=READY;
	myPCB->createStack();
	unlock();


}

void HandleThread::run(){
	while(1) {
		/*for(int i=0;i<32000;i++)
				{
					for (int j = 0; j < 16000; j++);
				}
		syncPrintf("Idle thread\n");*/
	}
}
