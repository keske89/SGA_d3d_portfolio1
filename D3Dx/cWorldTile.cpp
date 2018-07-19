#include "stdafx.h"
#include "cWorldTile.h"

#include "cWorldMapObj.h"

cWorldTile::cWorldTile()
	:m_Type(TILE_SAND)
	, m_pTile(NULL)
	, m_bAnimation(false)
	, m_nIdx(0)
	, m_ani(5.0f)
{
}


cWorldTile::~cWorldTile()
{
}

void cWorldTile::Setup()
{
	D3DXMATRIX matS, matT, matST;
	D3DXMatrixScaling(&matS, 0.06f, 1.0f, 0.06f);
	D3DXMatrixTranslation(&matT, 0, 0.0f, 0);
	matST = matS * matT;


	if (m_Type == TILE_GRASS)
	{
		m_pTile = new cWorldMapObj; ((cWorldMapObj*)m_pTile)->SetFilename(_T("./map/"), _T("Map_Tile_Top.obj"), _T("./map/Grass.png"));  m_pTile->SetLocalMatrix(&matST); m_pTile->Setup();
	}
	else if (m_Type == TILE_WATER)
	{
		m_pTile = new cWorldMapObj; ((cWorldMapObj*)m_pTile)->SetFilename(_T("./map/"), _T("Map_Tile_Top.obj"), _T("./map/water.png"));  m_pTile->SetLocalMatrix(&matST); m_pTile->Setup();
	}
	else if (m_Type == TILE_SAND)
	{
		m_pTile = new cWorldMapObj; ((cWorldMapObj*)m_pTile)->SetFilename(_T("./map/"), _T("Map_Tile_Top.obj"), _T("./map/DLC_MapSand.png"));  m_pTile->SetLocalMatrix(&matST); m_pTile->Setup();
	}
}

void cWorldTile::Update()
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y - m_ani, m_vPosition.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_rot.y, m_rot.x, m_rot.z);

	m_matWorld = matR * matT;

	if (m_bAnimation)
	{
		this->Animation(m_nIdx);
	}
}

void cWorldTile::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pTile->Render();
}

void cWorldTile::Release()
{
	SAFE_RELEASE(m_pTile);
}

void cWorldTile::Animation(int idx)
{
	if (m_ani > 0.0f)
	{
		m_ani -= 0.1f;
	}

	if (m_rot.x < 2 * D3DX_PI)
	{
		m_rot.x += 0.08f - idx * 0.002;
	}
}
