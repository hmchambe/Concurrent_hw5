// ----------------------------------------------------------- 
// NAME : Hunter Chambers                         User ID: 81276171 
// DUE DATE : 12/06/2019                                       
// PROGRAM ASSIGNMENT 5                                        
// FILE NAME : thread.cpp            
// PROGRAM PURPOSE :                                           
//    Solves the river crossing problem concurrently using monitors      
// ----------------------------------------------------------- 
#include "ThreadClass.h"
#include "thread.h"
#include "boat-monitor.h"

static MyMonitor *myMonitor;

// ----------------------------------------------------------- 
// FUNCTION  Constructor                          
//     Initialize BoatThread                            
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
BoatThread::BoatThread(int boat)
		:boat(boat)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "TheAlmightyBoooaaaattt" << '\0';
	myMonitor = new MyMonitor("TheAlmightyBoooaaaattt");
}

// ----------------------------------------------------------- 
// FUNCTION  Initialize CannibalThread                          
//     Initialize myMonitor                            
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
CannibalThread::CannibalThread(int id)
	:id(id)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "HungryCannibal[" << id << "]" << '\0';
}

// ----------------------------------------------------------- 
// FUNCTION  Initialize MissionaryThread                          
//     Initialize myMonitor                            
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
MissionaryThread::MissionaryThread(int id)
	:id(id)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "InnocentMissionary[" << id << "]" << '\0';
}

// ----------------------------------------------------------- 
// FUNCTION  ThreadFunc                          
//     CannibalThreads main function                        
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
void CannibalThread::ThreadFunc()
{
	char buf[512];
	sprintf(buf, "%*cCannibal %d starts\n", id, ' ', id);
	write(1, buf, strlen(buf));
	while(1)
	{
		Delay();
		sprintf(buf, "%*cCannibal %d arrives\n", id, ' ', id);
		write(1, buf, strlen(buf));
		myMonitor->CannibalArrives(id);
		Delay();
	}
}

// ----------------------------------------------------------- 
// FUNCTION  ThreadFunc                          
//     BoatThreads main function                        
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
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

// ----------------------------------------------------------- 
// FUNCTION  ThreadFunc                          
//     MissionaryThreads main function                        
// PARAMETER USAGE :                                           
//    None               
// FUNCTION CALLED :                                           
//    None        
// ----------------------------------------------------------- 
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
		Delay();

	}

}


