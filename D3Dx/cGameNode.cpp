#include "stdafx.h"
#include "cGameNode.h"


cGameNode::cGameNode()
{
}


cGameNode::~cGameNode()
{
}

void cGameNode::Setup()
{
}

void cGameNode::Update()
{
}

void cGameNode::Render()
{
}

void cGameNode::Destroy()
{
}

void cGameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);

		break;
	}
}
