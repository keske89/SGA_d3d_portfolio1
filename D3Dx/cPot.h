#pragma once
#include "cActionObj.h"

class cFoodObj;
class cProgressbar;

class cPot : public cActionObj
{
public:
	
	cProgressbar*			m_pPgbar;
	std::vector<cFoodObj*>	m_vecFood;
	int						m_size;

public:
	cPot();
	~cPot();

	virtual void Setup()	override;
	virtual void Update()	override;
	virtual void Render()	override;

	void SetFood(cFoodObj* foodobject);

};

