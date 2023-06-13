/*
 * main.cpp
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#include "thread.h"
#include "queue.h"
#include "system.h"

int userMain(int argc, char *argv[]);

int main(int argc, char *argv[]) {

	System::start();
	int x = userMain(argc, argv);
	System::stop();
	return x;
}
