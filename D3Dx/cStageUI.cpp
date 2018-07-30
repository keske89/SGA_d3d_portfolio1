#include "stdafx.h"
#include "cStageUI.h"


cStageUI::cStageUI()
	: m_nTimer(240)
	, m_pTimerTexture(NULL)
	, m_pNumberTexture(NULL)
	, m_pCoinTexture(NULL)
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
	m_pCoinTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/Points_Background.png", &m_STCoinImageInfo);
	D3DXMatrixTransformation2D(&m_matCoin, NULL, 0.0f, &D3DXVECTOR2(0.4f, 0.4f), NULL, 0.0f, &D3DXVECTOR2(0, m_VP.Height - 210));
	m_pNumberTexture = g_pTextureManager->GetTexture(L"./Resources/StageTexture/Numbers.png", &m_STNumberImageInfo);
	D3DXMatrixTransformation2D(&m_matNumberSecond0, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width - 70, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matNumberSecond1, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width - 140, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matNumberSecond2, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width - 210, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matCoinNumber0, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(140, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matCoinNumber1, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(70, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matCoinNumber2, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(0, m_VP.Height - 150));
	m_nTimer = 300 * 60;
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
	int CS0 = DATABASE->GetTip();
	int CS1 = DATABASE->GetTip();
	int CS2 = DATABASE->GetTip();
	CS0 = CS0 % 10;
	CS1 /= 10;
	CS1 = CS1 % 10;
	CS2 /= 100;
	CS2 = CS2 % 10;

	if (m_pSprite)
	{
		//m_pSprite->SetWorldViewLH(Matrix.Scaling(0.2f, 0.2f, 0.2f), NULL);
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		//타이머 그리기//////////////////////////////////////////////////////////////////////////////////////
		m_pSprite->SetTransform(&m_matTimer);
		m_pSprite->Draw(
			m_pTimerTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		if (NS2 > 0)
		{
			m_pSprite->SetTransform(&m_matNumberSecond2);
			m_pSprite->Draw(
				m_pNumberTexture,
				&getRect(0 + (NS2 % 5) * 280, 0 + (int)(NS2 / 5) * 420, 280 + (NS2 % 5) * 280, 420 + (int)(NS2 / 5) * 420),
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (!(NS2 == 0 && NS1 == 0))
		{
			m_pSprite->SetTransform(&m_matNumberSecond1);
			m_pSprite->Draw(
				m_pNumberTexture,
				&getRect(0 + (NS1 % 5) * 280, 0 + (int)(NS1 / 5) * 420, 280 + (NS1 % 5) * 280, 420 + (int)(NS1 / 5) * 420),
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		m_pSprite->SetTransform(&m_matNumberSecond0);
		m_pSprite->Draw(
			m_pNumberTexture,
			&getRect(0 + (NS0 % 5) * 280, 0 + (int)(NS0 / 5) * 420, 280 + (NS0 % 5) * 280, 420 + (int)(NS0 / 5) * 420),
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		//코인 그리기///////////////////////////////////////////////////////////////////////////////////////
		m_pSprite->SetTransform(&m_matCoin);
		m_pSprite->Draw(
			m_pCoinTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		if (CS2 > 0)
		{
			m_pSprite->SetTransform(&m_matCoinNumber2);
			m_pSprite->Draw(
				m_pNumberTexture,
				&getRect(0 + (CS2 % 5) * 280, 0 + (int)(CS2 / 5) * 420, 280 + (CS2 % 5) * 280, 420 + (int)(CS2 / 5) * 420),
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (!(CS2 == 0 && CS1 == 0))
		{
			m_pSprite->SetTransform(&m_matCoinNumber1);
			m_pSprite->Draw(
				m_pNumberTexture,
				&getRect(0 + (CS1 % 5) * 280, 0 + (int)(CS1 / 5) * 420, 280 + (CS1 % 5) * 280, 420 + (int)(CS1 / 5) * 420),
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		m_pSprite->SetTransform(&m_matCoinNumber0);
		m_pSprite->Draw(
			m_pNumberTexture,
			&getRect(0 + (CS0 % 5) * 280, 0 + (int)(CS0 / 5) * 420, 280 + (CS0 % 5) * 280, 420 + (int)(CS0 / 5) * 420),
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pSprite->End();
	}
}
