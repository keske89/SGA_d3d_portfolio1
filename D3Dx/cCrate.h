#pragma once
#include "cActionObj.h"

class cCrateLid;

class cCrate : public cActionObj
{
public:
	cCrateLid*	m_CrateLid;
public:
	cCrate();
	~cCrate();


	virtual void Setup();
	virtual void Update();
	virtual void Render();

};

