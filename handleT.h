/*
 * handleThread.h
 *
 *  Created on: May 12, 2018
 *      Author: OS1
 */

#ifndef ALEKS_HANDLET_H_
#define ALEKS_HANDLET_H_

#include "thread.h"

class System;

class HandleThread :public Thread{
public:

	void start();
	HandleThread();
	virtual void run();
	friend class System;
};

#endif /* ALEKS_HANDLET_H_ */
