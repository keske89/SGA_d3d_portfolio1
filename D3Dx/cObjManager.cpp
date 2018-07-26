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
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Chopping_Board.obj", &matWorld);

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Tomato_Whole.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Tomato_Sliced.obj", &matWorld);

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Onion_Whole.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Onion_Sliced.obj", &matWorld);

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Mushroom_Whole.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Mushroom_Sliced.obj", &matWorld);
	
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Crate_mesh.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"CrateLid_mesh.obj", &matWorld);
	
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Sink1.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Sink_Counter.obj", &matWorld);

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Plate.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"PlateReturnBox.obj", &matWorld);

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Cooker.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Pot_Mesh.obj", &matWorld);

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Bin.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"CounterTop_Isolated.obj", &matWorld);

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"ThePass.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/IngameObj/", L"ThePass_FatScrolling.obj", &matWorld);

	SetMeshData(L"./Resources/Mesh/IngameObj/", L"Recipe.obj", &matWorld);


	

	//===============================================================PLAYER PARTS
	SetMeshData(L"./Resources/Mesh/Player/", L"Body.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/Player/", L"Hand_Open_L1.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/Player/", L"Hand_Grip_R #010449.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/Player/", L"Hand_Open_R #000539.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/Player/", L"Hat_Fancy #000039.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/", L"RunPuff.obj", &matWorld);
	//===============================================================PLAYER HEAD
	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, 3.43f, 0, 0);
	SetMeshData(L"./Resources/Mesh/Player/", L"Chef_Bear.obj", &matT);
	SetMeshData(L"./Resources/Mesh/Player/", L"Chef_Beard #010486.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/Player/", L"Chef_BlackCat #010487.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/Player/", L"Chef_Boof #010478.obj", &matWorld);
	SetMeshData(L"./Resources/Mesh/Player/", L"Chef_Box #010481.obj", &matWorld);
	D3DXMatrixTranslation(&matT, -12.33f, 0, -2.0f);
	SetMeshData(L"./Resources/Mesh/Player/", L"Chef_Buck_Head #010488.obj", &matT);
	D3DXMatrixTranslation(&matT, 4.45f, 0, 0);
	SetMeshData(L"./Resources/Mesh/Player/", L"Chef_Dino.obj", &matT);
	//Chef_Dino
}


void cObjManager::SetMeshData(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIX* pMat)
{
	if (m_mesh != NULL) m_mesh = NULL;

	m_mesh = ObjLoader->ObjectLoadMesh(filepath, filename, pMat);
	m_mapMesh[filename] = m_mesh;
}

LPD3DXMESH cObjManager::GetMesh(LPCTSTR filename)
{

	assert(m_mapMesh.find(filename) != m_mapMesh.end() && "일치하는 매쉬 키값이 없습니다");

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
