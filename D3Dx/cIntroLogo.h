#pragma once
#include "cWMDefinition.h"
#include "UIImage.h"

class cIntroLogo : public IDisplayObject
{
private:
	LPD3DXSPRITE m_pSprite;
	iUIObject* m_pRootUI;

	float m_fRot;
	int m_nState;

public:
	cIntroLogo();
	~cIntroLogo();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Setup() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void Release() override;

	void logoAnimation();
};

