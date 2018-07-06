#pragma once
#include "cGameNode.h"

class cIGObj;
class cCamera;
class cCharacter;
class cCharacterControl;



class cTestScene1 : public cGameNode
{
private:
	cCamera*				m_pCamera;
	LPD3DXFONT				m_pFont;
	cIGObj*					m_IGObj;
	cCharacter*				m_pChef[2];
	cCharacterControl*		m_pControl;

	std::vector<cIGObj*>	m_vecObj;

public:
	cTestScene1();
	~cTestScene1();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

