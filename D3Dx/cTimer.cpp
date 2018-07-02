#include "stdafx.h"
#include "cTimer.h"
#include <mmsystem.h> //timeGetTime() == 밀리세컨

#pragma comment(lib, "winmm.lib")

cTimer::cTimer()
{
}


cTimer::~cTimer()
{
}

void cTimer::Setup()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;

		_lastTime = timeGetTime();	//강제로 0.001초로 맞춤 잘가라 CPU
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSframeCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;
}

void cTimer::tick(float lockFPS)
{
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}

	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//프레임수치를 고정한다 == 프레임 스키핑
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < 1.0f / lockFPS)
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSframeCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	//초당 프레임이 유지되면~
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSframeCount;
		_FPSframeCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long cTimer::getFrameRate(TCHAR* str) const
{
	if (str != NULL)
	{
		wsprintf(str, L"FPS : %d", _frameRate);
	}

	return _frameRate;
}
