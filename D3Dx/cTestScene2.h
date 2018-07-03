#pragma once
#include "cGameNode.h"

class cCamera;

class cTestScene2 : public cGameNode
{
private:
	cCamera * m_pCamera;
	LPD3DXFONT				m_pFont;

public:
	cTestScene2();
	~cTestScene2();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};