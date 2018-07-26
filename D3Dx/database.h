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
	SYNTHESIZE(int, m_nStageNum, stageNum);
	SYNTHESIZE(int, m_nChageChefNum1P, chageChefNum1P);
	SYNTHESIZE(int, m_nChageChefNum2P, chageChefNum2P);
	SYNTHESIZE(unsigned int, m_nTip, Tip);
public:

	void Setup();
	void Update();
	void Release();

	inline bool getIsStageClear(int num) { return m_bIsStageclear[num]; }
	inline int getStageStar(int num) { return m_nStageStar[num]; }
	inline int ChangeTip(int num) { m_nTip += num; }
};

