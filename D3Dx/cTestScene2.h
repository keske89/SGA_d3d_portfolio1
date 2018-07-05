#pragma once
#include "cGameNode.h"

class cCamera;
class cCharacter;
class cCharacterControl;

class cTestScene2 : public cGameNode
{
private:
	cCamera * m_pCamera;
	LPD3DXFONT				m_pFont;
	cCharacter *			m_pChef[2];
	cCharacterControl *		m_pControl;

public:
	cTestScene2();
	~cTestScene2();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};