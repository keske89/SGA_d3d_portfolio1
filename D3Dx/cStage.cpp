#include "stdafx.h"
#include "cStage.h"


cStage::cStage()
	: m_pMesh(NULL)
{
}


cStage::~cStage()
{
	SAFE_RELEASE(m_pMesh);
}

void cStage::Setup(int stageNum)
{
	HANDLE file;
	DWORD read;

	WCHAR filePath[1024] = L"";
	wsprintf(filePath, L"./StageMap/stage%d.map", stageNum);

	file = CreateFile(filePath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	int maxTextureSize = 0;
	ReadFile(file, &maxTextureSize, sizeof(int), &read, NULL);
	m_vecTex.resize(maxTextureSize);
	for (int i = 0; i < maxTextureSize; ++i)
	{
		int num;
		ReadFile(file, &num, sizeof(int), &read, NULL);
		int length;
		ReadFile(file, &length, sizeof(int), &read, NULL);
		wstring tempString;
		tempString.resize(length);
		ReadFile(file, &tempString[0], length * sizeof(WCHAR), &read, NULL);
		m_vecTex[num] = tempString;
	}
	int maxVectorSize = 0;
	ReadFile(file, &maxVectorSize, sizeof(int), &read, NULL);
	wstring tempStr;
	vector<ST_PNT_VERTEX>		vecVertex;
	vector<WORD>				vecIndex;
	vector<DWORD>				vecAttribute;
	vecVertex.resize(maxVectorSize);
	vecIndex.resize(maxVectorSize);
	vecAttribute.resize(maxVectorSize / 3);
	ReadFile(file, &vecVertex[0], sizeof(ST_PNT_VERTEX) * maxVectorSize, &read, NULL);
	ReadFile(file, &vecIndex[0], sizeof(WORD) * maxVectorSize, &read, NULL);
	ReadFile(file, &vecAttribute[0], sizeof(DWORD) * maxVectorSize / 3, &read, NULL);
	int test = 0;
	D3DXCreateMeshFVF(
		maxVectorSize / 3,
		maxVectorSize,
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


	int maxObjSize = 0;
	D3DXMATRIX matTemp;
	int tempType = 0;
	ReadFile(file, &maxObjSize, sizeof(int), &read, NULL);
	for (int i = 0; i < maxObjSize; ++i)
	{
		ReadFile(file, &matTemp, sizeof(D3DXMATRIX), &read, NULL);
		ReadFile(file, &tempType, sizeof(int), &read, NULL);
		m_vecNewObjData.push_back(make_pair(tempType, matTemp));
	}
	ReadFile(file, &maxObjSize, sizeof(int), &read, NULL);
	for (int i = 0; i < maxObjSize; ++i)
	{
		ReadFile(file, &matTemp, sizeof(D3DXMATRIX), &read, NULL);
		ReadFile(file, &tempType, sizeof(int), &read, NULL);
		m_vecSetObjData.push_back(make_pair(tempType, matTemp));
	}

	int maxBlockSize = 0;
	pair<int, int> tempPair;
	ReadFile(file, &maxBlockSize, sizeof(int), &read, NULL);
	for (int i = 0; i < maxBlockSize; ++i)
	{
		ReadFile(file, &tempPair, sizeof(pair<int, int>), &read, NULL);
		m_mapIsBlockedData.insert(make_pair(tempPair, 0));
	}

	ReadFile(file, &m_vecChefPos[0], sizeof(D3DXVECTOR3), &read, NULL);
	ReadFile(file, &m_vecChefPos[1], sizeof(D3DXVECTOR3), &read, NULL);



	CloseHandle(file);
}

void cStage::Update()
{
}

void cStage::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (int i = 0; i < m_vecTex.size(); ++i)
	{
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_vecTex[i].c_str()));
		m_pMesh->DrawSubset(i);
	}
}
