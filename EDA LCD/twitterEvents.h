#pragma once
#include "genericEventGenerator.h"
class twitterEvents :
	public genericEventGenerator
{
public:
	twitterEvents();
	~twitterEvents();
	virtual eventClass getEvent(void);
	virtual bool hayEvent(void);
};

