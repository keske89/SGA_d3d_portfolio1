#include "stdafx.h"
#include "cBackground.h"
#include "cObjLoader.h"


cBackground::cBackground()
	: m_pMesh(NULL)
	, m_pSkyMesh(NULL)
{
}


cBackground::~cBackground()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pSkyMesh);
}

void cBackground::Setup(int num)
{
	m_strBackgroundName[0] = L"BG_1";
	TEXTUREMANAGER->addTexture(m_strBackgroundName[0], L"./Resources/StageTexture/BG_1.jpg");
	m_strBackgroundName[1] = L"BG_2";
	TEXTUREMANAGER->addTexture(m_strBackgroundName[1], L"./Resources/Texture2D/Map_PirateShip.png");
	m_strBackgroundName[2] = L"BG_3";


	TEXTUREMANAGER->addTexture(L"BG_SKY", L"./Resources/StageTexture/BG_SKY.png");

	vector<ST_PNT_VERTEX>	vecVertex;
	vector<WORD>			vecIndex;
	vector<DWORD>			vecAttribute;
	D3DXMATRIX matIden;
	D3DXMatrixIdentity(&matIden);
	D3DXMATRIX matTrans1;
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTrans2;

	if (m_pMesh)
		m_pMesh->Release();

	//front
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.251f, 0.666f));	//0
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.251f, 0.334f));	//1
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.500f, 0.334f));	//2
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.500f, 0.334f));	//2
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.500f, 0.666f));	//3
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.251f, 0.666f));	//0
	//top
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.251f, 0.000f));	//5
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.500f, 0.000f));	//4
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.500f, 0.333f));	//2
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.500f, 0.333f));	//2
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.251f, 0.333f));	//1
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.251f, 0.000f));	//5
	//right
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.501f, 0.334f));	//2
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.750f, 0.334f));	//4
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.750f, 0.666f));	//7
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.750f, 0.666f));	//7
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.501f, 0.666f));	//3
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.501f, 0.334f));	//2
	//bottom
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.251f, 0.667f));	//0
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.500f, 0.667f));	//3
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.500f, 1.000f));	//7
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.500f, 1.000f));	//7
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.251f, 1.000f));	//6
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.251f, 0.667f));	//0
	//left
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.000f, 0.334f));	//5
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.250f, 0.334f));	//1
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.250f, 0.666f));	//0
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.250f, 0.666f));	//0
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.000f, 0.666f));	//6
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.000f, 0.334f));	//5
	//back
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.751f, 0.666f));	//7
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.751f, 0.334f));	//4
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.000f, 0.334f));	//5
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.000f, 0.334f));	//5
	AddVertex(vecVertex, D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR2(1.000f, 0.666f));	//6
	AddVertex(vecVertex, D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.751f, 0.666f));	//7
	AddNormalVector(vecVertex);
	for (int i = 0; i < vecVertex.size(); ++i)
	{
		vecIndex.push_back(i);
	}
	vecAttribute = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if (num == 1)
	{
		D3DXCreateMeshFVF(
			vecVertex.size() / 3,
			vecVertex.size(),
			D3DXMESH_MANAGED,
			ST_PNT_VERTEX::FVF,
			g_pD3DDevice,
			&m_pMesh);

		ST_PNT_VERTEX* verticies = NULL;
		WORD* index = NULL;
		DWORD* attribute = NULL;
		m_pMesh->LockVertexBuffer(0, (LPVOID*)&verticies);
		memcpy(verticies, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
		m_pMesh->UnlockVertexBuffer();
		m_pMesh->LockIndexBuffer(0, (LPVOID*)&index);
		memcpy(index, &vecIndex[0], vecIndex.size() * sizeof(WORD));
		m_pMesh->UnlockIndexBuffer();
		m_pMesh->LockAttributeBuffer(0, &attribute);
		memcpy(attribute, &vecAttribute[0], vecAttribute.size() * sizeof(DWORD));
		m_pMesh->UnlockAttributeBuffer();

		vector<DWORD> adjacencyInfo(m_pMesh->GetNumFaces() * 3);
		vector<DWORD> optimizedAdjacencyInfo(m_pMesh->GetNumFaces() * 3);
		m_pMesh->GenerateAdjacency(0.0f, &adjacencyInfo[0]);
		m_pMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_VERTEXCACHE,
			&adjacencyInfo[0],
			&optimizedAdjacencyInfo[0],
			0,
			0);

		D3DXMatrixRotationYawPitchRoll(&matRotation, 0, 0, 0);
		D3DXMatrixTranslation(&matTrans1, 0, -1.0f, 0);
		D3DXMatrixScaling(&matScale, 50.0f, 50.0f, 50.0f);
		D3DXMatrixTranslation(&matTrans2, 0, -0.01f, 0);

		m_matWorld[0] = matRotation * matTrans1 * matScale * matTrans2;
	}
	else if (num == 2)
	{
		cObjLoader * obj = NULL;
		D3DXMatrixTranslation(&matTrans1, 0.26f, -0.163f, -1.55);
		D3DXMatrixScaling(&matScale, 50.0f, 50.0f, 50.0f);
		m_matWorld[1] = matTrans1 * matScale;
		m_pMesh = obj->LoadMesh(L"./Resources/Mesh/Object/", L"Map_PirateShip.obj", &matIden);
	}

	D3DXCreateMeshFVF(
		vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pSkyMesh);

	ST_PNT_VERTEX* verticies = NULL;
	WORD* index = NULL;
	DWORD* attribute = NULL;
	m_pSkyMesh->LockVertexBuffer(0, (LPVOID*)&verticies);
	memcpy(verticies, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pSkyMesh->UnlockVertexBuffer();
	m_pSkyMesh->LockIndexBuffer(0, (LPVOID*)&index);
	memcpy(index, &vecIndex[0], vecIndex.size() * sizeof(WORD));
	m_pSkyMesh->UnlockIndexBuffer();
	m_pSkyMesh->LockAttributeBuffer(0, &attribute);
	memcpy(attribute, &vecAttribute[0], vecAttribute.size() * sizeof(DWORD));
	m_pSkyMesh->UnlockAttributeBuffer();

	vector<DWORD> adjacencyInfo2(m_pSkyMesh->GetNumFaces() * 3);
	vector<DWORD> optimizedAdjacencyInfo2(m_pSkyMesh->GetNumFaces() * 3);
	m_pSkyMesh->GenerateAdjacency(0.0f, &adjacencyInfo2[0]);
	m_pSkyMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyInfo2[0],
		&optimizedAdjacencyInfo2[0],
		0,
		0);

	D3DXMatrixScaling(&m_matSky, 10000.0f, 10000.0f, 10000.0f);
}

