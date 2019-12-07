#include "ThreadClass.h"
#include "thread.h"
#include "boat-monitor.h"

int main(int argc, char *argv[])
{
	int cannibals = atoi(argv[1]) ? atoi(argv[1]) : 8;
	int missionaries = atoi(argv[2]) ? atoi(argv[2]) : 8;
        int boats = atoi(argv[3]) ? atoi(argv[3]) : 5;
	int i;
	
	BoatThread *boatThread = new BoatThread(boats);
	MissionaryThread *missionaryThread[sizeof(MissionaryThread)*missionaries];
	CannibalThread *cannibalThread[sizeof(CannibalThread)*cannibals];
	
	// Initialize threads
	for(i=0; i<missionaries; i++)
	{
		missionaryThread[i] = new MissionaryThread(i);
	}
	for(i=0; i<cannibals; i++)
	{
		cannibalThread[i] = new CannibalThread(i);
	}

	// Start threads
	boatThread->Begin();
	for(i=0; i<missionaries; i++)
	{
		missionaryThread[i]->Begin();
	}
	for(i=0; i<cannibals; i++)
	{
		cannibalThread[i]->Begin();
	}

	// Cleanup
	boatThread->Join();
	Exit();
	return 0;
}
