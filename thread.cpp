#include "ThreadClass.h"
#include "thread.h"
#include "boat-monitor.h"

static MyMonitor *myMonitor;

BoatThread::BoatThread(int boat)
		:boat(boat)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "TheAlmightyBoooaaaattt" << '\0';
	myMonitor = new MyMonitor("TheAlmightyBoooaaaattt");
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

void CannibalThread:ThreadFunc()
{
	char buf[512];
	sprintf(buf, "%*cCannibal %d starts\n", id, ' ', id);
	write(1, buf, strlen(buf));
	while(1)
	{
		Delay();

		sprintf(buf, "%*cCannibal %d arrives\n", id, ' ', id);
		write(1, buf, strlen(buf));
		MyMonitor->CannibalArrives(id);
		Delay();
		Delay();
	}
}

void BoatThread::ThreadFunc()
{
	char buffer[512];
	sprintf(buffer, "***** BOAT thread starts\n");
	write(1, buffer, strlen(buffer));
	
	int totalTrips = boat;
	int currentTrip = 1;
	while(boat)
	{	
		Delay();
//TODO check this part
		myMonitor->BoatReady();
		sprintf(buffer, "***** The boat is ready\n***** Boat load (%d): Passenger list (%s)\n***** Boat load (%d): Completed\n", currentTrip, myMonitor->passengerList(), currentTrip);
		write(1, buffer, strlen(buffer));
		Delay();
		myMonitor->BoatDone(totalTrips);
		boat -= 1;
		currentTrip += 1;	
	}
	Exit();
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
	sprintf(buf, "%*cMissionary %d starts\n", id, ' ', id);
	write(1, buf, strlen(buf));
	while(1)
	{
		Delay();
		sprintf(buf, "%*cMissionary %d arrives\n", id, ' ', id);
		myMonitor->MissionaryArrives(id);


	}

}


