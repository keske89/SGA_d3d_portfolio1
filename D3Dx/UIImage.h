#pragma once
#include "cWMDefinition.h"
#include "iUIObject.h"

class UIImage : public iUIObject
{
public:
	LPDIRECT3DTEXTURE9 m_pTex;

	UIImage(LPD3DXSPRITE pSprite);
	virtual ~UIImage();

	void Render() override;
	void RotateImage();
	void SetTexture(LPCTSTR filename);
	void SetSize(D3DXVECTOR2 size) { m_size = size; }
};

