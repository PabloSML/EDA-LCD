#include "twitterEvents.h"



twitterEvents::twitterEvents()
{
}


twitterEvents::~twitterEvents()
{
}

eventClass
twitterEvents::getEvent(void)
{
	return myEvent;
}

bool
twitterEvents::hayEvent(void)
{
	return false;	//SOLO PARA QUE COMPILE
}