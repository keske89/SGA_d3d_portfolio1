#pragma once
#include "cWMDefinition.h"
#include "iUIObject.h"

class UIText : public iUIObject
{
public:
	LPD3DXFONT m_pFont;
	LPCTSTR m_text;
	DWORD m_drawTextFormat;

	UIText(LPD3DXFONT pFont, LPD3DXSPRITE pSprite);
	virtual ~UIText();

	void Render() override;
	void Release();
};

