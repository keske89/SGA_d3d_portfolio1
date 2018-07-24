#include "stdafx.h"
#include "cStageUI.h"


cStageUI::cStageUI()
	: m_nTimer(180)
	, m_pTimerTexture(NULL)
	, m_pNumberTexture(NULL)
{
}


cStageUI::~cStageUI()
{
	SAFE_RELEASE(m_pSprite);
}

void cStageUI::Setup()
{
	D3DVIEWPORT9 m_VP;
	g_pD3DDevice->GetViewport(&m_VP);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	m_pTimerTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/Timer_Background.png", &m_STTimerImageInfo);
	//D3DXMatrixTranslation(&m_matTimer, 100, 100, 0);
	D3DXMatrixTransformation2D(&m_matTimer, NULL, 0.0f, &D3DXVECTOR2(0.2f, 0.2f), NULL, 0.0f, &D3DXVECTOR2(0, 0));
	m_pNumberTexture = g_pTextureManager->GetTexture(L"./Resources/StageTexture/Numbers.png", &m_STNumberImageInfo);
	D3DXMatrixTranslation(&m_matNumberMinute, 200, 100, 0);
	D3DXMatrixTranslation(&m_matNumberSecond1, 300, 100, 0);
	D3DXMatrixTranslation(&m_matNumberSecond2, 400, 100, 0);
}

void cStageUI::Update()
{
}

void cStageUI::Render()
{
	if (m_pSprite)
	{
		//m_pSprite->SetWorldViewLH(Matrix.Scaling(0.2f, 0.2f, 0.2f), NULL);
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		m_pSprite->SetTransform(&m_matTimer);
		m_pSprite->Draw(
			m_pTimerTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		//m_pSprite->SetTransform(&m_matNumberMinute);
		//m_pSprite->Draw(
		//	m_pNumberTexture,
		//	NULL,
		//	NULL,
		//	NULL,
		//	D3DCOLOR_ARGB(255, 255, 255, 255));
		//
		//m_pSprite->SetTransform(&m_matNumberSecond1);
		//m_pSprite->Draw(
		//	m_pNumberTexture,
		//	NULL,
		//	NULL,
		//	NULL,
		//	D3DCOLOR_ARGB(255, 255, 255, 255));
		//m_pSprite->SetTransform(&m_matNumberSecond2);
		//m_pSprite->Draw(
		//	m_pNumberTexture,
		//	NULL,
		//	NULL,
		//	NULL,
		//	D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pSprite->End();
	}
}
