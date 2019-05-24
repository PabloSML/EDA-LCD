#include "userInterfaceDispatcher.h"
#include "eventGeneratorBundle.h"


userInterfaceDispatcher::userInterfaceDispatcher()
{
	cutIndex = 0;
	hayTuit = false;
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
		cout << "INGRESE A EVENTO DE TECLADO " << endl;
		switch (event->getSubType())
		{
			case EXIT:
				break;
			case NEXT:
				tuitToShow = tw->getNextTuit();
				hayTuit = true;
				cutIndex = 0;
				break;
			case REPEAT:
				tuitToShow = tw->getSameTuit();
				hayTuit = true;
				cutIndex = 0;
				break;
			case PREVIOUS:
				tuitToShow = tw->getPreviousTuit();
				hayTuit = true;
				cutIndex = 0;
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
	else if (event->getType() == TW_ev && event->getSubType() != TW_EV_TYPE::NO_TW_EVENT)
	{
		//cout << "INGRESE A EVENTO DE TWITTER " << endl;
		//cout << "SUBTYPE ANTES:   " << event->getSubType() << endl;
		switch (event->getSubType())
		{
		case FIRST_TUIT:
			tuitToShow = tw->getFirstTuit();
			hayTuit = true;
			break;
		case LAST_TUIT:
			if (tuitToShow.find("Ultimo Tuit") == string::npos)
				tuitToShow = "  Ultimo Tuit:" + tuitToShow;
			break;
		case NEXT_TUIT:
			cout << "INGRESE A NEXT TUIT  " << endl;
			tuitToShow = tw->getNextTuit();
			hayTuit = true;
			cutIndex = 0;
			break;
		}
		tw->setEvent(TW_EV_TYPE::NO_TW_EVENT);
		//cout << "SUBTYPE:   " << event->getSubType() << endl;
	}
	else if (event->getType() == TM_ev)
	{
		if (event->getSubType() == REFRESH)
		{
			string str;
			if (cutIndex + 16 <= tuitToShow.length())
			{
				str = tuitToShow.substr(0 + cutIndex, 16);
				cutIndex++;
				print(tw, str);
			}
			else
			{
				if (hayTuit)
				{
					tw->setEvent(TW_EV_TYPE::NEXT_TUIT);
					hayTuit = false;
				}
			}
		}
		//tw->setEvent(TW_EV_TYPE::NEXT_TUIT);
		tm->setEvent(TM_EV_TYPE::NO_TM_EVENT);
	}
}


void
userInterfaceDispatcher::print(twitterEvents* tw,string tuitToDisplay)
{
	clear();
	refresh();
	cout << tw->getDate() << endl;
	cout << tuitToDisplay << endl;
}

