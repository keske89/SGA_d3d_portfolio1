#pragma once

class cOrder
{
protected :
	D3DXMATRIX					m_matWorld;
	std::vector<cOrder*>		m_vecChild;
	ST_UI_SIZE					m_stSize;
	int							m_cost;
	float count;

	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(cOrder*, m_pParent, Parent);
	


public:
	cOrder();
	virtual ~cOrder();

	virtual void AddChild(cOrder* pChild);
	virtual void Destroy();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual int GetCost() { return m_cost; }
	virtual float GetCount() { return count; }
	
};

