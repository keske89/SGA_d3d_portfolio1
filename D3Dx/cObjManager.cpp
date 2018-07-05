#include "stdafx.h"
#include "cObjManager.h"
#include "cObjLoader.h"



cObjManager::cObjManager()
	: m_mesh(NULL)
{
	m_mapMesh.clear();
}


cObjManager::~cObjManager()
{
	
}



void cObjManager::Setup()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	ObjLoader = new cObjLoader;

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Knife.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Tomato_Whole.obj", &matWorld);
}


void cObjManager::SetMeshData(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIX* pMat)
{
	if (m_mesh != NULL) m_mesh = NULL;

	m_mesh = ObjLoader->LoadMesh(filepath, filename, pMat);
	m_mapMesh[filename] = m_mesh;
}

LPD3DXMESH cObjManager::GetMesh(LPCTSTR filename)
{
	
	assert(m_mapMesh.find(filename) != m_mapMesh.end() && "��ġ�ϴ� �޽� Ű���� �����ϴ�");
	
	return m_mapMesh[filename];
}

void cObjManager::Destroy()
{
	for (auto p : m_mapMesh)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapMesh.clear();
}
