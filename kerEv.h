/*
 * kerEv.h
 *
 *  Created on: May 30, 2018
 *      Author: OS1
 */

#ifndef KEREV_H_
#define KEREV_H_

typedef unsigned char IVTNo;

class Thread;
class PCB;
class Semaphore;

class KernelEv {
public:
	KernelEv (IVTNo ivtNo);
	~KernelEv ();
	void wait ();
	void signal();
private:
	IVTNo ivtNo;
	Thread* owner;
	Semaphore *mySem;
};

#endif /* KEREV_H_ */
