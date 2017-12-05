#include<iostream>

using namespace std;

#ifndef Signaler_H
#define Signaler_H

class Signaler {
	public:
		Signaler();
		~Signaler();
		bool threadComplete;
		int overrunCount;
		int counter;
	private:
};

#endif
