#include "Manager.h"



Manager::Manager()
{
}


Manager::~Manager()
{
	currentEvent = FirstEvent->nextEvent();
	delete FirstEvent;
	FirstEvent = nullptr;
	for (size_t i = 0; i < m_numPointsFollowPath-1; i++)
	{
		Observe_Event* deleteEvent = currentEvent;
		currentEvent = deleteEvent->nextEvent();
		delete deleteEvent;
		deleteEvent = nullptr;
	}
}

void Manager::initObserveEventsFollowPath(int numPoints)
{
	m_numPointsFollowPath = numPoints;
	FirstEvent = new Observe_Event;
	FirstEvent->setEvent("paso punto 1");
	currentEvent = FirstEvent;
	for (int i = 0; i < numPoints-1; i++)
	{
		currentEvent->m_nextObserve= new Observe_Event;
		currentEvent = currentEvent->m_nextObserve;
		std::stringstream ss;
		ss << (i + 2);
		std::string evento = "paso punto ";
		evento += ss.str();
		currentEvent->setEvent(evento);

	}
	currentEvent->m_nextObserve = FirstEvent;
}
