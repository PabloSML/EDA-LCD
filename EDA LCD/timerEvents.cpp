#include "timerEvents.h"
#include <iostream>

timerEvents::timerEvents() 
{
	timer = DEFAULT_TIMER;
	myEvent.setType(EventType::TM_ev);
	myEvent.setSubType((int)TM_EV_TYPE::REFRESH);
	tick = (milliseconds)timer;
}


eventClass
timerEvents::getEvent(void)
{
	return myEvent;
}

bool
timerEvents::hayEvent(void)
{
	//std::cout << "PREGUNTO POR EL EVENTO" << std::endl;
	bool isThereEvent = false;
	current = high_resolution_clock::now();
	timeSpan = duration_cast<duration<double>> (current - origin);
	if (timeSpan > tick)
	{
		//if (setEvent())
		//{
			isThereEvent = true;
			setEvent(TM_EV_TYPE::REFRESH);


			//cout << "eventos cada" << tick << "   MILISEG" << std::endl;
			//std::cout << "HUBO EVENTO DE TIMER EN HAYEVENT" << std::endl;
		//}
		restartTimer();
	}

	return isThereEvent;
}

void
timerEvents::riseSpeed()
{
	if (timer + TIME_SENSIBILITY <= MAX_TIMER)
	{
		timer += TIME_SENSIBILITY;
		cout << "eventos cada" << timer << "   MILISEG" << std::endl;
		tick = (milliseconds)timer;
	}

} 

void
timerEvents::downSpeed()
{
	if (timer - TIME_SENSIBILITY >= MIN_TIMER)
	{
		timer -= TIME_SENSIBILITY;
		cout << "eventos cada" << timer << "   MILISEG" << std::endl;
		tick = (milliseconds)timer;
	}
}


std::string
timerEvents::getDate(void)
{
	/*std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::string s(30, '\0');
	std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return s;*/

	//AGREGAR FUNCION PARA OBTENER LA FECHA
	string str = "PONER FECHA";
	return str;
}


void
timerEvents::setEvent(TM_EV_TYPE ev)
{
	myEvent.setSubType(ev);
}