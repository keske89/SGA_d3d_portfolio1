#include "stdafx.h"
#include "cStageMapTool.h"
#include "cCamera.h"
#include "cStageGrid.h"
#include "cRay.h"


cStageMapTool::cStageMapTool()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
{
}


cStageMapTool::~cStageMapTool()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
}

void cStageMapTool::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cStageGrid;
	m_pGrid->Setup();
}

void cStageMapTool::Update()
{
	if (m_pCamera)
	{
		m_pCamera->Update();
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			D3DXVECTOR3	vecTemp;
			cRay ray;
			float ratio = 0.0f;
			ratio = ray.getPickRayOrg().z / ray.getPickRayDir().z;
			vecTemp = ray.getPickRayOrg() - (ray.getPickRayDir() * ratio);
		}
	}
}

void cStageMapTool::Render()
{
	if (m_pGrid)
		m_pGrid->Render();
}

void cStageMapTool::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
