#include "stdafx.h"
#include "cStageMapToolUI.h"


cStageMapToolUI::cStageMapToolUI()
	: m_pSprite(NULL)
	, m_nSelectTileNum(0)
	, m_nTextureNum(0)
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
	m_stTileSelectButton.wstrTexture = L"./Resources/StageTexture/FloorTile_0.png";
	g_pTextureManager->GetTexture(m_stTileSelectButton.wstrTexture.c_str(), &m_stTileSelectButton.imageInfo);
	//
	m_stMenuButton[MT_FLOOR].wstrTexture = L"./Resources/StageTexture/MenuFloor.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_FLOOR].wstrTexture.c_str(), &m_stMenuButton[MT_FLOOR].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_FLOOR].matrix, 0, 0, 0);

	m_stMenuButton[MT_OBJECT].wstrTexture = L"./Resources/StageTexture/MenuObject.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_OBJECT].wstrTexture.c_str(), &m_stMenuButton[MT_OBJECT].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_OBJECT].matrix, 0, 60, 0);

	m_stMenuButton[MT_NEWOBJ].wstrTexture = L"./Resources/StageTexture/MenuNewObj.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_NEWOBJ].wstrTexture.c_str(), &m_stMenuButton[MT_NEWOBJ].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_NEWOBJ].matrix, 0, 120, 0);

	m_stMenuButton[MT_BLOCK].wstrTexture = L"./Resources/StageTexture/MenuBlock.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_BLOCK].wstrTexture.c_str(), &m_stMenuButton[MT_BLOCK].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_BLOCK].matrix, 0, 180, 0);

	m_stMenuButton[MT_OPEN].wstrTexture = L"./Resources/StageTexture/MenuOpen.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_OPEN].wstrTexture.c_str(), &m_stMenuButton[MT_OPEN].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_OPEN].matrix, 0, 240, 0);

	m_stMenuButton[MT_SAVE].wstrTexture = L"./Resources/StageTexture/MenuSave.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_SAVE].wstrTexture.c_str(), &m_stMenuButton[MT_SAVE].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_SAVE].matrix, 0, 300, 0);

	m_stMenuButton[MT_LOAD].wstrTexture = L"./Resources/StageTexture/MenuLoad.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_LOAD].wstrTexture.c_str(), &m_stMenuButton[MT_LOAD].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_LOAD].matrix, 0, 360, 0);

	m_stMenuButton[MT_TEXTURE1].wstrTexture = L"./Resources/StageTexture/MenuTexture.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_TEXTURE1].wstrTexture.c_str(), &m_stMenuButton[MT_TEXTURE1].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_TEXTURE1].matrix, 0, 420, 0);

	m_stMenuButton[MT_TEXTURE2].wstrTexture = L"./Resources/StageTexture/MenuTexture.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_TEXTURE2].wstrTexture.c_str(), &m_stMenuButton[MT_TEXTURE2].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_TEXTURE2].matrix, 0, 480, 0);

	m_stMenuButton[MT_TEXTURE3].wstrTexture = L"./Resources/StageTexture/MenuTexture.png";
	g_pTextureManager->GetTexture(m_stMenuButton[MT_TEXTURE3].wstrTexture.c_str(), &m_stMenuButton[MT_TEXTURE3].imageInfo);
	D3DXMatrixTranslation(&m_stMenuButton[MT_TEXTURE3].matrix, 0, 540, 0);

	m_stMenuSelectButton.wstrTexture = L"./Resources/StageTexture/MenuSelect.png";
	g_pTextureManager->GetTexture(m_stMenuSelectButton.wstrTexture.c_str(), &m_stMenuSelectButton.imageInfo);
	D3DXMatrixTranslation(&m_stMenuSelectButton.matrix, 0, 0, 0);
}

void cStageMapToolUI::Update()
{
	int xNum = m_nSelectTileNum / 10;
	int yNum = m_nSelectTileNum % 10;
	D3DXMatrixTranslation(&m_stTileSelectButton.matrix, VP.Width - (60 * (xNum + 1)), 60 * yNum, 0);
}

void cStageMapToolUI::Render()
{
	if (m_pSprite)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		for (int i = 0; i < MT_TEXTURE1; ++i)
		{
			m_pSprite->SetTransform(&m_stMenuButton[i].matrix);
			m_pSprite->Draw(
				g_pTextureManager->GetTexture(m_stMenuButton[i].wstrTexture.c_str()),
				NULL,
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (m_eTileType == TT_FLOOR)
		{
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
			m_pSprite->SetTransform(&m_stTileSelectButton.matrix);
			m_pSprite->Draw(
				g_pTextureManager->GetTexture(m_stTileSelectButton.wstrTexture.c_str()),
				NULL,
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			m_pSprite->SetTransform(&m_stMenuButton[MT_FLOOR].matrix);
			m_pSprite->Draw(
				g_pTextureManager->GetTexture(m_stMenuSelectButton.wstrTexture.c_str()),
				NULL,
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else if (m_eTileType == TT_OBJECT)
		{
			m_pSprite->SetTransform(&m_stMenuButton[MT_OBJECT].matrix);
			m_pSprite->Draw(
				g_pTextureManager->GetTexture(m_stMenuSelectButton.wstrTexture.c_str()),
				NULL,
				NULL,
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			for (int i = 0; i < m_nTextureNum; ++i)
			{
				m_pSprite->SetTransform(&m_stMenuButton[MT_TEXTURE1 + i].matrix);
				m_pSprite->Draw(
					g_pTextureManager->GetTexture(m_stMenuButton[MT_TEXTURE1 + i].wstrTexture.c_str()),
					NULL,
					NULL,
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}


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

bool cStageMapToolUI::SelectMenu(int & num)
{
	RECT rc;
	for (int i = 0; i < MT_MAX; ++i)
	{
		SetRect(&rc,
			(int)m_stMenuButton[i].matrix._41 + 5,
			(int)m_stMenuButton[i].matrix._42 + 5,
			(int)m_stMenuButton[i].matrix._41 + 150,
			(int)m_stMenuButton[i].matrix._42 + 50);
		if (PtInRect(&rc, _ptMouse))
		{
			if (i >= MT_TEXTURE1 + m_nTextureNum)
			{
				return false;
			}
			if (i == MT_FLOOR)
			{
				m_eTileType = TT_FLOOR;
			}
			else if (i == MT_OBJECT)
			{
				m_eTileType = TT_OBJECT;
			}
			else
			{
				num = i;
			}
			return true;
		}
	}

	return false;
}
