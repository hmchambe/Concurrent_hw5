#include "ThreadClass.h"

MyMonitor::MyMonitor(char *Name)
	: Monitor(Name, HOARE)
{
	CanniblesWaiting = 0;
	MissionariesWaiting = 0;
}
