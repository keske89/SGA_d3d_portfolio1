#pragma once
#include "cGameNode.h"

class cTestScene2 : public cGameNode
{
private:
	LPD3DXFONT				m_pFont;

public:
	cTestScene2();
	~cTestScene2();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};