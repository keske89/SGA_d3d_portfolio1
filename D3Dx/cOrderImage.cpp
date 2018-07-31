#include "stdafx.h"
#include "cOrderImage.h"


cOrderImage::cOrderImage()
	: m_pTexture(NULL)
	, m_pBarTexture(NULL)
{
	D3DXMatrixIdentity(&mat_Shake);
}


cOrderImage::~cOrderImage()
{
	//SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pgBar);
	//SAFE_RELEASE(m_pBarTexture);
}

void cOrderImage::SetTexture(const WCHAR* szFullPath)
{
	D3DXIMAGE_INFO	stImageInfo, m_stImageInfo ;
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

	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
	D3DXCreateSprite(g_pD3DDevice, &m_pgBar);
	m_pBarTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Bar.png", &m_stImageInfo);

	count = (float)m_stImageInfo.Width;
}

void cOrderImage::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));
	pSprite->End();

	m_pgBar->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pgBar->SetTransform(&m_matWorld);
	RECT pgBar;
	SetRect(&pgBar, 0, m_stSize.nHeight, count, 50);
	m_pgBar->Draw(m_pBarTexture, &pgBar,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pgBar->End();

	//cOrder::Render(pSprite);
}



void cOrderImage::Shaking()
{
	D3DXMATRIX rotY;
	D3DXVECTOR3 v(0, 1, 0);
	D3DXMatrixIdentity(&rotY);
	D3DXMatrixRotationAxis(&rotY, &v, D3DX_PI / 6);
	mat_Shake = rotY;
}
