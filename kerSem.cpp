/*
 * kerSem.cpp
 *
 *  Created on: May 25, 2018
 *      Author: OS1
 */

#include "kerSem.h"
#include "queue.h"
#include "pcb.h"
#include "semaphor.h"
#include "system.h"
#include "SCHEDULE.H"



KernelSem::KernelSem(int init, Semaphore *mySem) {
	//lock();
	val=init;
    this->mySem=mySem;
    mySem->myImpl=this;
    //unlock();
}

KernelSem::~KernelSem(){
	while (val < 0) signal();
}

int KernelSem::wait(int toBlocked){
	//lock();

	int ret = 0;
	if(!toBlocked && val<=0) {
		ret = -1;

	}
	else if (--val<0) {
		ret = 1;
		((PCB*)System::running)->State=BLOCKED;
		System::blockedSem->put((PCB*)System::running);


		System::myDispatch();
	}
	//unlock();
	return ret;
}

void KernelSem::signal(){

	//lock();
	val++;
	if(val<=0){
		PCB *temp = System::blockedSem->get();
		temp->State=READY;
		Scheduler::put(temp); //Scheduler::put((PCB*)System::blockedSem->get()->State=READY);
	}

	//unlock();

}

int KernelSem::getVal() const { return val; }


