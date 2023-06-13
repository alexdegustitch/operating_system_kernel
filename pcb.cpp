/*
 * pcb.cpp
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#include "pcb.h"

PCB::PCB(Thread* myThread, StackSize stackSize, Time timeSlice){

	//lock();
	this->myThread=myThread;
	myThread->myPCB=this;
	State=NEW;
	this->stackSize=stackSize;
	this->timeSlice=this->startingTime=timeSlice;
	sleepTime = 0;
	stack=0;
	blockedPCB = new Queue();
	//unlock();


}

PCB::~PCB(){
	//lock();
	delete stack;
	delete blockedPCB;
	//unlock();
}

Time PCB::getTime(){
	return timeSlice;
}


void PCB::createStack(){

	//lock();
	//proveri u odn. na lab
	static int n=this->stackSize/2;
	this->stack=new unsigned[n];
	this->stack[n-1]=0x200;
	this->stack[n-2]=FP_SEG(&(System::wrapper));
	this->stack[n-3]=FP_OFF(&(System::wrapper));

	this->sp=FP_OFF(this->stack+n-12);
	this->ss=FP_SEG(this->stack+n-12);

	//unlock();

}
