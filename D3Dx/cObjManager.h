#pragma once

#define ObJMANAGER cObjManager::GetInstance()

class cObjLoader;

class cObjManager
{
private:
	SINGLETONE(cObjManager);
	map<LPCTSTR, LPD3DXMESH>	m_mapMesh;
	LPD3DXMESH					m_mesh;
	cObjLoader*					ObjLoader;
	

	void SetMeshData(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIX* pMat);

public:
	void Setup();
	
	LPD3DXMESH GetMesh(LPCTSTR filename);
	void Destroy();



};

