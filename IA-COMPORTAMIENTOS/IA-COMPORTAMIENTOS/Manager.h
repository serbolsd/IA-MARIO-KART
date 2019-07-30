#pragma once
#include "vector2.h"
#include <vector>
#include <Graphics.hpp>
#include "Point.h"
#include <Window.hpp>
#include "Observe_Event.h"
#include <sstream>
class Manager
{
public:
	Manager();
	~Manager();
	Observe_Event* FirstEvent;
	Observe_Event* currentEvent;
	void initObserveEventsFollowPath(int numPoints);
	int m_numPointsFollowPath = 0;
};

