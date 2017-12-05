#include <iostream>
#include <thread>

#include "Semaphore.h"
#include "Orchestrator.h"
#include "Scheduler.h"
#include "Timer.h"

using namespace std;


int main() {
	cout<<"Threads are being executed."<< endl;
	Semaphore* sema = new Semaphore(0);
	Scheduler sched;
	sched.s = sema;
	sched.run();
	sched.setPriority(99);
	sched.setProcessor(0);
	Timer time;
	sched.s = sema;
	time.s = sema;
	time.run();
	int total = sched.threadSet[0]->sig->counter + sched.threadSet[1]->sig->counter + sched.threadSet[2]->sig->counter + sched.threadSet[3]->sig->counter;
	sched.join();
	cout<< "The threads ran a total of "<<total<<" times."<<endl;
	cout<< "Thread 0 ran "<< sched.threadSet[0]->sig->counter << " times."<< endl;
	cout<< "Thread 0 had "<< sched.threadSet[0]->sig->overrunCount << " overruns."<< endl;

	cout<< "Thread 1 ran "<< sched.threadSet[1]->sig->counter << " times."<< endl;
	cout<< "Thread 1 had "<< sched.threadSet[1]->sig->overrunCount << " overruns."<< endl;

	cout<< "Thread 2 ran "<< sched.threadSet[2]->sig->counter << " times."<< endl;
	cout<< "Thread 2 had "<< sched.threadSet[2]->sig->overrunCount << " overruns."<< endl;

	cout<< "Thread 3 ran "<< sched.threadSet[3]->sig->counter << " times."<< endl;
	cout<< "Thread 3 had "<< sched.threadSet[3]->sig->overrunCount << " overruns."<< endl;
	return 0;
}
