#include "ThreadClass.h"
#include "thread.h"
#include "boat-monitor.h"

static BoatMonitor *myMonitor

BoatThread::BoatThread(int boat)
		:boat(boat)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "TheAlmightyBoooaaaattt" << '\0';
	myMonitor = new MyMonitor("TheAlmightBoooaaaattt");
}

CannibalThread::CannibalThread(int id)
	:id(id)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "HungryCannibal[" << id << "]" << '\0';
}

MissionaryThread::MissionaryThread(int id)
	:id(id)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "InnocentMissionary[" << id << "]" << '\0';
}

void BoatThread::ThreadFunc()
{
	char buf[512];
	sprintf(buf, "***** BOAT thread starts\n");
	write(1, buf, strlen(buf));
	
	int totalTrips = boats;
	int currentTrip = 1;
	while(boats)
	{	
		Delay();
//TODO check this part
		sprintf(buf, "***** The boat is ready\n");
		write(1, buf, strlen(buf));
		


	}
}

void CannibalThread::ThreadFunc()
{
	char buf[512];
	sprintf(buf, "%*cCannibal %d starts\n", id, ' ', id);
	write(1, buf, strlen(buf));
	while(1)
	{
		

	}
}

void MissionaryThread::ThreadFunc()
{
	char buf[512];
	sprintf(buf, "%*cMissionary %d starts\n", id, ' ' id);
	write(1, buf, strlen(buf));
	while(1)
	{
		Delay();
		sprintf(buf, %*cMissionary %d arrives\n", id, ' ', id);
		myMonitor->MissionaryArrives(id);


	}

}