void cBackground::Render(int num)
{
	SetupMaterials();
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matSky);
	g_pD3DDevice->SetTexture(0, TEXTUREMANAGER->findTexture(L"BG_SKY"));
	m_pSkyMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld[num - 1]);
	g_pD3DDevice->SetTexture(0, TEXTUREMANAGER->findTexture(m_strBackgroundName[num - 1]));
	m_pMesh->DrawSubset(0);
}

void cBackground::AddNormalVector(vector<ST_PNT_VERTEX>& vector)
{
	D3DXVECTOR3 v1, v2, vn, vtemp;
	for (int i = 0; i < vector.size() / 3; ++i)
	{
		v1 = vector[i * 3 + 2].p - vector[i * 3 + 1].p;
		v2 = vector[i * 3].p - vector[i * 3 + 1].p;
		D3DXVec3Cross(&vn, &v1, &v2);
		D3DXVec3Normalize(&vn, &vn);
		vector[i * 3].n = vn;
		vector[i * 3 + 1].n = vn;
		vector[i * 3 + 2].n = vn;
	}
}

void cBackground::SetReverse(vector<ST_PNT_VERTEX>& vector)
{
	D3DXVECTOR3 vtemp;
	for (int i = 0; i < vector.size() / 3; ++i)
	{
		vtemp = vector[i * 3].p;
		vector[i * 3].p = vector[i * 3 + 2].p;
		vector[i * 3 + 2].p = vtemp;
	}
}

void cBackground::AddVertex(vector<ST_PNT_VERTEX>& vector, D3DXVECTOR3 vp, D3DXVECTOR2 vt)
{
	ST_PNT_VERTEX stTemp;
	stTemp.p = vp;
	stTemp.t = vt;
	vector.push_back(stTemp);
}

void cBackground::SetupMaterials()
{
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Ambient = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	mtrl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mtrl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	g_pD3DDevice->SetMaterial(&mtrl);
}