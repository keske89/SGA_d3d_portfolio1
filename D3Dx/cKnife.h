#pragma once
#include "cActionObj.h"

class cProgressbar;
class cFoodObj;


class cKnife : public cActionObj
{
	cProgressbar* progressbar;
	cFoodObj*	  m_pInven;


public:
	cKnife();
	virtual ~cKnife();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

