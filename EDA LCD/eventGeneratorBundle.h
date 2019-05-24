#pragma once
#include "genericEventGenerator.h"
#include <list>

using namespace std;

class eventGeneratorBundle
{
public:
	eventGeneratorBundle();
	~eventGeneratorBundle();

	bool Continue(void);
	bool hayEvent(void);

	eventClass getEvent(void);

	void attach(genericEventGenerator*);
	void detach(genericEventGenerator*);

private:
	list<genericEventGenerator*> eventGens;
	list<eventClass> eventQueue;
	bool quit;
};

