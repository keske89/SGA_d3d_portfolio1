#pragma once
class cGameNode
{
public:
	cGameNode();
	virtual ~cGameNode();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

