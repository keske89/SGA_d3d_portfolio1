#include "stdafx.h"
#include "cStageMapToolUI.h"


cStageMapToolUI::cStageMapToolUI()
	: m_pSprite(NULL)
	, m_nSelectTileNum(0)
	, m_eTileType(TT_FLOOR)
{
}


cStageMapToolUI::~cStageMapToolUI()
{
	SAFE_RELEASE(m_pSprite);
}

void cStageMapToolUI::Setup()
{
	//바닥 타일 세팅
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	D3DXMATRIX matT, matS;
	g_pD3DDevice->GetViewport(&VP);
	for (int i = 0; i < (MAX_FLOOR_TILE / 10) + 1; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (i * 10 + j >= MAX_FLOOR_TILE) break;
			WCHAR buffer[128];
			int num = i * 10 + j + 1;
			wsprintf(buffer, L"./Resources/StageTexture/FloorTile_%d.png", num);
			m_stFloorTile[i * 10 + j].wstrTexture = buffer;
			g_pTextureManager->GetTexture(m_stFloorTile[i * 10 + j].wstrTexture.c_str(), &m_stFloorTile[i * 10 + j].imageInfo);
			D3DXMatrixScaling(&matS, 50.0f / (float)(m_stFloorTile[i * 10 + j].imageInfo.Width), 50.0f / (float)(m_stFloorTile[i * 10 + j].imageInfo.Height), 1.0f);
			D3DXMatrixTranslation(&matT, VP.Width - (60 * (i + 1)) + 5, (60 * j) + 5, 0);
			m_stFloorTile[i * 10 + j].matrix = matS * matT;
		}
	}
	m_stSelectButton.wstrTexture = L"./Resources/StageTexture/FloorTile_0.png";
	g_pTextureManager->GetTexture(m_stSelectButton.wstrTexture.c_str(), &m_stSelectButton.imageInfo);
	//
}

void cStageMapToolUI::Update()
{
	int xNum = m_nSelectTileNum / 10;
	int yNum = m_nSelectTileNum % 10;
	D3DXMatrixTranslation(&m_stSelectButton.matrix, VP.Width - (60 * (xNum + 1)), 60 * yNum, 0);
}

void cStageMapToolUI::Render()
{
	if (m_pSprite && m_eTileType == TT_FLOOR)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		for (int i = 0; i < MAX_FLOOR_TILE; ++i)
		{
			m_pSprite->SetTransform(&m_stFloorTile[i].matrix);
			m_pSprite->Draw(
				g_pTextureManager->GetTexture(m_stFloorTile[i].wstrTexture.c_str()),
				NULL,
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		m_pSprite->SetTransform(&m_stSelectButton.matrix);
		m_pSprite->Draw(
			g_pTextureManager->GetTexture(m_stSelectButton.wstrTexture.c_str()),
			NULL,
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pSprite->End();
	}
}

bool cStageMapToolUI::SelectTile(int& num)
{
	RECT rc;
	for (int i = 0; i < MAX_FLOOR_TILE; ++i)
	{
		SetRect(&rc,
			(int)m_stFloorTile[i].matrix._41,
			(int)m_stFloorTile[i].matrix._42,
			(int)m_stFloorTile[i].matrix._41 + 50,
			(int)m_stFloorTile[i].matrix._42 + 50);
		if (PtInRect(&rc, _ptMouse))
		{
			m_nSelectTileNum = i;
			num = i;
			return true;
		}
	}

	return false;
}