/*
 * semaphor.h
 *
 *  Created on: May 25, 2018
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include "kerSem.h"

class Semaphore {
public:
	friend class KernelSem;

	Semaphore(int init=1);
	virtual ~Semaphore();

	virtual int wait(int toBlock);
	virtual void signal();

	int val () const;

private:

	KernelSem* myImpl;
};



#endif /* SEMAPHOR_H_ */
