#pragma once

/*
*KB_ev -> KeyboardEvent
*NW_ev -> NetworkingEvent
*TM_ev -> TimerEvent
*TW_ev -> TwitterEvent
*/
enum class EventType {KB_ev, NW_ev, TM_ev, TW_ev};
/*
enum eventType {EXIT, NEXT, REPEAT, PREVIOUS, FASTER, SLOWER,	// user events
	REFRESH,													// clock events
	TOKEN_RECIEVED, DATA_RECIEVED, DISCONNECTED, NO_MORE_DATA,	// networking events
	LAST_TWEET, FIRST_TWEET, TWEET_READY, NEXT_TWEET};			// tweet control
	*/
/*typedef struct {
	EventType type;
	const void* data;
}eventStruct;

class eventClass {
public:
	eventClass();
	~eventClass(){ delete data; }



private:
	EventType type;
	void* data;
};*/

class genericEventGenerator
{
public:
	virtual EventType getEvent(void) = 0;
	virtual bool hayEvent(void) = 0;
};

