#include "stdafx.h"
#include "cBackground.h"
#include "cObjLoader.h"


cBackground::cBackground()
	: m_pMesh(NULL)
{
}


cBackground::~cBackground()
{
	SAFE_RELEASE(m_pMesh);
}

void cBackground::Setup(int num)
{
	m_strBackgroundName[0] = L"BG1";
	TEXTUREMANAGER->addTexture(m_strBackgroundName[0], L"./Resources/StageTexture/BG_1.png");
	m_strBackgroundName[1] = L"BG2";
	TEXTUREMANAGER->addTexture(m_strBackgroundName[1], L"./Resources/Texture2D/Map_PirateShip.png");
	m_strBackgroundName[2] = L"BG3";


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

	if (num == 1)
	{
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
		AddNormalVector(vecVertex, -1);
		for (int i = 0; i < vecVertex.size(); ++i)
		{
			vecIndex.push_back(i);
		}
		//vecIndex;
		vecAttribute = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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

		D3DXMatrixRotationYawPitchRoll(&matRotation, D3DX_PI / 2.0f, 0, D3DX_PI / 2.0f);
		D3DXMatrixTranslation(&matTrans1, -0.75f, -1.0f, -0.65f);
		D3DXMatrixScaling(&matScale, 500.0f, 500.0f, 500.0f);
		D3DXMatrixTranslation(&matTrans2, 0, -0.01f, 0);

		m_matWorld[0] = matRotation * matTrans1 * matScale * matTrans2;
	}
	else if (num == 2)
	{
		cObjLoader * obj = NULL;
		D3DXMatrixTranslation(&matTrans1, 0.3, -0.2f, -1.5);
		D3DXMatrixScaling(&matScale, 50.0f, 50.0f, 50.0f);
		m_matWorld[0] = matTrans1 * matScale;
		m_pMesh = obj->LoadMesh(L"./Resources/Mesh/Object/", L"Map_PirateShip.obj", &matIden);
	}
}

void cBackground::Render(int num)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld[0]);
	g_pD3DDevice->SetTexture(0, TEXTUREMANAGER->findTexture(m_strBackgroundName[num - 1]));
	m_pMesh->DrawSubset(0);
}

void cBackground::AddNormalVector(vector<ST_PNT_VERTEX>& vector, int reverse)
{
	D3DXVECTOR3 v1, v2, vn;
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

void cBackground::AddVertex(vector<ST_PNT_VERTEX>& vector, D3DXVECTOR3 vp, D3DXVECTOR2 vt)
{
	ST_PNT_VERTEX stTemp;
	stTemp.p = vp;
	stTemp.t = vt;
	vector.push_back(stTemp);
}
