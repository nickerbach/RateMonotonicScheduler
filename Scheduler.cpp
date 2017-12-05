#include "Scheduler.h"

Scheduler::Scheduler() {
	threadSet.push_back(new Orchestrator(1));
	threadSet.push_back(new Orchestrator(2));
	threadSet.push_back(new Orchestrator(4));
	threadSet.push_back(new Orchestrator(16));
}

Scheduler::~Scheduler() {}

void Scheduler::run() {
	threadSet[0]->run();
	threadSet[0]->setProcessor(0);
	threadSet[0]->setPriority(90);
	threadSet[1]->run();
	threadSet[1]->setProcessor(0);
	threadSet[1]->setPriority(80);
	threadSet[2]->run();
	threadSet[2]->setProcessor(0);
	threadSet[2]->setPriority(70);
	threadSet[3]->run();
	threadSet[3]->setProcessor(0);
	threadSet[3]->setPriority(60);

	mainThread = thread(schedule, threadSet, s);
}

void Scheduler::setProcessor(int processor)
{
	//cpu_set_t cpuset;
  //CPU_ZERO(&cpuset);
  //CPU_SET(processor, &cpuset);
  //int rc = pthread_setaffinity_np(mainThread.native_handle(), sizeof(cpu_set_t), &cpuset);
}

void Scheduler::setPriority(int priority) {
	sched_param sch_params;
    sch_params.sched_priority = priority;
    int rc = pthread_setschedparam(mainThread.native_handle(), SCHED_FIFO, &sch_params);
    if (rc) {
    	cout << "Priority switch failed with rc " << rc << endl;
    }
}

void Scheduler::join() {
	mainThread.join();
}

void schedule(vector<Orchestrator*> threadSet, Semaphore* s) {
	int currentTime = -1;
	for (int i = 0; i < 200; ++i)
	{
		currentTime++;
		s->wait();
		if (!threadSet[0]->sig->threadComplete && currentTime != 0)
		{
				threadSet[0]->sig->overrunCount++;
		}
		threadSet[0]->mySemaphore->signal();
		if (currentTime % 2 == 0)
		{
			if (!threadSet[1]->sig->threadComplete && currentTime != 0)
			{
				threadSet[1]->sig->overrunCount++;
			}
			threadSet[1]->mySemaphore->signal();
		}
		if (currentTime % 4 == 0) {
			if (!threadSet[2]->sig->threadComplete && currentTime != 0) {
				threadSet[2]->sig->overrunCount++;
			}
			threadSet[2]->mySemaphore->signal();
		}
		if (currentTime % 16 == 0)
		{
			if (!threadSet[3]->sig->threadComplete && currentTime != 0)
			{
				threadSet[3]->sig->overrunCount++;
			}
			threadSet[3]->mySemaphore->signal();
		}
	}
}
