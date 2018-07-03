#include "stdafx.h"
#include "cTextManager.h"


cTextManager::cTextManager()
{
}


cTextManager::~cTextManager()
{
}

void cTextManager::DrawMessage(LPD3DXFONT font, unsigned int x, unsigned int y, unsigned int width, unsigned int height, D3DXCOLOR color, LPCSTR message)
{
	RECT rc;
	rc.left = x;
	rc.right = x + width;
	rc.top = y;
	rc.bottom = y + height;
	font->DrawTextA(NULL, message, -1, &rc, 0, color);
}
