#pragma once
#include "genericEventGenerator.h"
class timerEvents :
	public genericEventGenerator
{
public:
	timerEvents();
	~timerEvents();
	eventClass getEvent(void);
	bool hayEvent(void);
};

