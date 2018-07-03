#pragma once
#include "cGameNode.h"

class cTestScene1 : public cGameNode
{
private:
	LPD3DXFONT				m_pFont;

public:
	cTestScene1();
	~cTestScene1();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

