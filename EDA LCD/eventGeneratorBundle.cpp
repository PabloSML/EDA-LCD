#include "eventGeneratorBundle.h"
#include <iostream>



eventGeneratorBundle::eventGeneratorBundle()
{
}


eventGeneratorBundle::~eventGeneratorBundle()
{
}

bool
eventGeneratorBundle::Continue()
{
	return !quit;
}

bool
eventGeneratorBundle::hayEvent()
{
	for (genericEventGenerator* gen : eventGens)
	{
		if (gen->hayEvent())
			eventQueue.push_back(gen->getEvent());
	}

	return !(eventQueue.empty());
}

eventClass
eventGeneratorBundle::getEvent()
{
	list<eventClass>::iterator itr = eventQueue.begin();
	eventClass temp = *itr;
	eventQueue.pop_front();

	return temp;
}

void
eventGeneratorBundle::attach(genericEventGenerator* evGen)
{
	eventGens.push_back(evGen);
}

void
eventGeneratorBundle::detach(genericEventGenerator* evGen)
{
	list<genericEventGenerator*>::iterator itr = eventGens.begin();
	int size = eventGens.size();
	bool done = false;

	for (int i = 0; i < size && !done; i++, itr++)
	{
		if (*itr == evGen)
		{
			eventGens.erase(itr);
			done = true;
		}
	}
	if (!done)
		std::cout << "Event Generator not found in Bundle" << std::endl;
}