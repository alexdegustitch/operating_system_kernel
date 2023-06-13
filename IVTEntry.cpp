/*
 * IVTEntry.cpp
 *
 *  Created on: May 30, 2018
 *      Author: OS1
 */
#include "IVTEntry.h"
#include <dos.h>
#include "system.h"
#include "kerEv.h"

IVTEntry* IVTEntry::IVTTable[256];

IVTEntry::IVTEntry(int ivtNo,void interrupt (*newIR)(...)) {

	myEvent = 0;
	this->ivtNo=ivtNo;
	IVTTable[ivtNo]=this;
	lockasm();
		oldIR = getvect(ivtNo);
		setvect(ivtNo, newIR);
	unlockasm();
}

IVTEntry::~IVTEntry() {
	lockasm();
	setvect(ivtNo, oldIR);
	unlockasm();
	oldIR();
}
void IVTEntry::signal() {
	if (myEvent) myEvent->signal();
}
void IVTEntry::callOld() {
	//lock();
	oldIR();
	//unlock();
}

void IVTEntry::setEvent(KernelEv *kev) {
	//lock();
	myEvent = kev;
	//unlock();
}

void IVTEntry::removeEvent() {
	//lock();
	myEvent = 0;
	//unlock();
}



