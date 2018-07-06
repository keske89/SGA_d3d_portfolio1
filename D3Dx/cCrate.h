#pragma once
#include "cActionObj.h"


class cCrate : public cActionObj
{
public:
	cCrate();
	~cCrate();


	virtual void Setup()	override;
	virtual void Update()	override;
	virtual void Render()	override;

};


