#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

#define DATABASE database::GetInstance()

class database
{
	SINGLETONE(database)

private:
	bool m_bIsStageclear[10];
	int m_nStageStar[10];

public:

	void Setup();
	void Update();
	void Release();

	inline bool getIsStageClear(int num) { return m_bIsStageclear[num]; }
	inline int getStageStar(int num) { return m_nStageStar[num]; }
};

