#include "stdafx.h"
#include "cTestScene1.h"
#include "cCamera.h"
#include "cIGObj.h"
#include "cCharacter.h"
#include "cCharacterControl.h"



cTestScene1::cTestScene1()
	: m_pCamera(NULL)
	, m_pControl(NULL)
{
	for (int i = 0; i < 2; i++)
		m_pChef[i] = NULL;
}


cTestScene1::~cTestScene1()
{
	delete m_pCamera;
	delete m_IGObj;
	SAFE_RELEASE(m_pFont);

	delete m_pControl;
	for (int i = 0; i < 2; i++)
	{
		delete m_pChef[i];
	}

}

void cTestScene1::Setup()
{
	AddFontResource(L"±Ã¼­Ã¼.ttf");

	D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, L"±Ã¼­Ã¼", &m_pFont);
	m_IGObj = new cIGObj;
	m_IGObj->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup();


	/*m_pControl = new cCharacterControl;

	for (int i = 0; i < 2; i++)
	{
		m_pChef[i] = new cCharacter;
		m_pControl->AddcCharacter(m_pChef[i]);
		m_pChef[i]->SetUp(D3DXVECTOR3(i * 3, 0, 0), m_pControl);
	}
	m_pControl->SetUp();*/


	
}

void cTestScene1::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
	m_IGObj->Update();


	/*for (int i = 0; i < 2; i++)
	{
		m_pChef[i]->Update();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		m_pControl->SetPlaterMod(2);*/
}

void cTestScene1::Render()
{
	RECT rc;
	SetRect(&rc, 10, 200, 1000, 1000);

	m_pFont->DrawText(NULL, L"TestScene1", strlen("TestScene1"), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));
	

	m_IGObj->Render();

	/*for (int i = 0; i < 2; i++)
	{
		m_pChef[i]->Render();
	}*/
}

void cTestScene1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
