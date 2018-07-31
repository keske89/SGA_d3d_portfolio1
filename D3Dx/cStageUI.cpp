#include "stdafx.h"
#include "cStageUI.h"


cStageUI::cStageUI()
	: m_nTimer(240)
	, m_pTimerTexture(NULL)
	, m_pNumberTexture(NULL)
	, m_pCoinTexture(NULL)
	, m_nOutroTimer(0)
{
}


cStageUI::~cStageUI()
{
	SAFE_RELEASE(m_pSprite);
}

void cStageUI::Setup()
{
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
	D3DXMatrixTransformation2D(&m_matCoinNumber0, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(180, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matCoinNumber1, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(120, m_VP.Height - 150));
	D3DXMatrixTransformation2D(&m_matCoinNumber2, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(60, m_VP.Height - 150));
	m_pMinusTexture = g_pTextureManager->GetTexture(L"./Resources/StageTexture/Minus.png", &m_STMinusImageInfo);
	D3DXMatrixTransformation2D(&m_matMinus, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), NULL, 0.0f, &D3DXVECTOR2(0, m_VP.Height - 150));
	m_pReadyTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/LevelIntro_Ready.png", &m_STReadyImageInfo);
	m_pGoTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/LevelIntro_Go.png", &m_STGoImageInfo);
	m_pStarTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/ScoreSummary_Star.png", &m_STStarImageInfo);
	m_pTimeUpTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/ScoreSummary_TimesUp.png", &m_STTimeUpImageInfo);
	D3DXMatrixTransformation2D(&m_matOutro, NULL, 0.0f, &D3DXVECTOR2(1.0f, 1.0f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width / 2.0f - 447, m_VP.Height / 2.0f - 100));
	m_pPauseTexture = g_pTextureManager->GetTexture(L"./Resources/StageTexture/Pause.png", &m_STPauseImageInfo);
	D3DXMatrixTransformation2D(&m_matPause, NULL, 0.0f, &D3DXVECTOR2(2.0f, 2.0f), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width / 2.0f - 300, m_VP.Height / 2.0f - 165));

	SOUNDMANAGER->addSound("1UpSound", "./Sound/smb_1-up.wav", false, false);
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
	bool isNegative = false;
	if (DATABASE->GetTip() < 0)
	{
		CS0 *= -1;
		CS1 *= -1;
		CS2 *= -1;
		isNegative = true;
	}
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
		if (isNegative == true)
		{
			m_pSprite->SetTransform(&m_matMinus);
			m_pSprite->Draw(
				m_pMinusTexture,
				NULL,
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		m_pSprite->End();
	}
}

bool cStageUI::StageIntro(int timer)
{
	if (timer < 240)
	{
		float fScale = timer / 240.0f;
		D3DXMatrixTransformation2D(&m_matIntro, NULL, 0.0f, &D3DXVECTOR2(0.2f * fScale, 0.2f * fScale), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width / 2.0f - 150.0f * fScale, m_VP.Height / 2.0f - 50.0f * fScale));
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pSprite->SetTransform(&m_matIntro);
		m_pSprite->Draw(
			m_pReadyTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->End();
		return false;
	}
	else if (timer < 360)
	{
		float fScale = (timer - 240.0f) / 120.0f;
		D3DXMatrixTransformation2D(&m_matIntro, NULL, 0.0f, &D3DXVECTOR2(0.2f * fScale, 0.2f * fScale), NULL, 0.0f, &D3DXVECTOR2(m_VP.Width / 2.0f - 150.0f * fScale, m_VP.Height / 2.0f - 50.0f * fScale));
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pSprite->SetTransform(&m_matIntro);
		m_pSprite->Draw(
			m_pGoTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->End();
		return false;
	}
	else return true;
}

bool cStageUI::StageOutro()
{
	m_nOutroTimer++;
	int stage = 0;
	if (m_nOutroTimer < 120) stage = 0;
	else if (m_nOutroTimer == 120) stage = 1;
	else if (m_nOutroTimer < 240) stage = 2;
	else if (m_nOutroTimer == 240) stage = 3;
	else if (m_nOutroTimer < 360) stage = 4;
	else if (m_nOutroTimer == 360) stage = 5;
	else if (m_nOutroTimer < 480) stage = 6;
	else stage = 6;

	if (m_nOutroTimer == 480) return false;

	if (stage == 0)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pSprite->SetTransform(&m_matOutro);
		m_pSprite->Draw(
			m_pTimeUpTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->End();
		return true;
	}
	else if (stage == 1 && DATABASE->GetTip() >= 40)
	{
		SOUNDMANAGER->play("1UpSound", CH_STAGE_EFFECT, 1.0f);
		DATABASE->setStageStar(DATABASE->GetstageNum() - 1, 1);
		return true;
	}
	else if (stage == 3 && DATABASE->GetTip() >= 80)
	{
		SOUNDMANAGER->play("1UpSound", CH_STAGE_EFFECT, 1.0f);
		DATABASE->setStageStar(DATABASE->GetstageNum() - 1, 2);
		return true;
	}
	else if (stage == 5 && DATABASE->GetTip() >= 160)
	{
		SOUNDMANAGER->play("1UpSound", CH_STAGE_EFFECT, 1.0f);
		DATABASE->setStageStar(DATABASE->GetstageNum() - 1, 3);
		return true;
	}
	float angle = ((m_nOutroTimer % 360) / 360.f) * D3DX_PI * 2.0f;
	if (stage > 1 && DATABASE->GetTip() >= 40)
	{
		D3DXMatrixTransformation2D(&m_matStar1, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), &D3DXVECTOR2(64, 64), angle, &D3DXVECTOR2(m_VP.Width / 2.0f - 64, m_VP.Height / 2.0f - 64));
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pSprite->SetTransform(&m_matStar1);
		m_pSprite->Draw(
			m_pStarTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->End();
	}
	if (stage > 3 && DATABASE->GetTip() >= 80)
	{
		D3DXMatrixTransformation2D(&m_matStar2, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), &D3DXVECTOR2(64, 64), angle, &D3DXVECTOR2(m_VP.Width / 2.0f - 64 - 128, m_VP.Height / 2.0f - 64));
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pSprite->SetTransform(&m_matStar2);
		m_pSprite->Draw(
			m_pStarTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->End();
	}
	if (stage > 5 && DATABASE->GetTip() >= 160)
	{
		D3DXMatrixTransformation2D(&m_matStar3, NULL, 0.0f, &D3DXVECTOR2(0.25f, 0.25f), &D3DXVECTOR2(64, 64), angle, &D3DXVECTOR2(m_VP.Width / 2.0f - 64 + 128, m_VP.Height / 2.0f - 64));
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pSprite->SetTransform(&m_matStar3);
		m_pSprite->Draw(
			m_pStarTexture,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->End();
		return true;
	}
	else
	{
		return true;
	}
}

void cStageUI::RenderPause()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matPause);
	m_pSprite->Draw(
		m_pPauseTexture,
		NULL,
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pSprite->End();
}
