#pragma once
#include "cActionObj.h"

class cCrateLid	: public cActionObj
{
public:

	SYNTHESIZE(std::string, m_attr, Attr);

public:
	cCrateLid();
	~cCrateLid();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

