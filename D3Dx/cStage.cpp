#include "stdafx.h"
#include "cStage.h"


cStage::cStage()
{
}


cStage::~cStage()
{
	for (int i = 0; i < m_vecMesh.size(); ++i)
	{
		SAFE_RELEASE(m_vecMesh[i]);
	}
}

void cStage::Setup(int stageNum, vector<pair<int, D3DXMATRIX>>& vecNewObj, vector<pair<int, D3DXMATRIX>>& vecSetObj, map<pair<int, int>, int>& mapBlock, D3DXVECTOR3& player1Location, D3DXVECTOR3& player2Location)
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

	int forSize = maxVectorSize / MAX_VEC_SIZE;
	int vecRest = maxVectorSize % MAX_VEC_SIZE;
	for (int i = 0; i < forSize + 1; ++i)
	{
		int vecSize = 0;
		if (i == forSize) vecSize = vecRest;
		else vecSize = MAX_VEC_SIZE;

		LPD3DXMESH tempMesh;
		D3DXCreateMeshFVF(
			vecSize / 3,
			vecSize,
			D3DXMESH_MANAGED,
			ST_PNT_VERTEX::FVF,
			g_pD3DDevice,
			&tempMesh);

		ST_PNT_VERTEX* verticies = NULL;
		WORD* index = NULL;
		DWORD* attribute = NULL;
		tempMesh->LockVertexBuffer(0, (LPVOID*)&verticies);
		vector<ST_PNT_VERTEX> testVertex;
		testVertex.resize(vecSize);
		memcpy(&testVertex[0], &vecVertex[i * MAX_VEC_SIZE], vecSize * sizeof(ST_PNT_VERTEX));
		memcpy(verticies, &vecVertex[i * MAX_VEC_SIZE], vecSize * sizeof(ST_PNT_VERTEX));
		tempMesh->UnlockVertexBuffer();
		tempMesh->LockIndexBuffer(0, (LPVOID*)&index);
		memcpy(index, &vecIndex[i * MAX_VEC_SIZE], vecSize * sizeof(WORD));
		tempMesh->UnlockIndexBuffer();
		tempMesh->LockAttributeBuffer(0, &attribute);
		memcpy(attribute, &vecAttribute[(i * MAX_VEC_SIZE) / 3], (vecSize / 3) * sizeof(DWORD));
		tempMesh->UnlockAttributeBuffer();

		vector<DWORD> adjacencyInfo(tempMesh->GetNumFaces() * 3);
		vector<DWORD> optimizedAdjacencyInfo(tempMesh->GetNumFaces() * 3);
		tempMesh->GenerateAdjacency(0.0f, &adjacencyInfo[0]);
		tempMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_VERTEXCACHE,
			&adjacencyInfo[0],
			&optimizedAdjacencyInfo[0],
			0,
			0);

		m_vecMesh.push_back(tempMesh);
	}
	

	int maxObjSize = 0;
	D3DXMATRIX matTemp;
	int tempType = 0;
	ReadFile(file, &maxObjSize, sizeof(int), &read, NULL);
	for (int i = 0; i < maxObjSize; ++i)
	{
		ReadFile(file, &matTemp, sizeof(D3DXMATRIX), &read, NULL);
		ReadFile(file, &tempType, sizeof(int), &read, NULL);
		vecNewObj.push_back(make_pair(tempType, matTemp));
	}
	ReadFile(file, &maxObjSize, sizeof(int), &read, NULL);
	for (int i = 0; i < maxObjSize; ++i)
	{
		ReadFile(file, &matTemp, sizeof(D3DXMATRIX), &read, NULL);
		ReadFile(file, &tempType, sizeof(int), &read, NULL);
		vecSetObj.push_back(make_pair(tempType, matTemp));
	}

	int maxBlockSize = 0;
	pair<int, int> tempPair;
	ReadFile(file, &maxBlockSize, sizeof(int), &read, NULL);
	for (int i = 0; i < maxBlockSize; ++i)
	{
		ReadFile(file, &tempPair, sizeof(pair<int, int>), &read, NULL);
		mapBlock.insert(make_pair(tempPair, 0));
	}

	ReadFile(file, &player1Location, sizeof(D3DXVECTOR3), &read, NULL);
	ReadFile(file, &player2Location, sizeof(D3DXVECTOR3), &read, NULL);

	CloseHandle(file);

	SOUNDMANAGER->addSound("testBGM", "./sound/GRANZO-CIRCLE.mp3", false, false);
	SOUNDMANAGER->play("testBGM", CH_BGM, 1.0f);
	//SOUNDMANAGER->isPlaySound(CH_BGM);
}

void cStage::Update()
{
}

void cStage::Render()
{
	SetupMaterials();
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (int i = 0; i < m_vecTex.size(); ++i)
	{
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_vecTex[i].c_str()));
		for (int j = 0; j < m_vecMesh.size(); ++j)
		{
			m_vecMesh[j]->DrawSubset(i);
		}
	}
}

void cStage::SetupMaterials()
{
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = mtrl.Specular.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = mtrl.Specular.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = mtrl.Specular.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = mtrl.Specular.a = 1.0f;
	g_pD3DDevice->SetMaterial(&mtrl);
}
