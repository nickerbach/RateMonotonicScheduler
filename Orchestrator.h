#include<iostream>
#include<thread>

#include "Semaphore.h"
#include "Signaler.h"

using namespace std;

#ifndef Orchestrator_H
#define Orchestrator_H

class Orchestrator{
	public:
		Orchestrator(int _runCount);
		~Orchestrator();
		void run();
		void setProcessor(int processor);
		void setPriority(int priority);
		void join();
		Semaphore* mySemaphore;
		Signaler* sig;
	private:
		int runCount;
		thread mainThread;
};

void doWork(int runCount, Semaphore* mySemaphore, Signaler* sig);

#endif
