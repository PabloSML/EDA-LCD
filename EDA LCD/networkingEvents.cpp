#include "networkingEvents.h"



networkingEvents::networkingEvents()
{
}


networkingEvents::~networkingEvents()
{
}

eventClass
networkingEvents::getEvent(void)
{
	return myEvent;
}

bool
networkingEvents::hayEvent(void)
{
	return false;	//SOLO PARA QUE COMPILE
}