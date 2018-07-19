#include "stdafx.h"
#include "cWMapMenu.h"

#include "UIButton.h"
#include "UIImage.h"
#include "UIText.h"

cWMapMenu::cWMapMenu()
	: m_pSprite(NULL)
	, m_pRootUI(NULL)
{
}

cWMapMenu::~cWMapMenu()
{
}

void cWMapMenu::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	UIImage* pImage = new UIImage(m_pSprite);
	pImage->SetTexture(_T("./Resources/ui/UI_Select.png"));
	m_pRootUI = pImage;

	UIText* pText = new UIText(g_pFontManager->GetFont(eFontType::FT_TIME), m_pSprite);

	m_pRootUI->AddChild(pText);
	pText->m_text = _T("Push the                Button");
	pText->m_size = D3DXVECTOR2(312, 200);
	pText->setPosition(&D3DXVECTOR3(0, -50, 0));
	pText->SetName(_T("textview"));

	UIImage* pImage2 = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage2);
	pImage2->SetTexture(_T("./Resources/ui/Keyboard_Space.png"));
	pImage2->m_size = D3DXVECTOR2(100, 100);
	pImage2->setPosition(&D3DXVECTOR3(120, 5, 0));
	pImage2->SetName(_T("spacebutton"));

	UIImage* pImage3 = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage3);
	pImage3->SetTexture(_T("./Resources/ui/Engagment_Bar.png"));
	pImage3->m_size = D3DXVECTOR2(WINSIZEX, 200);
	pImage3->setPosition(&D3DXVECTOR3(180, WINSIZEY - 240, 0));
	pImage3->SetName(_T("bar"));


	UIButton* pButton = new UIButton(this, m_pSprite, 1);
	m_pRootUI->AddChild(pButton);
	pButton->setPosition(&D3DXVECTOR3(WINSIZEX / 2 - 320, WINSIZEY - 220, 0));
	pButton->SetTexture(_T("./Resources/ui/btn-med-up.png.png"), _T("./Resources/ui/btn-med-over.png.png"), _T("./Resources/ui/btn-med-down.png.png"));

	pButton->SetText(g_pFontManager->GetFont(eFontType::FT_TIME), _T("Button1"));
	pButton->SetName(_T("button1"));

	pButton = new UIButton(this, m_pSprite);
	m_pRootUI->AddChild(pButton);
	pButton->setPosition(&D3DXVECTOR3(WINSIZEX / 2 + 100, WINSIZEY - 220, 0));
	pButton->SetTexture(_T("./Resources/ui/btn-med-up.png.png"), _T("./Resources/ui/btn-med-over.png.png"), _T("./Resources/ui/btn-med-down.png.png"));

	pButton->SetText(g_pFontManager->GetFont(eFontType::FT_TIME), _T("Button2"));
	pButton->SetName(_T("button2"));

	D3DXMATRIXA16 matS, matR, matT;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	//D3DXMatrixScaling(&matS, 1.5f, 0.8f, 0);
	//D3DXMatrixRotationZ(&matR, D3DX_PI / 3.0f);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);


	m_matWorld = matS * matR * matT;
}

void cWMapMenu::Update()
{
	m_pRootUI->Update();
}

void cWMapMenu::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);

	m_pRootUI->Render();

	m_pSprite->End();
}

void cWMapMenu::Release()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pRootUI);
}

void cWMapMenu::OnClick(UIButton * pSender)
{
	if (pSender->GetName() == _T("button1"))
	{
		UIText* pUIText = (UIText*)m_pRootUI->FindChildByName(_T("textview"));
		pUIText->m_text = _T("button1 pressed");
	}
	else if (pSender->GetName() == _T("button2"))
	{
		UIText* pUIText = (UIText*)m_pRootUI->FindChildByName(_T("textview"));
		pUIText->m_text = _T("button2 pressed");
	}
}
