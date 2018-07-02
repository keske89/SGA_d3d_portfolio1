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

void cTimeManager::Render(HDC hdc)
{
	TCHAR str[256];
	string frameRate;
	//font 백그라운드 모드는 2개가 있다
	//TRANSPARENT : 투명
	//OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);


#ifdef _DEBUG
	{
		wsprintf(str, L"framePerSec (FPS) : %d", m_pTimer->getFrameRate());
		TextOut(hdc, 0, 0, str, _tcslen(str));

		wsprintf(str, L"worldTime : %f", m_pTimer->getWorldTime());
		TextOut(hdc, 0, 20, str, _tcslen(str));

		wsprintf(str, L"elapsedTime : %f", m_pTimer->getElapsedTime());
		TextOut(hdc, 0, 40, str, _tcslen(str));
	}
#else
	{
		wsprintf(str, L"framePerSec (FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, _tcslen(str));
	}
#endif
}
