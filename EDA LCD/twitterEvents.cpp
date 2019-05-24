#include "twitterEvents.h"



twitterEvents::twitterEvents()
{
	myEvent.setType((EventType::TW_ev));
	myEvent.setSubType((TW_EV_TYPE::NO_EVENT));

	index = 0;
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
	bool value = false;
	/*if (index = 0)
	{
		value = true;
		myEvent.setSubType((TW_EV_TYPE::FIRST_TUIT));
	}*/
	/* if ((index + 1) == tuits.size())
	{	
		value = true;
		myEvent.setSubType((TW_EV_TYPE::LAST_TUIT));
	}*/
	
	return value;
}

string
twitterEvents::getNextTuit(void)
{
	list<string>::iterator it = tuits.begin();

	if ((index+1) < tuits.size())
	{
		index += 1;
	}
	std::advance(it, index);

	return *it;
}

string
twitterEvents::getSameTuit(void)
{
	list<string>::iterator it = tuits.begin();
	std::advance(it, index );

	return *it;
}

string
twitterEvents::getPreviousTuit(void)
{
	list<string>::iterator it = tuits.begin();
	if (index > 0)
	{
		index -= 1;
		std::advance(it, index);
	}

	return *it;
}

void 
twitterEvents::setTuits(std::list<std::string> downloadTuits)
{
	tuits=downloadTuits;
}

string
twitterEvents::getFirstTuit(void)
{
	list<string>::iterator it = tuits.begin();

	return *it;
}