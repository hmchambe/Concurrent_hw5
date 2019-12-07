//Contains all class definitions of threads

#ifndef _THREAD_STUFF
#define _THREAD_STUFF
#include "ThreadClass.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>


class CannibalThread : public Thread
{
        public:
        // constructor
        CannibalThread(int id);
        private:
        void ThreadFunc();
        int id;
};

class MissionaryThread : public Thread
{
	public:
	// constructor
	MissionaryThread(int id);
	private:
	void ThreadFunc();
	int id;

};

class BoatThread : public Thread
{

	public:
	// constructor
	BoatThread(int boat);

	private:
	void ThreadFunc();
	int boat;
};

#endif
