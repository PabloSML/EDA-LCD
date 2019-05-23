#pragma once
#include "genericEventGenerator.h"
class keyboardEvents :
	public genericEventGenerator
{
public:
	keyboardEvents();
	~keyboardEvents();
	virtual eventClass getEvent(void);
	virtual bool hayEvent(void);
};
