#pragma once
#include "cGameNode.h"

class cCamera;

class cWorldMapScene;

class cMainGame : public cGameNode
{
private:
	cCamera * m_pCamera;
	cWorldMapScene* m_pWMScene;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();

	
};

