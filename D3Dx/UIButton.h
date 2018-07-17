#pragma once
#include "cWMDefinition.h"
#include "iUIObject.h"

class UIButton;
class UIText;

class IUIButtonDelegate
{
public:
	virtual void OnClick(UIButton* pSender) = 0;
	void Release() { delete this; }
};

class UIButton : public iUIObject
{
private:
	enum ButtonState
	{
		NORMAL,
		MOUSEOVER,
		SELECTED,
		COUNT
	};
	enum InterfaceType
	{
		KEYBOARD,
		MOUSE,
		BOTH,
		InterfaceEnd
	};
	int m_type;
	ButtonState m_buttonState;

	bool m_bCheck;

public:
	IUIButtonDelegate * m_pDelegate;
	LPDIRECT3DTEXTURE9 m_aTexture[COUNT];
	UIText* m_pText;

	UIButton(IUIButtonDelegate* pDelegate, LPD3DXSPRITE pSprite);
	UIButton(IUIButtonDelegate* pDelegate, LPD3DXSPRITE pSprite, int type);
	virtual ~UIButton();


	void Update() override;
	void Render() override;
	void Release() override;

	void KeyBoardControl();
	void MouseControl();

	void SetTexture(LPCTSTR normal, LPCTSTR mouseOver, LPCTSTR selected);
	void SetText(LPD3DXFONT pFont, LPCTSTR text);

	void SetCheck(bool check) { m_bCheck = check; }
	bool GetCheck() { return m_bCheck; }

};

