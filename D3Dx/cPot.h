#pragma once
#include "cActionObj.h"

class cFoodObj;
class cProgressbar;

class cPot : public cActionObj
{
public:
	
	cProgressbar*			m_pPgbar;
	std::vector<cFoodObj*>	m_vecFood;

public:
	cPot();
	~cPot();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void SetFood(cFoodObj* foodobject);

};

