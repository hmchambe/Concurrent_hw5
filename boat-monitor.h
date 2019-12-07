// Contains the class definition of monitors
//
#ifndef _MYMONITOR_H
#define _MYMONITOR_H
#include "thread.h"

class MyMonitor : public Monitor
{
	public:
		MyMonitor(char* Name);
// TODO these might be wrong
		char* getRiderName();
		int getCrossingNumber();
//
		void CannibalArrives(int CannibalName);
		void MissionaryArrives(int MissionaryName);
		void BoatReady();
		void BoatDone();
		bool isMissionarySafe();

	private:
		Condition *MissionaryLine;
		Condition *CannibalLine;
		Condition *BoatLine
		bool boarded;
		bool boatReady;		
		bool isMissionarySafe;	
		int passengerAmount;	
		int passengerNumber[3];
		int passengerRole[3];
		int missionariesWaiting;
		int cannibalsWaiting;
		int passengers;		
		int totalTrips;
		int trip;
}

#endif
