#include "stdafx.h"
#include "cTestScene0.h"


cTestScene0::cTestScene0()
{
}


cTestScene0::~cTestScene0()
{
	SAFE_RELEASE(m_pFont);
}

void cTestScene0::Setup()
{
	AddFontResource(L"�ü�ü.ttf");

	D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, L"�ü�ü", &m_pFont);
}

void cTestScene0::Update()
{
}

void cTestScene0::Render()
{
	RECT rc;
	SetRect(&rc, 10, 200, 1000, 1000);

	m_pFont->DrawText(NULL, L"������ �׽�Ʈ��0", strlen("������ �׽�Ʈ��0"), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

}
