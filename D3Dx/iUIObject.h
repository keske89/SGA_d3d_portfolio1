#pragma once
#include "IDisplayObject.h"
#include "cWMDefinition.h"

class iUIObject : public IDisplayObject
{
protected:
	LPD3DXSPRITE m_pSprite;

public:
	D3DXVECTOR3 m_combinedPos;
	D3DXVECTOR3 m_pivot;
	D3DXVECTOR2 m_size;
	D3DCOLOR	m_color;

	bool m_bDrawBorder;

public:
	iUIObject(LPD3DXSPRITE pSprite);
	virtual ~iUIObject();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void setColor(D3DCOLOR color) { m_color = color; }

	void UpdateCombinedPosition();
	void DrawBorder();
	void GetFinalRect(RECT* rect);
	D3DXVECTOR3* GetCombinedPos() { return &m_combinedPos; }

	D3DXVECTOR2 GetSize() { return m_size; }
};

