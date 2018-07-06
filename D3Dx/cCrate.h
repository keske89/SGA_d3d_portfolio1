#pragma once
#include "cActionObj.h"


class cCrate : public cActionObj
{
public:
	cCrate();
	~cCrate();


	virtual void Setup();
	virtual void Update();
	virtual void Render();

};


