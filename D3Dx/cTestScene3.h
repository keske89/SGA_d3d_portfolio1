#pragma once
#include "cGameNode.h"

class cCamera;

class cTestScene3 : public cGameNode
{
private:
	cCamera * m_pCamera;
	LPD3DXFONT				m_pFont;

public:
	cTestScene3();
	~cTestScene3();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};