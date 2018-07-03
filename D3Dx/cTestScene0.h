#pragma once
#include "cGameNode.h"

class cTestScene0 : public cGameNode
{
private:
	LPD3DXFONT				m_pFont;

public:
	cTestScene0();
	~cTestScene0();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};