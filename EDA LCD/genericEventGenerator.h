#pragma once

#define NO_SUBTYPE (-1)

/*
*KB_ev -> KeyboardEvent
*NW_ev -> NetworkingEvent
*TM_ev -> TimerEvent
*TW_ev -> TwitterEvent
*/
enum class EventType {KB_ev, NW_ev, TM_ev, TW_ev};

class eventClass {
public:
	eventClass() { this->subType = NO_SUBTYPE; this->data = nullptr; }
	eventClass(EventType type, int subType, void* data)
	{
		this->type = type;
		this->subType = subType;
		this->data = data;
	}

	void setType(EventType type) { this->type = type; }
	void setSubType(int subType) { this->subType = subType; }
	void setData(void* data) { this->data = data; }
	bool isEventEmpty(void) { 
		bool empty = true;
		if (this->subType != NO_SUBTYPE)
			empty = false;
		return empty;
	}

private:
	EventType type;
	int subType;
	void* data;
};

class genericEventGenerator
{
public:
	virtual eventClass getEvent(void) = 0;
	virtual bool hayEvent(void) = 0;

protected:
	eventClass myEvent;
};

