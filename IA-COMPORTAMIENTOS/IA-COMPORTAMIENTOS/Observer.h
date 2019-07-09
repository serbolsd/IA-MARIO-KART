#pragma once
#include <string>
class Observer
{
public:
	Observer();
	virtual ~Observer();
protected:
	std::string Event;
	Observer *NextObserver; 
	virtual void OnObserver() {};
};

