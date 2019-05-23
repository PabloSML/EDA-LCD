#pragma once
#include "genericEventGenerator.h"
class networkingEvents :
	public genericEventGenerator
{
public:
	networkingEvents();
	~networkingEvents();

	virtual eventClass getEvent(void);
	virtual bool hayEvent(void);
};

