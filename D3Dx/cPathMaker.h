#pragma once
#include "cPath.h"

class cPathMaker
{
public:
	cPathMaker();
	~cPathMaker();

	void CreatePath(PATH_TYPE type, D3DXVECTOR3 From, D3DXVECTOR3 To, vector<cPath*>& vec);
};

