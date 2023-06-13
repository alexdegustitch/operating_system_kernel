/*
 * semaphor.cpp
 *
 *  Created on: May 25, 2018
 *      Author: OS1
 */

#include "kerSem.h"
#include "semaphor.h"

int Semaphore::val() const{
	return myImpl->val;
}

Semaphore::Semaphore(int init){
	lock();
	myImpl = new KernelSem(init, this);
	unlock();
}

Semaphore::~Semaphore(){
	lock();
	delete myImpl;
	unlock();
}
int Semaphore::wait(int toBlock){
	lock();
	int ret = myImpl->wait(toBlock);
	unlock();
	return ret;
}

void Semaphore::signal(){
	lock();
	myImpl->signal();
	unlock();
}

