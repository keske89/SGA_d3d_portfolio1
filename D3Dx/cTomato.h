#pragma once
#include "cFoodObj.h"

class cTomato : public cFoodObj
{

public:
	cTomato();
	virtual ~cTomato();

	virtual void Setup();
	virtual void Update();
	virtual void Render();


};

