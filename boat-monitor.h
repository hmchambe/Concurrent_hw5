// Contains the class definition of monitors
//
#ifndef _MYMONITOR_H
#define _MYMONITOR_H
#include "thread.h"

class MyMonitor : public Monitor
{
	public:
		MyMonitor(char* Name);
		char* passengerList();
		void CannibalArrives(int CannibalName);
		void MissionaryArrives(int MissionaryName);
		void BoatReady();
		void BoatDone(int totalTrips);
		bool isMissionarySafe();

	private:
		Condition *MissionaryLine;
		Condition *CannibalLine;
		Condition *BoatLine;
		bool boarded;
		bool boatReady;		
		bool missionarySafe;	
		int passengerAmount;	
		int passengerNumber[3];
		int passengerRole[3];
		int missionariesWaiting;
		int cannibalsWaiting;
		int passengers;		
		int totalTrips;
		int trip;
};

#endif
