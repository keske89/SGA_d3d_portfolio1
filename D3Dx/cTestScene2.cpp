#include "stdafx.h"
#include "cTestScene2.h"
#include "cCamera.h"
#include "cChef.h"
#include "cCharacterControl.h"

cTestScene2::cTestScene2()
	: m_pCamera(NULL)
	, m_pControl(NULL)
{
	for (int i = 0; i < 2; i++)
		m_pChef[i] = NULL;
}


cTestScene2::~cTestScene2()
{
	delete m_pCamera;
	delete m_pControl;
	for (int i = 0; i < 2; i++)
	{
		delete m_pChef[i];
	}
	SAFE_RELEASE(m_pFont);
}

void cTestScene2::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();
	AddFontResource(L"�ü�ü.ttf");

	D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, L"�ü�ü", &m_pFont);

	m_pControl = new cCharacterControl;

	for (int i = 0; i < 2; i++)
	{
		m_pChef[i] = new cChef;
		m_pControl->AddcCharacter(m_pChef[i]);
		m_pChef[i]->SetUp(D3DXVECTOR3(i * 3, 0, 0), m_pControl);
	}
}

void cTestScene2::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
	if (m_pControl)
		m_pControl->Control();
	for (int i = 0; i < 2; i++)
	{
		m_pChef[i]->Update();
	}
}

void cTestScene2::Render()
{
	RECT rc;
	SetRect(&rc, 10, 200, 1000, 1000);
	char m_str[256];

	for (int i = 0; i < 2; i++)
	{
		m_pChef[i]->Render();
	}
}

void cTestScene2::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
