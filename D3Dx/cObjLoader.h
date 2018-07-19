#pragma once
#include "stdafx.h"


class cObjLoader
{
private:

public:
	cObjLoader();
	~cObjLoader();

	LPD3DXMESH LoadMesh(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIX* pMat);
	LPD3DXMESH ObjectLoadMesh(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIX* pMat);
};

