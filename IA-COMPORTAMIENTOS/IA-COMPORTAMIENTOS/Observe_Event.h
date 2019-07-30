#pragma once
#include "Observer.h"
#include <iostream>
class Observe_Event:Observer
{
public:
	Observe_Event();
	~Observe_Event();
private:
public:
	Observe_Event* m_nextObserve=nullptr;
	void OnObserver() ;
	bool OnComplete() { std::cout << m_Event << "\n"; return true; };
	Observe_Event* nextEvent() { return m_nextObserve; };
	virtual void setEvent(std::string Event) { m_Event = Event; };
	void onDelete();
};

