#pragma once
#include "stdafx.h"
#include "cGameNode.h"

class cIntroScene : public cGameNode
{
public:
	cIntroScene();
	~cIntroScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

