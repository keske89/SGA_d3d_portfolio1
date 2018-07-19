#pragma once
#include "cWMDefinition.h"
#include "IDisplayObject.h"

#include "UIButton.h"

class cWMapMenu : public IDisplayObject, public IUIButtonDelegate
{
private:
	LPD3DXSPRITE m_pSprite;
	iUIObject* m_pRootUI;

public:
	cWMapMenu();
	virtual ~cWMapMenu();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;
};
