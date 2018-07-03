#include "stdafx.h"
#include "cTestScene3.h"


cTestScene3::cTestScene3()
{
}


cTestScene3::~cTestScene3()
{
	SAFE_RELEASE(m_pFont);
}

void cTestScene3::Setup()
{
	AddFontResource(L"±Ã¼­Ã¼.ttf");

	D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, L"±Ã¼­Ã¼", &m_pFont);
}

void cTestScene3::Update()
{
}

void cTestScene3::Render()
{
	RECT rc;
	SetRect(&rc, 10, 200, 1000, 1000);

	m_pFont->DrawText(NULL, L"TestScene3", strlen("TestScene3"), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));
}
