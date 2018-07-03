#pragma once
#include "cGameNode.h"

class cTestScene3 : public cGameNode
{
private:
	LPD3DXFONT				m_pFont;

public:
	cTestScene3();
	~cTestScene3();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};