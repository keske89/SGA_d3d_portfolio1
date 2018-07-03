#include "stdafx.h"
#include "cTestScene2.h"
#include "cCamera.h"


cTestScene2::cTestScene2()
	: m_pCamera(NULL)
{
}


cTestScene2::~cTestScene2()
{
	delete m_pCamera;
	SAFE_RELEASE(m_pFont);
}

void cTestScene2::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();
	AddFontResource(L"±Ã¼­Ã¼.ttf");

	D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, L"±Ã¼­Ã¼", &m_pFont);
}

void cTestScene2::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
}

void cTestScene2::Render()
{
	RECT rc;
	SetRect(&rc, 10, 200, 1000, 1000);

	m_pFont->DrawText(NULL, L"TestScene2", strlen("TestScene2"), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));
}

void cTestScene2::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
