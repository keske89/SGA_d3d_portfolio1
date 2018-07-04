#pragma once
#include "cGameNode.h"


class cTestScene0 : public cGameNode
{
private:

public:
	cTestScene0();
	~cTestScene0();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};