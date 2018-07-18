#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class database : public singletonBase <database>
{
private:
	bool m_bIsStageclear[10];

public:
	database();
	~database();

	void Setup();
	void Update();
	void Release();

	inline bool getIsStageClear(int num) { return m_bIsStageclear[num - 1]; }
};

