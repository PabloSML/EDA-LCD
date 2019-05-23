#pragma once

/*
*KB_ev -> KeyboardEvent
*NW_ev -> NetworkingEvent
*TM_ev -> TimerEvent
*TW_ev -> TwitterEvent
*/
enum class EventType {KB_ev, NW_ev, TM_ev, TW_ev};

class eventClass {
public:
	eventClass(EventType type, int data)
	{
		this->type = type;
		this->data = data;
	}

private:
	EventType type;
	int data;
};

class genericEventGenerator
{
public:
	virtual eventClass getEvent(void) = 0;
	virtual bool hayEvent(void) = 0;
};

