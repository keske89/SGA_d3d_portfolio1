#pragma once
#include "stdafx.h"
#include "cGameNode.h"

#include "iUIObject.h"

class cIntroLogo;
class cIntroUI;

class cIntroScene : public cGameNode
{
private:
	cIntroUI * m_UI;
	cIntroLogo* m_Logo;

public:
	cIntroScene();
	~cIntroScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

