#include <iostream>
#include <vector>

#include "Orchestrator.h"

using namespace std;

#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler{
	public:
		Scheduler();
		~Scheduler();
		void run();
		void setProcessor(int processor);
		void setPriority(int priority);
		void join();
		Semaphore* s;
		int* currentTime;
		vector<Orchestrator*> threadSet;
	private:
		thread mainThread;
};

void schedule(vector<Orchestrator*> threadSet, Semaphore* s);

#endif
