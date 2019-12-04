//Contains all class definitions of threads

#ifndef THREAD_STUFF
#define THREAD_STUFF
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "thread-support.h"


class CannibalThread : public Thread
{
        public:
        // constructor
        ElfThread(int id);
        private:
        void ThreadFunc();
        int id;
};

class MissionaryThread : public Thread
{
	public:
	// constructor

	private:
	void ThreadFunc();


};

class BoatThread : public Thread
{

	public:
	// constructor

	private:
	void ThreadFunc();

};
