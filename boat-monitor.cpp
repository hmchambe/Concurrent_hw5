#include "ThreadClass.h"

// COMPLETE
MyMonitor::MyMonitor(char *Name)
	: Monitor(Name, HOARE)
{
	srand(time(NULL));
	isMissionarySafe = false;
	boarded = false;
	boatReady = false;
	trip = 0;
	passengerAmount = 0;
	canniblesWaiting = 0;
	CannibalLine = new Condition("Hungry");
	missionariesWaiting = 0;
	MissionaryLine = new Condition("Innocent");
	BoatLine = new Condition("OnBoat");
	passengerNumber = new int[3];
	passengerRole = new int [3];

	passengerNumber[0] = 2;
	passengerNumber[1] = 2;
	passengerNumber[2] = 2;
	passengerRole[0] = 2;
	passengerRole[1] = 2;
	passengerRole[2] = 2;
}

// COMPLETE
bool MyMonitor::isMissionarySafe()
{
	return isMissionarySafe;
}

// COMPLETE
void MyMonitor::BoatReady()
{
	MonitorBegin();
	
	int i, j, selectedIndex, placeholder;
	int options[] = {2, 0, 1};
	for(i=0; i<=2; i++)
	{
		// Randomization process
		placeholder = options[i]
		selectedIndex = rand() % 3;
		options[i] = options[selectedIndex];
		options[selectedIndex] = placeholder;
		// Choosing how to fill boat, while not allowing missionaries to be eaten
		switch(options[i])
		{
			case 0:
				if(missionaryWaiting >= 3)
				{
					for(j=0; j<3; j++)
					{
						MissionaryLine->Signal();
					}
					sprintf(buffer, "MONITOR(%d): Three missionaries are selected (%d, %d, %d)\n", trip+1, passengerNumber[0], passengerNumber[1], passengerNumber[2]);
				}
				break;
			case 1:
				for(j=0; j<2; j++)
				{
					MissionaryLine->Signal();
				}
				CannibalLine->Signal();
				int cannibal = 1, firstMiss = 0, secondMiss = 2;
				if(passengerRole[0] == 0)
				{
					cannibal = 0;
					firstMiss = 1;
					secondMiss = 2;
				}else if(passengerRole[1] == 0)
				{
					firstMiss = 0;
					secondMiss = 1;
					cannibal = 2;
				}
				sprintf(buffer, "MONITOR(%d): Two Missionaries (%d, %d) and one cannibal (%d) are selected\n", trip+1, passengerNumber[firstMiss], passengerNumber[secondMiss], passengerNumber[cannibal]);
				break;
			default:
				for(j=0; j<3; j++)
				{
					CannibalLine->Signal();
				}
				sprintf(buffer, "MONITOR(%d): Three cannibals are selected (%d, %d, %d)\n", trip+1, passengerNumber[0], passengerNumber[1], passengerNumber[2]);
				break;
		}
		write(1, buffer, strlen(buffer));
	}
	MonitorEnd();

}

// COMPLETE
void MyMonitor::BoatDone(int totalTrips)
{
	MonitorBegin();
	int i;
	char buffer[512];
	for(i=0; i<3; i++)
	{		
		BoatLine->Signal();
	}
	trip++;
	if(!(totalTrips - trip))
	{
		boatReady = false;
		while(missionariesWaiting)
		{
			MissionaryLine->Signal();
			missionariesWaiting--;
		}		
		while(cannibalsWaiting)
		{
			CannibalLine->Signal();
			cannibalsWaiting--;
		}
		sprintf(buffer, "MONITOR: %d crosses have been made\nMONITOR: This river cross is closed indefinitely for renovation\n", trip);
		write(1, buffer, strlen(buffer));
	}
	MonitorEnd();
}

void MyMonitor::MissionaryArrives(int missionaryName)
{
	MonitorBegin();
	if(!boatReady)
	{	//Boat is not ready for any reason
		MonitorEnd();
		return;
	}
	missionariesWaiting += 1;

	if(!isMissionarySafe) isMissionarySafe = true;
	MissionaryLine->Wait();
	if(!boatReady)
	{
		MonitorEnd()
		return;
	}	
	missionariesWaiting -= 1;
	passengerNumber[passengerAmount] = missionaryName + 1;
	// Identifying as a missionary
	passengerRole[passengerAmount] = 1;
	if(isMissionarySafe) isMissionarySafe = false;
	passengerAmount += 1;
	if(passengerAmount == 3) boarded = true;
	BoatLine->Wait();
	passengerAmount -= 1;
	passengerNumber[passengerAmount] = 2;
	passengerRole[passengerAmount] = 2;
	if(!passengerNumber) boarded = false;
	MonitorEnd();
}

CannibalThread:ThreadFunc()
{
	char buf[512];
	sprintf(buf, "%*cCannibal %d starts\n", id, ' ', id);
	write(1, buf, strlen(buf));
	while(1)
	{
		Delay();

		sprintf(%*cCannibal %d arrives\n", id, ' ', id);
		write(1, buf, strlen(buf));
		MyMonitor->CannibalArrives(id);
		Delay();
		Delay();
	}
}

void MyMonitor::CannibalArrives(int cannibalName)
{	// Basically the same as MissionaryArrives()
	MonitorBegin();
	if(!boatReady)
	{
		MonitorEnd();
		return;
	}

	cannibalsWaiting += 1;
	if(!isMissionarySafe) isMissionarySafe = true;
	CannibalLine->Wait();
	if(!boatReady)
	{
		MonitorEnd();
		return;
	}
	cannibalsWaiting -= 1;
	passengerNumber[passengerAmount] = cannibalName + 1;
	// Identifying as a missionary
	passengerRole[passengerAmount] = 1;
	if(isMissionarySafe) isMissionarySafe = false;
	passengerAmount += 1;
	if(passengerAmount == 3) boarded = true;
	BoatLine->Wait();
	passengerAmount -= 1;
	passengerNumber[passengerAmount] = 2;
	passengerRole[passengerAmount] = 2;
	if(!passengerNumber) boarded = false;
	
	MonitorEnd();
}

// Helper Function
char* MyMonitor::passengerList()
{
	int i;
	char *passengerList = new char[512];
	char buffer[512];
	for(i=0; i<3; i++)
	{
		switch(passengerRole[i])
		{
			case 0:
				sprintf(buffer, "c%d,", passengerNumber[i]);
				break;
			default:
				sprintf(buffer, "m%d,", passengerNumber[i]);
				break;
		}
		strcat(passengerList, buffer);
	}
	return passengerList;

}

