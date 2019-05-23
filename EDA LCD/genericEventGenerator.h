#pragma once

#define NO_DATA (-1)

/*
*KB_ev -> KeyboardEvent
*NW_ev -> NetworkingEvent
*TM_ev -> TimerEvent
*TW_ev -> TwitterEvent
*/
enum class EventType {KB_ev, NW_ev, TM_ev, TW_ev};

class eventClass {
public:
	eventClass() { this->data = NO_DATA; }
	eventClass(EventType type, int data)
	{
		this->type = type;
		this->data = data;
	}

	void setType(EventType type) { this->type = type; }
	void setData(int data) { this->data = data; }
	bool isDataEmpty(void) { 
		bool empty = true;
		if (this->data != NO_DATA)
			empty = false;
		return empty;
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

protected:
	eventClass myEvent;
};

