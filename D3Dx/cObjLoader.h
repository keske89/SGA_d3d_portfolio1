#pragma once
#include "stdafx.h"


class cObjLoader
{
private:
	CString m_filePath;
	//map<CString, MTLTEX*> m_mtltexList;

public:
	cObjLoader();
	~cObjLoader();

	LPD3DXMESH LoadMesh(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIX* pMat);
};

