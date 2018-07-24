#pragma once
#include "cGameNode.h"
#include "cSelectUI.h"
class cCharaterChangeScene : public cGameNode
{
private:
	cSelectUI * m_pSelectUi;
public:
	cCharaterChangeScene();
	~cCharaterChangeScene();
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
