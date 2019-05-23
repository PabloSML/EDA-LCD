#include "timerEvents.h"

timerEvents::timerEvents()
{
}


timerEvents::~timerEvents()
{
}

bool
timerEvents::setEvent()
{
	bool success = false;
	if (myEvent.isEventEmpty())
	{
		myEvent.setType(EventType::TM_ev);
		myEvent.setSubType((int)tmEvType::TICK);
		success = true;
	}

	return success;
}

eventClass
timerEvents::getEvent(void)
{
	eventClass temp = myEvent;
	myEvent.setSubType(NO_SUBTYPE);
	myEvent.setData(nullptr);
	return temp;
}

bool
timerEvents::hayEvent(void)
{
	bool isThereEvent = false;
	milliseconds tick = milliseconds(100);
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