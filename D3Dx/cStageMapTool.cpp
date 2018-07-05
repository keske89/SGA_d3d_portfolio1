#include "stdafx.h"
#include "cStageMapTool.h"
#include "cCamera.h"
#include "cStageGrid.h"
#include "cRay.h"
#include "cStageMapToolUI.h"


cStageMapTool::cStageMapTool()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pUI(NULL)
	, m_nTextureNum(0)
	, m_vecPos(0, 0, 0)
	, m_fRotAngle(0.0f)
	, m_nIndexX(0)
	, m_nIndexZ(0)
{
}


cStageMapTool::~cStageMapTool()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pUI);
}

void cStageMapTool::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cStageGrid;
	m_pGrid->Setup();

	m_pUI = new cStageMapToolUI;
	m_pUI->Setup();

	ST_PNT_VERTEX tempV;
	tempV.p = D3DXVECTOR3(-0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 0);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 1);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matTrans;
	D3DXMATRIX matTransAfterRot;
	D3DXMatrixRotationY(&matRot, m_fRotAngle);
	D3DXMatrixTranslation(&matTransAfterRot, 0.5f, 0, 0.5f);
	D3DXMatrixTranslation(&matTrans, m_nIndexX, 0, m_nIndexZ);
	m_stFloorTileTemplate.matFinal = matRot * matTransAfterRot * matTrans;
	m_stFloorTileTemplate.wstrTexture = m_pUI->getTileTexture(m_nTextureNum);
}

void cStageMapTool::Update()
{
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pUI)
		m_pUI->Update();

	Control();
}

void cStageMapTool::Render()
{
	if (m_pGrid)
		m_pGrid->Render();

	if (m_pUI)
		m_pUI->Render();

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (m_iterFloorTiles = m_mapFloorTiles.begin(); m_iterFloorTiles != m_mapFloorTiles.end(); ++m_iterFloorTiles)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_iterFloorTiles->second.matFinal);
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_iterFloorTiles->second.wstrTexture.c_str()));
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_iterFloorTiles->second.vecVertex.size() / 3, &m_iterFloorTiles->second.vecVertex[0], sizeof(ST_PNT_VERTEX));
	}
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_stFloorTileTemplate.matFinal);
	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_stFloorTileTemplate.wstrTexture.c_str()));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_stFloorTileTemplate.vecVertex.size() / 3, &m_stFloorTileTemplate.vecVertex[0], sizeof(ST_PNT_VERTEX));
}

void cStageMapTool::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cStageMapTool::Control()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_vecPos.z += 0.1f;
		m_pCamera->setVLookAt(m_vecPos);
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_vecPos.z -= 0.1f;
		m_pCamera->setVLookAt(m_vecPos);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_vecPos.x += 0.1f;
		m_pCamera->setVLookAt(m_vecPos);
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_vecPos.x -= 0.1f;
		m_pCamera->setVLookAt(m_vecPos);
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		m_fRotAngle -= D3DX_PI / 2.0f;
		if (m_fRotAngle <= -D3DX_PI * 2.0f)
			m_fRotAngle = 0.0f;
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		m_fRotAngle += D3DX_PI / 2.0f;
		if (m_fRotAngle >= D3DX_PI * 2.0f)
			m_fRotAngle = 0.0f;
	}

	cRay ray;
	float ratio = 0.0f;
	ratio = ray.getPickRayOrg().y / ray.getPickRayDir().y;
	m_nIndexX = (ray.getPickRayOrg().x - (ray.getPickRayDir().x * ratio));
	m_nIndexZ = (ray.getPickRayOrg().z - (ray.getPickRayDir().z * ratio));
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matTrans;
	D3DXMATRIX matTransAfterRot;
	D3DXMatrixRotationY(&matRot, m_fRotAngle);
	D3DXMatrixTranslation(&matTransAfterRot, 0.5f, 0, 0.5f);
	D3DXMatrixTranslation(&matTrans, m_nIndexX, 0, m_nIndexZ);
	m_stFloorTileTemplate.matFinal = matRot * matTransAfterRot * matTrans;
	m_stFloorTileTemplate.wstrTexture = m_pUI->getTileTexture(m_nTextureNum);
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (m_pUI->SelectTile(m_nTextureNum) == true)
		{

		}
		else if (m_pUI->getTileType() == TT_FLOOR)
		{
			if (m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapFloorTiles.end())
			{
				m_mapFloorTiles.erase(m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			}
			m_mapFloorTiles.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), m_stFloorTileTemplate));
		}
	}
}