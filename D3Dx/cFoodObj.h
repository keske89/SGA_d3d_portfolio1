#pragma once
#include "cIGObj.h"
class cProgressbar;

class cFoodObj : public cIGObj
{
protected:
	SYNTHESIZE(bool, m_isChopped, chopped);
	SYNTHESIZE(bool, m_bIsStart, isStart);

	
public:
	cFoodObj();
	virtual ~cFoodObj();
	
};

