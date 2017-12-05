#include "Orchestrator.h"


Orchestrator::Orchestrator(int x) {
	runCount = x;
	mySemaphore = new Semaphore(0);
	sig = new Signaler();
}

Orchestrator::~Orchestrator() {}

void Orchestrator::run() {
	mainThread = thread(doWork, runCount, mySemaphore, sig);
}

void Orchestrator::setProcessor(int processor) {
	//cpu_set_t cpuset;
    //CPU_ZERO(&cpuset);
    //CPU_SET(processor, &cpuset);
    //int rc = pthread_setaffinity_np(mainThread.native_handle(), sizeof(cpu_set_t), &cpuset);
}

void Orchestrator::setPriority(int threadPriority) {
	sched_param sch_params;
    sch_params.sched_priority = threadPriority;
    int rc = pthread_setschedparam(mainThread.native_handle(), SCHED_FIFO, &sch_params);
    if (rc) {
    	cout << "Your priority switched failed with rc " << rc << endl;
    }
}

void Orchestrator::join() {
	mainThread.join();
}

void doWork(int runCount, Semaphore* s, Signaler* sign) {
	for (int j = 0; j < 32; ++j){
		s->wait();
		sign->threadComplete = false;
		sign->counter++;
		for (int x = 0; x < runCount; ++x)
		{
			int** arr = new int*[10];

			for (int row = 0; row < 10; ++row)
			{
				arr[row] = new int[10];
				for (int column = 0; column < 10; ++column)
				{
					arr[row][column] = 3;
				}
			}

			int cols[10] = {0,5,1,6,2,7,3,8,4,9};

			for (int i = 0; i < 10; ++i)
			{
				int col = cols[i];
				for (int j = 0; j < 10; ++j)
				{
					arr[1][i] = arr[1][i] * arr[j][i];
				}
			}
		}
		sign->threadComplete = true;
	}
}
