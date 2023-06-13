/*
 * queue.h
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#ifndef ALEKS_QUEUE_H_
#define ALEKS_QUEUE_H_

#include <dos.h>
#include "system.h"

class PCB;

class Elem {
		friend class Queue;
		PCB *pcb;
		Elem *next;

		Elem(PCB *pcb);
		~Elem();

};

class Queue{
private:

	Elem *first;
	unsigned length;

public:
	Queue();
	~Queue();

	unsigned getSize();
	void put(PCB *pcb);
	PCB* get();
	void decrementSleepTimeAndRelease();
};

#endif /* ALEKS_QUEUE_H_ */
