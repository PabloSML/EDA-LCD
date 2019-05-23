#include "timerEvents.h"

timerEvents::timerEvents() 
{
	myEvent.setType(EventType::TM_ev);
	myEvent.setSubType((int)tmEvType::TICK);
	tick = (milliseconds)100;
}

bool
timerEvents::setEvent()
{
	bool success = false;
	if (myEvent.isEventEmpty())
	{
		success = true;
	}

	return success;
}

eventClass
timerEvents::getEvent(void)
{
	return myEvent;
}

bool
timerEvents::hayEvent(void)
{
	bool isThereEvent = false;
	current = high_resolution_clock::now();
	timeSpan = duration_cast<duration<double>> (current - origin);
	if (timeSpan > tick)
	{
		if (setEvent())
		{
			isThereEvent = true;
		}
		restartTimer();
	}

	return isThereEvent;
}