/*
 * queue.cpp
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#include "queue.h"
#include <stdlib.h>
#include "system.h"
#include "SCHEDULE.H"


Elem::Elem(PCB* pcb): next(0){

	this->pcb=pcb;
}

Elem::~Elem(){}

Queue::Queue() {
	//lock();
	first=0;
	length=0;
	//unlock();
}

Queue::~Queue() {
	//lock();
	Elem *old;
	while(first){
		old=first;
		first=first->next;
		old->pcb->State = READY;
		Scheduler::put(old->pcb);
		delete old;
	}
	//unlock();
}

unsigned Queue::getSize(){
	return length;
}

void Queue::put(PCB *pcb){
	//lock();
	Elem *new_elem = new Elem(pcb);

	/*if(first==0)
		first=last=new_elem;
	else
	{
		last->next=new_elem;
		last=new_elem;
	}*/
	new_elem->next=0;
	if(!first)
		first=new_elem;
	else{
		Elem *temp = first;
		for(temp=first;temp->next!=0;temp=temp->next);
		temp->next=new_elem;
	}

	length++;
	//unlock();
}

PCB* Queue::get(){
	//lock();
	if (first == 0) { /*unlock();*/ return 0; }
	/*Elem *temp=first;
	PCB *result = temp->pcb;
	first=temp->next;
	if (first == 0) last = 0;
	length--;
	delete temp;
	unlock();
	return result;*/

	Elem *temp=first;
	if(first->next==0)
		first=0;
	else
		first=first->next;
	length--;
	PCB *result = temp->pcb;
	delete temp;
	//unlock();
	return result;


}

void Queue::decrementSleepTimeAndRelease() {
	//lock();
	if (first == 0) { /*unlock();*/ return; }

	Elem *curr = first;
	Elem *pred = 0;
	Elem *old;

	while(curr){
		curr->pcb->sleepTime--;
		if(curr->pcb->sleepTime>0){
			pred=curr;
			curr=curr->next;
		}
		else{
			old=curr;
			curr=curr->next;
			if(!pred)
				first=curr;
			else
				pred->next=curr;

			PCB *myPCB = old->pcb;
			myPCB->State = READY;
			Scheduler::put(myPCB);
			length--;
			delete old;
		}
	}
	/*while (curr) {
		curr->pcb->sleepTime--;

		if (curr->pcb->sleepTime > 0) {
			pred = curr;
			curr = curr->next;
		} else {
			old = curr;

			PCB *myPCB = old->pcb;
			myPCB->State = READY;
			Scheduler::put(myPCB);

			curr = curr->next;
			if (!pred) {
				if (first == last) first = last = curr;
				else first = curr;
			} else {
				pred->next = curr;
				if (curr == last) last = pred;
			}
			delete old;
		}
	}*/

	//unlock();
}















