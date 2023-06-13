/*
 * kerSem.h
 *
 *  Created on: May 25, 2018
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_
#include "queue.h"
#include "semaphor.h"

class Queue;
class PCB;

class KernelSem {
public:
	friend class Semaphore;
	friend class PCB;

	KernelSem(int init, Semaphore *mySem);
	~KernelSem();

	int wait(int toBlock);
	void signal();

	int getVal () const;

private:
	Semaphore *mySem;
    int val;
};




#endif /* KERSEM_H_ */
