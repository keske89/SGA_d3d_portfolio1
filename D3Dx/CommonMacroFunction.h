#include "stdafx.h"

inline DWORD FtoDW(float f)
{
	return *((DWORD*)(&f));
}