#pragma once


/*
*KB_ev -> KeyboardEvent
*NW_ev -> NetworkingEvent
*TM_ev -> TimerEvent
*TW_ev -> TwitterEvent
*/
enum EventType {KB_ev, NW_ev, TM_ev, TW_ev}; 

class genericEventGenerator
{
public:
	virtual EventType getEvent(void) = 0;
	virtual bool hayEvent(void) = 0;
};

