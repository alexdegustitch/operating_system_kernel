/*
 * IVTEntry.h
 *
 *  Created on: May 30, 2018
 *      Author: OS1
 */

#include "kerEv.h"
#include "system.h"

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

class IVTEntry {
	friend class KernelEv;
private:
	static IVTEntry* IVTTable[256];

	unsigned ivtNo;
	KernelEv* myEvent;
	void interrupt (*oldIR)(...);

public:
	IVTEntry(int,void interrupt(*)(...));
   ~IVTEntry();
	void signal();
	void callOld();
	void setEvent(KernelEv *);
	void removeEvent();
};



#endif /* IVTENTRY_H_ */
