#include "stdafx.h"
#include "cObjLoader.h"

const int TOKEN_SIZE = 128;


cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}

LPD3DXMESH cObjLoader::LoadMesh(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIX * pMat)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<D3DXVECTOR3> vecN;
	vector<ST_PNT_VERTEX> vecPNT;
	vector<DWORD> vecAttbuf;
	CString mtlName;
	char token[TOKEN_SIZE];

	m_filePath = filepath;

	std::ifstream fin;

	fin.open(m_filePath + filename);

	if (fin.is_open() == false)
		assert(false && "fin.is_open() == false");

	while (fin.eof() == false)
	{
		fin >> token;

		if (!strcmp(token, "v"))
		{
			float x, y, z;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (!strcmp(token, "vt"))
		{
			float x, y;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f", &x, &y);
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (!strcmp(token, "vn"))
		{
			float x, y, z;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (!strcmp(token, "f"))
		{
			int aIndex[3][3];

			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEX pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];
				//vecPNT.push_back(VERTEX_PNT(vecP[aIndex[i][0] - 1], vecN[aIndex[i][2] - 1], vecT[aIndex[i][1] - 1]));

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformCoord(&pnt.n, &pnt.n, pMat);
				}
				D3DXVec3Normalize(&pnt.n, &pnt.n);
				vecPNT.push_back(pnt);
			}
			//vecAttbuf.push_back(m_mtltexList[mtlName]->id);
		}
	}
	//m_mtltexList.clear();
	fin.close();

	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecPNT.size() / 3, vecPNT.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &pMesh);

	ST_PNT_VERTEX* pV = NULL;
	DWORD flags = 0;
	pMesh->LockVertexBuffer(flags, (LPVOID*)&pV);
	memcpy(pV, &vecPNT[0], vecPNT.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(flags, (LPVOID*)&pI);
	for (size_t i = 0; i < vecPNT.size(); i++)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	/*DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(flags, &pA);
	memcpy(pA, &vecAttbuf[0], vecAttbuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();*/

	vector<DWORD> vecAdjacency(pMesh->GetNumFaces() * 3);
	pMesh->GenerateAdjacency(FLT_EPSILON, &vecAdjacency[0]);
	pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, &vecAdjacency[0], NULL, NULL, NULL);

	return pMesh;
}

LPD3DXMESH cObjLoader::ObjectLoadMesh(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIX * pMat)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<D3DXVECTOR3> vecN;
	vector<ST_PNT_VERTEX> vecPNT;
	vector<DWORD> vecAttbuf;
	CString mtlName;
	int id = -2;
	char token[TOKEN_SIZE];

	m_filePath = filepath;

	std::ifstream fin;

	fin.open(m_filePath + filename);

	if (fin.is_open() == false)
		assert(false && "fin.is_open() == false");

	while (fin.eof() == false)
	{
		fin >> token;


		if (!strcmp(token, "g"))
		{
			id++;
		}
		else if (!strcmp(token, "v"))
		{
			float x, y, z;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (!strcmp(token, "vt"))
		{
			float x, y;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f", &x, &y);
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (!strcmp(token, "vn"))
		{
			float x, y, z;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (!strcmp(token, "f"))
		{
			int aIndex[3][3];

			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEX pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];
				//vecPNT.push_back(VERTEX_PNT(vecP[aIndex[i][0] - 1], vecN[aIndex[i][2] - 1], vecT[aIndex[i][1] - 1]));

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformCoord(&pnt.n, &pnt.n, pMat);
				}
				D3DXVec3Normalize(&pnt.n, &pnt.n);
				vecPNT.push_back(pnt);
			}
			vecAttbuf.push_back(id);
		}
	}
	//m_mtltexList.clear();
	fin.close();

	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecPNT.size() / 3, vecPNT.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &pMesh);

	ST_PNT_VERTEX* pV = NULL;
	DWORD flags = 0;
	pMesh->LockVertexBuffer(flags, (LPVOID*)&pV);
	memcpy(pV, &vecPNT[0], vecPNT.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(flags, (LPVOID*)&pI);
	for (size_t i = 0; i < vecPNT.size(); i++)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(flags, &pA);
	memcpy(pA, &vecAttbuf[0], vecAttbuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdjacency(pMesh->GetNumFaces() * 3);
	pMesh->GenerateAdjacency(FLT_EPSILON, &vecAdjacency[0]);
	pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, &vecAdjacency[0], NULL, NULL, NULL);

	return pMesh;
}
