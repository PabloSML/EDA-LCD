#include "timerEvents.h"



timerEvents::timerEvents()
{
}


timerEvents::~timerEvents()
{
}

eventClass
timerEvents::getEvent(void)
{
	return myEvent;
}

bool
timerEvents::hayEvent(void)
{
	return false;	//SOLO PARA QUE COMPILE
}