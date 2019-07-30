#pragma once
#include <string>
class Observer
{
public:
	Observer();
	virtual ~Observer();
protected:
	std::string m_Event;
	virtual void OnObserver() {};
	virtual bool OnComplete() { return true; };
	virtual Observer* nextEvent() { return nullptr; };
	virtual void setEvent() {};
	virtual void onDelete() {};
};

