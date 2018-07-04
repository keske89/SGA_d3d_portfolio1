#include "stdafx.h"
#include "cMapTool.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cMapTool.h"


cMapTool::cMapTool()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
{
}


cMapTool::~cMapTool()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
}

void cMapTool::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();
}

void cMapTool::Update()
{
	if (m_pCamera)
	{
		m_pCamera->Update();
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
		}
	}
}

void cMapTool::Render()
{
	if (m_pGrid)
		m_pGrid->Render();
}

void cMapTool::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
