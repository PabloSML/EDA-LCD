#pragma once
#include "genericEventGenerator.h"
class networkingEvents :
	public genericEventGenerator
{
public:
	networkingEvents();
	~networkingEvents();

	virtual EventType getEvent(void);
	virtual bool hayEvent(void);
};

