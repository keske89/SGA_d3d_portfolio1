#include "stdafx.h"
#include "cStageScene.h"
#include "cStage.h"
#include "cCamera.h"
#include "cStageGrid.h"


cStageScene::cStageScene()
	: m_pStage(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_vecPos(0, 0, 0)
{
}


cStageScene::~cStageScene()
{
	SAFE_DELETE(m_pStage);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
}

void cStageScene::Setup()
{
	m_pStage = new cStage;
	m_pStage->Setup(2);

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cStageGrid;
	m_pGrid->Setup();
}

void cStageScene::Update()
{
	if (m_pCamera)
	{
		m_pCamera->Update();
		Control();
	}
}

void cStageScene::Render()
{
	if (m_pStage)
		m_pStage->Render();

	if (m_pGrid)
		m_pGrid->Render();
}

void cStageScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cStageScene::Control()
{
	//카메라 위치 조작
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
}
