#pragma once
#include "genericEventGenerator.h"
class timerEvents :
	public genericEventGenerator
{
public:
	timerEvents();
	~timerEvents();
	EventType getEvent(void);
	bool hayEvent(void);
};

