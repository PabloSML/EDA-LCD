#include "downloadDispatcher.h"



downloadDispatcher::downloadDispatcher()
{
}


downloadDispatcher::~downloadDispatcher()
{
}

void
downloadDispatcher::dispatcher(eventClass* event, keyboardEvents* kb, networkingEvents* nw, timerEvents* tm, twitterEvents* tw)
{
	if (event->getType() == KB_ev)
	{
		if (event->getSubType() == EXIT)
		{
			//DO SOMETHING
		}

	}
	else if (event->getType() == NW_ev)
	{
		switch (event->getSubType())
		{
			case DATA_RECEIVED:
				break;
			case DISCONNECTED:
				break;
			case NO_MORE_DATA:
				break;
		}
	}
	else if (event->getType() == TM_ev)
	{
		if (event->getSubType() == REFRESH)
		{
			//DO SOMETHING
		}

	}
	else if (event->getType() == TW_ev)
	{
		if (event->getSubType() == TUIT_READY)
		{

		}
	}

}
