#pragma once
#include "cWMDefinition.h"
#include "UIButton.h"

enum BUTTONSELECT
{
	BUTTON_1,	//NEW
	BUTTON_2,	//LOAD
	BUTTON_END
};

class cIntroUI :public IDisplayObject, public IUIButtonDelegate
{
private:
	LPD3DXSPRITE m_pSprite;

	iUIObject* m_pRootUI;
	int m_buttonSelect;

	BYTE _alpha;
	bool _isChange;
	string _nextScene;

public:
	cIntroUI();
	~cIntroUI();

	void IntroControl();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;
};

