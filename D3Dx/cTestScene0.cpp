#include "stdafx.h"
#include "cTestScene0.h"
#include "cCamera.h"


cTestScene0::cTestScene0()
	: m_pCamera(NULL)
{
}


cTestScene0::~cTestScene0()
{
	delete m_pCamera;
}

void cTestScene0::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();
}

void cTestScene0::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
}

void cTestScene0::Render()
{

}

void cTestScene0::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
