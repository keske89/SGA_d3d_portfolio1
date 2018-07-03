#include "stdafx.h"
#include "cTestScene1.h"
#include "cIGObj.h"


cTestScene1::cTestScene1()
{
}


cTestScene1::~cTestScene1()
{
	delete m_IGObj;
	SAFE_RELEASE(m_pFont);

}

void cTestScene1::Setup()
{
	AddFontResource(L"±Ã¼­Ã¼.ttf");

	D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, L"±Ã¼­Ã¼", &m_pFont);
	m_IGObj = new cIGObj;
	m_IGObj->Setup();

	
}

void cTestScene1::Update()
{
	m_IGObj->Update();
}

void cTestScene1::Render()
{
	RECT rc;
	SetRect(&rc, 10, 200, 1000, 1000);

	m_pFont->DrawText(NULL, L"TestScene1", strlen("TestScene1"), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	m_IGObj->Render();
}
