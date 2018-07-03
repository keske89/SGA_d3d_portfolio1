#pragma once
#include "cTimer.h"

#define TIMEMANAGER cTimeManager::GetInstance()

class cTimeManager
{
	SINGLETONE(cTimeManager)
private:
	cTimer* m_pTimer;

public:
	void Setup();
	void Destroy();
	void Update(float lock = 0.0f);
	void Render();

	inline float getElapsedTime(void) const { return m_pTimer->getElapsedTime(); }
	inline float getWorldTime(void) const { return m_pTimer->getWorldTime(); }
};

