#include "stdafx.h"
#include "cCharaterChangeScene.h"


cCharaterChangeScene::cCharaterChangeScene()
					:m_pSelectUi(NULL)
{
}


cCharaterChangeScene::~cCharaterChangeScene()
{
	SAFE_RELEASE(m_pSelectUi);
}

void cCharaterChangeScene::Setup()
{
	m_pSelectUi = new cSelectUI;
	m_pSelectUi->setPosition(&D3DXVECTOR3(0, 0, 0));
	m_pSelectUi->Setup();
}

void cCharaterChangeScene::Update()
{
	m_pSelectUi->Update();
}

void cCharaterChangeScene::Render()
{
	m_pSelectUi->Render();
}

void cCharaterChangeScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
