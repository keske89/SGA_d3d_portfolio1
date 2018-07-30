#pragma once
#include "cOrder.h"

class cOrderImage : public cOrder
{
protected :
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXSPRITE		m_pgBar;
	int count;
public:
	cOrderImage();
	virtual ~cOrderImage();

	virtual void SetTexture(const WCHAR* szFullPath);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual int GetCost() { return m_cost; }
};

