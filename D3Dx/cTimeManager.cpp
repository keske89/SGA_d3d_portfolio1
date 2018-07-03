#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager()
	: m_pTimer(NULL)
{
}


cTimeManager::~cTimeManager()
{
}

void cTimeManager::Setup()
{
	m_pTimer = new cTimer;
	m_pTimer->Setup();
}

void cTimeManager::Destroy()
{
	if (m_pTimer)
		delete m_pTimer;
}

void cTimeManager::Update(float lock)
{
	if (m_pTimer != NULL)
	{
		m_pTimer->tick(lock);
	}
}

void cTimeManager::Render()
{
	char buffer[256];
	string frameRate;


#ifdef _DEBUG
	{
		sprintf_s(buffer, sizeof(buffer), "framePerSec (FPS) : %d", m_pTimer->getFrameRate());
		TEXTMANAGER->DrawMessage(g_pFontManager->GetFont(FT_TIME), 0, 0, 500, 20, D3DCOLOR_ARGB(255, 0, 0, 0), buffer);
		//TextOut(hdc, 0, 0, str, _tcslen(str));

		sprintf_s(buffer, sizeof(buffer), "worldTime : %f", m_pTimer->getWorldTime());
		TEXTMANAGER->DrawMessage(g_pFontManager->GetFont(FT_TIME), 0, 20, 500, 20, D3DCOLOR_ARGB(255, 0, 0, 0), buffer);
		//TextOut(hdc, 0, 20, str, _tcslen(str));

		sprintf_s(buffer, sizeof(buffer), "elapsedTime : %f", m_pTimer->getElapsedTime());
		TEXTMANAGER->DrawMessage(g_pFontManager->GetFont(FT_TIME), 0, 40, 500, 20, D3DCOLOR_ARGB(255, 0, 0, 0), buffer);
		//TextOut(hdc, 0, 40, str, _tcslen(str));
	}
#else
	{
		sprintf_s(buffer, sizeof(buffer), "framePerSec (FPS) : %d", m_pTimer->getFrameRate());
		TEXTMANAGER->DrawMessage(g_pFontManager->GetFont(FT_TIME), 0, 0, 500, 20, D3DCOLOR_ARGB(255, 0, 0, 0), buffer);
	}
#endif
}
