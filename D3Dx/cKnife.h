#pragma once
#include "cActionObj.h"

class cKnife : public cActionObj
{
public:
	cKnife();
	virtual ~cKnife();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

