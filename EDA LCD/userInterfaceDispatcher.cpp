#include "userInterfaceDispatcher.h"
#include "eventGeneratorBundle.h"


userInterfaceDispatcher::userInterfaceDispatcher()
{
}


userInterfaceDispatcher::~userInterfaceDispatcher()
{
}

void
userInterfaceDispatcher::dispatcher(eventClass event, keyboardEvents* kb, networkingEvents* nw, timerEvents* tm, twitterEvents* tw)
{
	//cout << "INGRESE A DISPATCHER SHOW" << endl;
	if (event.getType() == KB_ev)
	{
		switch (event.getSubType())
		{
			case EXIT:
				break;
			case NEXT:
				tuitToShow = tw->getNextTuit();
				break;
			case REPEAT:
				tuitToShow = tw->getSameTuit();
				break;
			case PREVIOUS:
				tuitToShow = tw->getPreviousTuit();
				break;
			case FASTER:
				tm->riseSpeed() ;
				break;
			case SLOWER:
				tm->downSpeed();
				break;
		}
	}
	else if (event.getType() == TM_ev)
	{
		if (event.getSubType() == REFRESH)
		{
			//system("clear");
			clear();
			refresh();
			cout << tm->getDate() << endl;
			cout << tuitToShow << endl;
		}

	}
	else if (event.getType() == TW_ev)
	{
		switch (event.getType())
		{
		case FIRST_TUIT:
			tuitToShow = tw->getFirstTuit();
			break;
		case LAST_TUIT:
			tuitToShow = "Ultimo Tuit: " + tuitToShow;
			break;
		case NEXT_TUIT:
			tuitToShow = tw->getNextTuit();
			break;
		}
		event.setSubType(TW_EV_TYPE::NO_EVENT);
	}
}
