#pragma once
#include "cActionObj.h"

class cFoodObj;


class cKnife : public cActionObj
{
	
	


public:
	cKnife();
	virtual ~cKnife();

	virtual void Setup()	override;
	virtual void Update()	override;
	virtual void Render()	override;
	
};

