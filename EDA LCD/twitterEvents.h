#pragma once
#include "genericEventGenerator.h"
class twitterEvents :
	public genericEventGenerator
{
public:
	twitterEvents();
	~twitterEvents();
	virtual EventType getEvent(void);
	virtual bool hayEvent(void);
};

