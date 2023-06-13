#ifndef _EVENT_H_
#define _EVENT_H_

#include "IVTEntry.h"
#include "thread.h"


#define PREPAREENTRY(ivtno,old) \
void interrupt routine##ivtno(...); \
IVTEntry entry##ivtno(ivtno,routine##ivtno); \
void interrupt routine##ivtno(...) { \
	if (old) entry##ivtno.callOld(); \
	entry##ivtno.signal(); \
	dispatch(); \
}

typedef unsigned char IVTNo;

class KernelEv;

class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();

	void wait ();


protected:
	void signal();
	friend class KernelEv;
private:
	KernelEv* myImpl;

};


#endif
