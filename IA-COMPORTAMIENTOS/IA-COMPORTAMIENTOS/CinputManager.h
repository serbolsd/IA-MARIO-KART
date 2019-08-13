#pragma once
#include "Boid.h"
class CinputManager
{
public:
	CinputManager();
	~CinputManager();
	void onUpdate(int controlID, Boid & player);
	float m_timeTrans;
};

