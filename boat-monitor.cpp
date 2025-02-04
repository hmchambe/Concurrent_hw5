// ----------------------------------------------------------- 
// NAME : Hunter Chambers                         User ID: 81276171 
// DUE DATE : 12/06/2019                                       
// PROGRAM ASSIGNMENT 5                                        
// FILE NAME : boat-monitor.cpp            
// PROGRAM PURPOSE :                                           
//    Solves the river crossing problem concurrently using monitors      
// ----------------------------------------------------------- 
#include "ThreadClass.h"
#include "thread.h"
#include "boat-monitor.h"

// ----------------------------------------------------------- 
// FUNCTION  Constructor                          
//     Initialize myMonitor                            
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
MyMonitor::MyMonitor(char *Name)
	: Monitor(Name, HOARE)
{
	srand(time(NULL));
	


	missionarySafe = false;
	boarded = false;
	boatReady = false;
	trip = 0;
	passengerAmount = 0;
	cannibalsWaiting = 0;
	CannibalLine = new Condition("Hungry");
	missionariesWaiting = 0;
	MissionaryLine = new Condition("Innocent");
	BoatLine = new Condition("OnBoat");
	//passengerNumber = new int[3];
	//passengerRole = new int [3];

	passengerNumber[0] = 2;
	passengerNumber[1] = 2;
	passengerNumber[2] = 2;
	passengerRole[0] = 2;
	passengerRole[1] = 2;
	passengerRole[2] = 2;
}

// ----------------------------------------------------------- 
// FUNCTION  isMissionarySafe                
//     Tells if missionary is safe                            
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
bool MyMonitor::isMissionarySafe()
{
	return missionarySafe;
}

// COMPLETE
void MyMonitor::BoatReady()
{
	MonitorBegin();
	char buffer[512];
	int i, j, selectedIndex;
	bool boatFilled = false;
	// Randomization process
	selectedIndex = (int)(rand() % 3);
	while(!boatFilled){
		// Choosing how to fill boat, while not allowing missionaries to be eaten
		switch(selectedIndex)
		{
			case 0:
				if(missionariesWaiting >= 3)
				{
					for(j=0; j<3; j++)
					{
						MissionaryLine->Signal();
					}
					sprintf(buffer, "MONITOR(%d): Three missionaries are selected (%d, %d, %d)\n", trip+1, passengerNumber[0], passengerNumber[1], passengerNumber[2]);
				}
				write(1, buffer, strlen(buffer));
				boatFilled = true;
				break;
			case 1:
				for(j=0; j<2; j++)
				{
					MissionaryLine->Signal();
				}
				CannibalLine->Signal();
				int cannibal, firstMiss, secondMiss; 
				cannibal = 1;
				firstMiss = 0;
				secondMiss = 2;
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
				write(1, buffer, strlen(buffer));
				boatFilled = true;
				break;
			default:
				for(j=0; j<3; j++)
				{
					CannibalLine->Signal();
				}
				sprintf(buffer, "MONITOR(%d): Three cannibals are selected (%d, %d, %d)\n", trip+1, passengerNumber[0], passengerNumber[1], passengerNumber[2]);
				write(1, buffer, strlen(buffer));
				boatFilled = true;
				break;
		}
	}

	MonitorEnd();

}

// ----------------------------------------------------------- 
// FUNCTION  BoatDone                          
//     Cleans up when boat is done                            
// PARAMETER USAGE :                                           
//    totalTrips -> tells the number of trips total               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
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
		MonitorEnd();
		Exit();
	}
	MonitorEnd();
}

// ----------------------------------------------------------- 
// FUNCTION  MissionaryArrives                          
//     Lets boat know that missionary is ready and waits                         
// PARAMETER USAGE :                                           
//    missionaryName -> missionary id
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
void MyMonitor::MissionaryArrives(int missionaryName)
{
	MonitorBegin();
	if(!boatReady)
	{	//Boat is not ready for any reason
		MonitorEnd();
		return;
	}
	missionariesWaiting += 1;

	if(!missionarySafe) missionarySafe = true;
	MissionaryLine->Wait();
	if(!boatReady)
	{
		MonitorEnd();
		return;
	}	
	missionariesWaiting -= 1;
	passengerNumber[passengerAmount] = missionaryName + 1;
	// Identifying as a missionary
	passengerRole[passengerAmount] = 1;
	if(missionarySafe) missionarySafe = false;
	passengerAmount += 1;
	if(passengerAmount == 3) boarded = true;
	BoatLine->Wait();
	passengerAmount -= 1;
	passengerNumber[passengerAmount] = 2;
	passengerRole[passengerAmount] = 2;
	if(!passengerNumber) boarded = false;
	MonitorEnd();
}

// ----------------------------------------------------------- 
// FUNCTION  CannibalArrives                          
//     Lets boat know that the cannibal is ready and waiting                           
// PARAMETER USAGE :                                           
//	cannibalName: cannibal id
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
void MyMonitor::CannibalArrives(int cannibalName)
{	// Basically the same as MissionaryArrives()
	MonitorBegin();
	if(!boatReady)
	{
		MonitorEnd();
		return;
	}

	cannibalsWaiting += 1;
	if(!missionarySafe) missionarySafe = true;
	CannibalLine->Wait();
	if(!boatReady)
	{
		MonitorEnd();
		return;
	}
	cannibalsWaiting -= 1;
	passengerNumber[passengerAmount] = cannibalName + 1;
	// Identifying as a missionary
	passengerRole[passengerAmount] = 0;
	if(missionarySafe) missionarySafe = false;
	passengerAmount += 1;
	if(passengerAmount == 3) boarded = true;
	BoatLine->Wait();
	passengerAmount -= 1;
	passengerNumber[passengerAmount] = 2;
	passengerRole[passengerAmount] = 2;
	if(!passengerNumber) boarded = false;
	
	MonitorEnd();
}

// ----------------------------------------------------------- 
// FUNCTION  passengerList                          
//     returns the list of passengers on the boat                            
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
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

