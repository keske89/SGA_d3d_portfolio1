#include "stdafx.h"
#include "cStageUI.h"


cStageUI::cStageUI()
	: m_nTimer(240)
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
	D3DXMatrixTransformation2D(&m_matTimer, NULL, 0.0f, &D3DXVECTOR2(0.4f, 0.4f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width - 210, m_VP.Height - 210));
	m_pNumberTexture = g_pTextureManager->GetTexture(L"./Resources/StageTexture/Numbers.png", &m_STNumberImageInfo);
	D3DXMatrixTransformation2D(&m_matNumberSecond0, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width - 70, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matNumberSecond1, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width - 140, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matNumberSecond2, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width - 210, m_VP.Height - 150));
	m_nTimer = 240 * 60;
}

void cStageUI::Update()
{
	m_nTimer--;
}

void cStageUI::Render()
{
	int NS0 = m_nTimer / 60;
	int NS1 = m_nTimer / 60;
	int NS2 = m_nTimer / 60;
	NS0 = NS0 % 10;
	NS1 /= 10;
	NS1 = NS1 % 10;
	NS2 /= 100;
	NS2 = NS2 % 10;

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

		m_pSprite->SetTransform(&m_matNumberSecond0);
		m_pSprite->Draw(
			m_pNumberTexture,
			&getRect(0 + (NS0 % 5) * 280, 0 + (int)(NS0 / 5) * 420, 280 + (NS0 % 5) * 280, 420 + (int)(NS0 / 5) * 420),
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->SetTransform(&m_matNumberSecond1);
		m_pSprite->Draw(
			m_pNumberTexture,
			&getRect(0 + (NS1 % 5) * 280, 0 + (int)(NS1 / 5) * 420, 280 + (NS1 % 5) * 280, 420 + (int)(NS1 / 5) * 420),
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->SetTransform(&m_matNumberSecond2);
		m_pSprite->Draw(
			m_pNumberTexture,
			&getRect(0 + (NS2 % 5) * 280, 0 + (int)(NS2 / 5) * 420, 280 + (NS2 % 5) * 280, 420 + (int)(NS2 / 5) * 420),
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pSprite->End();
	}
}

RECT cStageUI::getRect(LONG left, LONG top, LONG right, LONG bottom)
{
	RECT result;
	result.left = left;
	result.top = top;
	result.right = right;
	result.bottom = bottom;
	return result;
}