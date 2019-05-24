#include "eventGeneratorBundle.h"
#include "genericEventGenerator.h"
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
	//printf("ENTRE A CONTINUE");

	bool continueFlag = true;

	if (hayEvent())
	{
		//cout << "HUBO EVENTO EN EL BUNDLE" << endl;
		for (list<eventClass>::iterator it = eventQueue.begin(); it != eventQueue.end(); it++)
		{
			if (it->getSubType() == EXIT && it->getType() == KB_ev)
				continueFlag = false;
		}
	}

	return continueFlag;
}

bool
eventGeneratorBundle::hayEvent()
{
	//printf("ENTRE A HAY EVENTO");
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
	//printf("ENTRE A GET EVENTO");
	list<eventClass>::iterator itr = eventQueue.begin();
	eventClass temp = *itr;
	eventQueue.pop_front();

	return temp;
}

void
eventGeneratorBundle::attach(genericEventGenerator* evGen)
{
	//printf("ENTRE A ATACH");
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