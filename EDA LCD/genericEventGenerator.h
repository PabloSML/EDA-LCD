#ifndef GENERICEVENTGENERATOR_H
#define GENERICEVENTGENERATOR_H

#define NO_SUBTYPE (-1)
#define TOTAL_EVENTS (4)

using namespace std;
/*
*KB_ev -> KeyboardEvent
*NW_ev -> NetworkingEvent
*TM_ev -> TimerEvent
*TW_ev -> TwitterEvent
*/

enum  EventType {KB_ev, NW_ev, TM_ev, TW_ev};
enum  kbEvType : int  { EXIT = 0, PREVIOUS, NEXT, REPEAT, FASTER, SLOWER, NO_KB_EVENT};
enum  NW_EV_TYPE : int { TOKEN_RECEIVED , DATA_RECEIVED , DISCONNECTED , NO_MORE_DATA, NO_NW_EVENT};
enum  TM_EV_TYPE : int { REFRESH, NO_TM_EVENT};
enum  TW_EV_TYPE : int { LAST_TUIT , TUIT_READY , NEXT_TUIT , FIRST_TUIT, NO_TW_EVENT};

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

	EventType getType(void) { return type; }
	int  getSubType(void) { return subType; }
	void* getData (void)	{ return data; }

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

#endif