#pragma once
#include "genericEventGenerator.h"
class timerEvents :
	public genericEventGenerator
{
public:
	timerEvents();
	~timerEvents();
	virtual EventType getEvent(void);
	virtual bool hayEvent(void);
};

