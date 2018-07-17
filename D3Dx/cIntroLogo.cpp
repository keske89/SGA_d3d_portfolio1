#include "stdafx.h"
#include "cIntroLogo.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UIText.h"


cIntroLogo::cIntroLogo()
	: m_pSprite(NULL)
	, m_pRootUI(NULL)
	, m_fRot(0.0f)
	, m_nState(1)
{
}


cIntroLogo::~cIntroLogo()
{
}

void cIntroLogo::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	UIImage* pImage = new UIImage(m_pSprite);
	pImage->SetTexture(_T("./Resources/ui/logo.png"));
	m_pRootUI = pImage;

	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, 10, 50, 0);
	m_matLocal = matT;
}

void cIntroLogo::Update()
{
	m_pRootUI->Update();
	logoAnimation();
}

void cIntroLogo::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);

	m_pRootUI->Render();
	m_pSprite->End();
}

void cIntroLogo::Release()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pRootUI);
}

void cIntroLogo::logoAnimation()
{
	int n = 3;
	float f1 = 0.1; // speed;
	float f2 = 1.0f - m_fRot / n; //t


	m_fRot += m_nState * f1;

	if (m_fRot >= n)
	{
		m_nState *= -1;
	}
	else if (m_fRot <= -n)
	{
		m_nState *= -1;
	}


	D3DXMATRIX matR;
	D3DXMatrixRotationZ(&matR, D3DXToRadian(m_fRot));
	m_matWorld = m_matLocal * matR;
}
