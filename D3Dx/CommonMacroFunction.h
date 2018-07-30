#include "stdafx.h"

inline DWORD FtoDW(float f)
{
	return *((DWORD*)(&f));
}

inline float GetDistance(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
{
	float x = (vec1.x - vec2.x) * (vec1.x - vec2.x);
	float z = (vec1.z - vec2.z) * (vec1.z - vec2.z);
	float result = sqrtf(x + z);
	return result;
}

inline RECT getRect(LONG left, LONG top, LONG right, LONG bottom)
{
	RECT result;
	result.left = left;
	result.top = top;
	result.right = right;
	result.bottom = bottom;
	return result;
}