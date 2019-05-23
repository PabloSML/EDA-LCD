#pragma once
#include "genericEventGenerator.h"
class keyboardEvents :
	public genericEventGenerator
{
public:
	keyboardEvents();
	~keyboardEvents();
	virtual eventType getEvent(void);
	virtual bool hayEvent(void);
};
