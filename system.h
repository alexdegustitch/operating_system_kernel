/*
 * system.h
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#ifndef ALEKS_SYSTEM_H_
#define ALEKS_SYSTEM_H_

#include "thread.h"
#include "handleT.h"
#include "pcb.h"
#include "queue.h"
#include <dos.h>
#include <iostream.h>

typedef void (interrupt *InterruptRoutine)(...);

#define lockasm() {asm{pushf; cli;}}
#define unlockasm() {asm{popf}}

class Queue;

extern volatile unsigned lockFlag;


class System{
private:
	static volatile int counter;
	static unsigned dispatchFlag;//static volatile char dispatched;
	//static unsigned lockFlag;//bez zabrane prekida

	static Thread *startingThread;
	static HandleThread *handler;
	static volatile PCB* running;
	static Queue *sleepQueue;
	static Queue *blockedSem;

	static void interrupt timer(...);
	static void wrapper();
	static void interrupt (*oldRoutine)(...);

protected:
	friend class PCB;
	friend class Thread;
	friend class KernelSem;
	friend class KernelEv;
	friend class Semaphore;
	friend class Queue;
	friend class IVTEntry;
	friend class HandleThread;
	friend class Event;
public:
	static void start();
	static void stop();
	static void myDispatch();

};

#define lock() {lockFlag = 0;}
#define unlock() {lockFlag=1; if (System::dispatchFlag) dispatch();}


#endif /* ALEKS_SYSTEM_H_ */
