#include "stdafx.h"
#include "cOrderImage.h"


cOrderImage::cOrderImage()
	: m_pTexture(NULL)
{
}


cOrderImage::~cOrderImage()
{
}

void cOrderImage::SetTexture(const WCHAR* szFullPath)
{
	D3DXIMAGE_INFO	stImageInfo;
	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);
	if (szFullPath == L"Resources/Texture2D/Order_Onion.png") //양파수프
	{
		m_cost = 300;
	}
	else if (szFullPath == L"Resources/Texture2D/Order_Tomato.png") // 토마토수프
	{
		m_cost = 3000;
	}
	
	m_stSize.nHeight = stImageInfo.Height;
	m_stSize.nWidth = stImageInfo.Width;
	count = m_stSize.nWidth;
}

void cOrderImage::Render(LPD3DXSPRITE pSprite)
{
	count--;
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT pgBar;
	SetRect(&pgBar, 0, 0, count, 50);
	

	pSprite->End();

	//cOrder::Render(pSprite);
}
