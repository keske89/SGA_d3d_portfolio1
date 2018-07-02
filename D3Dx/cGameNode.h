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

	LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
};

