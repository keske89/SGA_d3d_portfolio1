#pragma once

#define TEXTMANAGER cTextManager::GetInstance()

class cTextManager
{
private:
	SINGLETONE(cTextManager)

public:
	void DrawMessage(LPD3DXFONT font, unsigned int x, unsigned int y, unsigned int width, unsigned int height, D3DXCOLOR color, LPCSTR message);
};

