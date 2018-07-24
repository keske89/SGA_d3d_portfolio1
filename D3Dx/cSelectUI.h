#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"

enum BUTTONSELECT
{
	SELECTNUM_BRAR,
	SELECTNUM_BEARD,
	SELECTNUM_BLACKCAT,
	SELECTNUM_BOOF,
	SELECTNUM_BOX,
	SELECTNUM_BUCK,
	SELECTNUM_DINO,
	SELECTNUM_DOG
};

class UIObject;

class cSelectUI :	public IDisplayObject, public IUIButtonDelegate
{
private:
	LPD3DXSPRITE	m_pSprite;

	iUIObject*		m_pRootUI;
	UIObject *		m_pSelectCharater[2];
	int				m_buttonSelect;

	BYTE			_alpha;
	bool			_isChange;
	bool			_isMod;
	string			_nextScene;
public:
	cSelectUI();
	~cSelectUI();
	void SelectControl();
	void ChangeCharater();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;
};

