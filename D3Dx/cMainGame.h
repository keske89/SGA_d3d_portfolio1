#pragma once
#include "cGameNode.h"

class cMainGame : public cGameNode
{
private:


public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();

	
};

