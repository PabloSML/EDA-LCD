#include "userInterfaceDispatcher.h"
#include "eventGeneratorBundle.h"


userInterfaceDispatcher::userInterfaceDispatcher()
{
}


userInterfaceDispatcher::~userInterfaceDispatcher()
{
}

void
userInterfaceDispatcher::dispatcher(eventClass* event, keyboardEvents* kb, networkingEvents* nw, timerEvents* tm, twitterEvents* tw)
{
	//cout << "INGRESE A DISPATCHER SHOW" << endl;
	if (event->getType() == KB_ev)
	{
	//	cout << "INGRESE A EVENTO DE TECLADO " << endl;
		switch (event->getSubType())
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
		//kb->setEvent(kbEvType::NO_KB_EVENT);
	}
	else if (event->getType() == TM_ev)
	{
		if (event->getSubType() == REFRESH)
		{
			clear();
			refresh();
			cout << tm->getDate() << endl;
			cout << tuitToShow << endl;
		}
		//tw->setEvent(TW_EV_TYPE::NEXT_TUIT);
		//tm->setEvent(TM_EV_TYPE::NO_TM_EVENT);
	}
	else if (event->getType() == TW_ev && event->getSubType() != TW_EV_TYPE::NO_TW_EVENT)
	{
		//cout << "INGRESE A EVENTO DE TWITTER " << endl;
		//cout << "SUBTYPE ANTES:   " << event->getSubType() << endl;
		switch (event->getSubType())
		{
		case FIRST_TUIT:
			tuitToShow = tw->getFirstTuit();
			break;
		case LAST_TUIT:
			tuitToShow = "Ultimo Tuit: " + tuitToShow;
			break;
		case NEXT_TUIT:
			cout << "INGRESE A NEXT TUIT  " << endl;
			cout << "INGRESE A NEXT TUIT  " << endl;
			cout << "INGRESE A NEXT TUIT  " << endl;
			cout << "INGRESE A NEXT TUIT  " << endl;
			tuitToShow = tw->getNextTuit();
			break;
		}
		tw->setEvent(TW_EV_TYPE::NO_TW_EVENT);
		//cout << "SUBTYPE:   " << event->getSubType() << endl;
	}
}


void
userInterfaceDispatcher::print()
{

}

