#pragma once
#include "cGameNode.h"

class cIGObj;
class cCamera;


class cTestScene1 : public cGameNode
{
private:
	cCamera * m_pCamera;
	LPD3DXFONT				m_pFont;
	cIGObj*					m_IGObj;

public:
	cTestScene1();
	~cTestScene1();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

