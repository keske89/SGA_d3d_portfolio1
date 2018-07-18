#include "stdafx.h"
#include "cIntroUI.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UIText.h"


cIntroUI::cIntroUI()
	: m_pSprite(NULL)
	, m_pRootUI(NULL)
	, m_buttonSelect(BUTTON_1)

{
}

cIntroUI::~cIntroUI()
{
}

void cIntroUI::Setup()
{
	_isChange = false;
	_alpha = 0;
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	UIImage* pImage = new UIImage(m_pSprite);
	pImage->SetTexture(_T("./Resources/ui/SummaryScreen_Background.png"));
	m_pRootUI = pImage;

	//pImage = new UIImage(m_pSprite);
	//m_pRootUI->AddChild(pImage);
	//pImage->SetPosition(&D3DXVECTOR3(0, 100, 0));
	//pImage->setRotation(&D3DXVECTOR3(0, 100, 103));
	//pImage->m_size = D3DXVECTOR2(312, 200);
	//pImage->SetTexture(_T("./ui/logo.png"));
	//pImage->SetName(_T("LOGO"));

	UIText* pText = new UIText(g_pFontManager->GetFont(eFontType::FT_QUEST), m_pSprite);

	m_pRootUI->AddChild(pText);
	pText->m_text = _T("Press    A    to Continue");
	pText->m_size = D3DXVECTOR2(312, 200);
	pText->setColor(D3DXCOLOR(0, 0, 0, 1));
	pText->setPosition(&D3DXVECTOR3(850, 120, 0));
	pText->SetName(_T("textview"));

	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->setPosition(&D3DXVECTOR3(940, 190, 0));
	pImage->m_size = D3DXVECTOR2(312, 200);
	pImage->SetTexture(_T("./Resources/ui/A_Icon.png"));
	pImage->SetName(_T("ABUTTON"));

	UIButton* pButton = new UIButton(this, m_pSprite, 1);
	m_pRootUI->AddChild(pButton);
	pButton->setPosition(&D3DXVECTOR3(880, 400, 0));
	pButton->SetTexture(_T("./Resources/ui/btn-med-up.png.png"), _T("./Resources/ui/btn-med-over.png.png"), _T("./Resources/ui/btn-med-down.png.png"));

	pButton->SetText(g_pFontManager->GetFont(eFontType::FT_TIME), _T("NEW GAME"));
	pButton->SetName(_T("button1"));

	pButton = new UIButton(this, m_pSprite, 1);
	m_pRootUI->AddChild(pButton);
	pButton->setPosition(&D3DXVECTOR3(880, 510, 0));
	pButton->SetTexture(_T("./Resources/ui/btn-med-up.png.png"), _T("./Resources/ui/btn-med-over.png.png"), _T("./Resources/ui/btn-med-down.png.png"));

	pButton->SetText(g_pFontManager->GetFont(eFontType::FT_TIME), _T("LOAD GAME"));
	pButton->SetName(_T("button2"));

	D3DXMATRIXA16 matS, matR, matT;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	//D3DXMatrixScaling(&matS, 1.5f, 0.8f, 0);
	//D3DXMatrixRotationZ(&matR, D3DX_PI / 3.0f);
	D3DXMatrixRotationYawPitchRoll(&matR, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);


	m_matWorld = matS * matR * matT;
}

void cIntroUI::Update()
{
	if (_isChange)
	{
		_alpha++;
		if (_alpha >= 255)
		{
			if (_nextScene == "WMScene")
			{
				SCENEMANAGER->ChangeScene("WMScene");
				SCENEMANAGER->Setup();
			}
		}
	}
	else
	{
		m_pRootUI->Update();
		IntroControl();
	}

	//D3DXMATRIX matS, matR, matT;
	////D3DXMatrixIdentity(&matS);
	////D3DXMatrixIdentity(&matR);
	////D3DXMatrixIdentity(&matT);

	////D3DXMatrixScaling(&matS, 1.5f, 0.8f, 0);
	//D3DXMatrixRotationZ(&matR, D3DX_PI);
	////D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//UIImage* pImage = (UIImage*)m_pRootUI->FindChildByName(_T("LOGO"));
	//pImage->SetWorldMatrix(&matR);

	////m_matWorld = matS * matR * matT;
}

void cIntroUI::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);

	m_pRootUI->Render();
	m_pSprite->End();

	if (_isChange)
		IMAGEMANAGER->alphaRender(_T("blackMask"), _alpha);
}

void cIntroUI::Release()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pRootUI);
}

void cIntroUI::IntroControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		m_buttonSelect++;
		if (m_buttonSelect > 1) m_buttonSelect = BUTTON_1;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

		m_buttonSelect--;
		if (m_buttonSelect < 0) m_buttonSelect = BUTTON_2;
	}



	if (m_buttonSelect == BUTTON_1)
	{
		UIButton* pUIButton1 = (UIButton*)m_pRootUI->FindChildByName(_T("button1"));
		pUIButton1->SetCheck(true);
		UIButton* pUIButton2 = (UIButton*)m_pRootUI->FindChildByName(_T("button2"));
		pUIButton2->SetCheck(false);
	}
	else if (m_buttonSelect == BUTTON_2)
	{
		UIButton* pUIButton1 = (UIButton*)m_pRootUI->FindChildByName(_T("button1"));
		pUIButton1->SetCheck(false);
		UIButton* pUIButton2 = (UIButton*)m_pRootUI->FindChildByName(_T("button2"));
		pUIButton2->SetCheck(true);
	}

}

void cIntroUI::OnClick(UIButton * pSender)
{
	if (pSender->GetName() == _T("button1"))
	{
		_nextScene = "WMScene";
		_isChange = true;
	}
	else if (pSender->GetName() == _T("button2"))
	{
		UIText* pUIText = (UIText*)m_pRootUI->FindChildByName(_T("textview"));
		pUIText->m_text = _T("button2 pressed");
	}
}
