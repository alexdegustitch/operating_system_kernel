#include "event.h"
#include "kerEv.h"
#include "system.h"
#include "IVTEntry.h"
#include "kerSem.h"

Event::Event (IVTNo ivtNo) {
	lock();
	myImpl = new KernelEv(ivtNo);
	unlock();
}
Event::~Event () {
	lock();
	delete myImpl;
	unlock();
}
void Event::wait () {
	lock();
	myImpl->wait();
	unlock();
}
void Event::signal() {
	//lock();
	myImpl->signal();
	//unlock();
}

KernelEv::KernelEv (IVTNo ivtNo) {
	//if(IVTEntry::IVTTable[ivtNo]) {
		owner = System::running->myThread;
		this->ivtNo=ivtNo;
		this->mySem = new Semaphore(0);
		IVTEntry::IVTTable[ivtNo]->setEvent(this);
	//}
}
KernelEv::~KernelEv () {
	//if(IVTEntry::IVTTable[ivtNo]) {
	//lock();
		IVTEntry::IVTTable[ivtNo]->removeEvent();
		delete mySem;
	//unlock();
	//}
}
void KernelEv::wait () {
	//if(IVTEntry::IVTTable[ivtNo]) {
		if (System::running->myThread != owner) return;
		//lock();
		mySem->wait(0);
		//unlock();
//	}
}

void KernelEv::signal() {
	lock();
	//if(IVTEntry::IVTTable[ivtNo]) {
		if (mySem->val() == 1) { unlock(); return; }
		mySem->signal();
	//}
	unlock();
}


