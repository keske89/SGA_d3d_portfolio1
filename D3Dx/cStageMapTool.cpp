#include "stdafx.h"
#include "cStageMapTool.h"
#include "cCamera.h"
#include "cStageGrid.h"
#include "cRay.h"
#include "cStageMapToolUI.h"


cStageMapTool::cStageMapTool()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pUI(NULL)
	, m_nTextureNum(0)
	, m_vecPos(0, 0, 0)
	, m_fRotAngle(0.0f)
	, m_nIndexX(0)
	, m_nIndexZ(0)
	, m_fTBRXAxis(0.0f)
	, m_fTBRZAxis(0.0f)
{ 
}


cStageMapTool::~cStageMapTool()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pUI);
}

void cStageMapTool::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cStageGrid;
	m_pGrid->Setup();

	m_pUI = new cStageMapToolUI;
	m_pUI->Setup();

	//�ٴ� Ÿ���� ���ʰ� �Ǵ� �簢�� ����
	ST_PNT_VERTEX tempV;
	tempV.p = D3DXVECTOR3(-0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 0);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 1);
	m_stFloorTileTemplate.vecVertex.push_back(tempV);
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matTrans;
	D3DXMATRIX matTransAfterRot;
	D3DXMatrixRotationY(&matRot, m_fRotAngle);
	D3DXMatrixTranslation(&matTransAfterRot, 0.5f, 0, 0.5f);
	D3DXMatrixTranslation(&matTrans, m_nIndexX, 0, m_nIndexZ);
	m_stFloorTileTemplate.matFinal = matRot * matTransAfterRot * matTrans;
	m_stFloorTileTemplate.wstrTexture = m_pUI->getTileTexture(m_nTextureNum);

	//LoadObject(L"./Resources/Mesh/Wall1m.obj", m_vecObjectSample);
}

void cStageMapTool::Update()
{
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pUI)
		m_pUI->Update();

	Control();
}

void cStageMapTool::Render()
{
	if (m_pGrid)
		m_pGrid->Render();

	if (m_pUI)
		m_pUI->Render();

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	//�ٴ� Ÿ�� �׷��ش�.
	for (m_iterFloorTiles = m_mapFloorTiles.begin(); m_iterFloorTiles != m_mapFloorTiles.end(); ++m_iterFloorTiles)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_iterFloorTiles->second.matFinal);
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_iterFloorTiles->second.wstrTexture.c_str()));
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_iterFloorTiles->second.vecVertex.size() / 3, &m_iterFloorTiles->second.vecVertex[0], sizeof(ST_PNT_VERTEX));
	}
	//������Ʈ Ÿ�� �׷��ش�.
	for (m_iterObjectTiles = m_mapObjectTiles.begin(); m_iterObjectTiles != m_mapObjectTiles.end(); ++m_iterObjectTiles)
	{
		for (int i = 0; i < m_iterObjectTiles->second.size(); ++i)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_iterObjectTiles->second[i].matFinal);
			g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_iterObjectTiles->second[i].wstrTexture.c_str()));
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_iterObjectTiles->second[i].vecVertex.size() / 3, &m_iterObjectTiles->second[i].vecVertex[0], sizeof(ST_PNT_VERTEX));
		}
	}
	
	if (m_pUI->getTileType() == TT_FLOOR)	//Ŀ�� ��ġ�� ���� Ÿ���� �׷��ش�.
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_stFloorTileTemplate.matFinal);
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_stFloorTileTemplate.wstrTexture.c_str()));
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_stFloorTileTemplate.vecVertex.size() / 3, &m_stFloorTileTemplate.vecVertex[0], sizeof(ST_PNT_VERTEX));
	}
	else if (m_pUI->getTileType() == TT_OBJECT)	//Ŀ�� ��ġ�� ���� ������Ʈ�� �׷��ش�.
	{
		for (int i = 0; i < m_vecObjectSample.size(); ++i)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecObjectSample[i].matFinal);
			if (m_vecObjectSample[i].wstrTexture.size() > 0)
			{
				g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_vecObjectSample[i].wstrTexture.c_str()));
			}
			else
			{
				g_pD3DDevice->SetTexture(0, NULL);
			}
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecObjectSample[i].vecVertex.size() / 3, &m_vecObjectSample[i].vecVertex[0], sizeof(ST_PNT_VERTEX));
		}
	}


}

void cStageMapTool::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cStageMapTool::Control()
{
	//ī�޶� ��ġ ����
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_vecPos.z += 0.1f;
		m_pCamera->setVLookAt(m_vecPos);
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_vecPos.z -= 0.1f;
		m_pCamera->setVLookAt(m_vecPos);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_vecPos.x += 0.1f;
		m_pCamera->setVLookAt(m_vecPos);
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_vecPos.x -= 0.1f;
		m_pCamera->setVLookAt(m_vecPos);
	}
	//Ÿ���� ���� ����
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		m_fRotAngle -= D3DX_PI / 2.0f;
		if (m_fRotAngle <= -D3DX_PI * 2.0f)
			m_fRotAngle = 0.0f;
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		m_fRotAngle += D3DX_PI / 2.0f;
		if (m_fRotAngle >= D3DX_PI * 2.0f)
			m_fRotAngle = 0.0f;
	}
	//Ÿ�� ȸ�� �� ��ġ ���� ��Ʈ��
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		m_fTBRXAxis -= 0.5f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		m_fTBRXAxis += 0.5f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		m_fTBRZAxis += 0.5f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		m_fTBRZAxis -= 0.5f;
	}
	//���� ����
	cRay ray;
	float ratio = 0.0f;
	ratio = ray.getPickRayOrg().y / ray.getPickRayDir().y;
	m_nIndexX = (ray.getPickRayOrg().x - (ray.getPickRayDir().x * ratio));
	m_nIndexZ = (ray.getPickRayOrg().z - (ray.getPickRayDir().z * ratio));
	if (m_nIndexX < 0) m_nIndexX = 0;
	if (m_nIndexZ < 0) m_nIndexZ = 0;
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matTrans;
	D3DXMATRIX matTransBeforeRot;
	D3DXMATRIX matTransAfterRot;
	D3DXMatrixTranslation(&matTransBeforeRot, m_fTBRXAxis, 0, m_fTBRZAxis);
	D3DXMatrixRotationY(&matRot, m_fRotAngle);
	D3DXMatrixTranslation(&matTransAfterRot, 0.5f, 0, 0.5f);
	D3DXMatrixTranslation(&matTrans, m_nIndexX, 0, m_nIndexZ);
	m_stFloorTileTemplate.matFinal = matRot * matTransAfterRot * matTrans;
	m_stFloorTileTemplate.wstrTexture = m_pUI->getTileTexture(m_nTextureNum);
	for (int i = 0; i < m_vecObjectSample.size(); ++i)
	{
		m_vecObjectSample[i].matFinal = matTransBeforeRot * matRot * matTransAfterRot * matTrans;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		int menuNum;
		if (m_pUI->SelectMenu(menuNum) == true)
		{
			if (menuNum == MT_OPEN)
			{
				HANDLE file;
				DWORD read;

				OPENFILENAME ofn;

				WCHAR filePath[1024] = L"";
				ZeroMemory(&ofn, sizeof(OPENFILENAME));

				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = NULL;
				ofn.lpstrFile = filePath;
				ofn.nMaxFile = sizeof(filePath);
				ofn.nFilterIndex = true;
				ofn.nMaxFileTitle = NULL;
				ofn.lpstrFileTitle = NULL;
				ofn.lpstrInitialDir = NULL;
				ofn.lpstrFilter = L"OBJ Files(*.obj)\0*.obj\0";
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				if (GetOpenFileName(&ofn) == FALSE) return;

				wstring FullPath = ofn.lpstrFile;

				cObjLoader Loader;
				m_vecObjectSample.clear();
				LoadObject(FullPath.c_str(), m_vecObjectSample);

				m_pUI->setTextureNum(m_vecObjectSample.size());
			}
			else if (menuNum == MT_SAVE)
			{
				HANDLE file;
				DWORD write;

				OPENFILENAME ofn;
				WCHAR filePath[1024] = L"";
				ZeroMemory(&ofn, sizeof(OPENFILENAME));

				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = NULL;
				ofn.lpstrFile = filePath;
				ofn.nMaxFile = sizeof(filePath);
				ofn.nFilterIndex = true;
				ofn.nMaxFileTitle = NULL;
				ofn.lpstrFileTitle = NULL;
				ofn.lpstrInitialDir = NULL;
				ofn.lpstrFilter = L"All Files(*.*)\0*.*\0";			// �������ϳ��ӿ��� ������ �ִ� ������ �����ϴ� ���� ����
				ofn.Flags = OFN_OVERWRITEPROMPT;

				if (GetSaveFileName(&ofn) == false) return;

				wstring curMapFileName = ofn.lpstrFile;
				file = CreateFile(curMapFileName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);



				CloseHandle(file);
			}
			else if (menuNum == MT_TEXTURE1 || menuNum == MT_TEXTURE2 || menuNum == MT_TEXTURE3)
			{
				HANDLE file;
				DWORD read;

				OPENFILENAME ofn;

				WCHAR filePath[1024] = L"";
				ZeroMemory(&ofn, sizeof(OPENFILENAME));

				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = NULL;
				ofn.lpstrFile = filePath;
				ofn.nMaxFile = sizeof(filePath);
				ofn.nFilterIndex = true;
				ofn.nMaxFileTitle = NULL;
				ofn.lpstrFileTitle = NULL;
				ofn.lpstrInitialDir = NULL;
				ofn.lpstrFilter = L"PNG Files(*.png)\0*.png\0";
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				if (GetOpenFileName(&ofn) == FALSE) return;

				wstring FullPath = ofn.lpstrFile;
				m_vecObjectSample[menuNum - MT_TEXTURE1].wstrTexture = FullPath;
				/*
				WCHAR* token = NULL;
				WCHAR* text = &FullPath[0];
				wstring RelativePath = L"./Resources/Texture2D/";
				while (1)
				{
					token = wcstok_s(NULL, L"\\", &text);
					if (wcscmp(token, L"Texture2D") == 0) break;
				}
				RelativePath = RelativePath + text;
				m_vecObjectSample[menuNum - 6].wstrTexture = RelativePath;
				*/
			}
		}
		else if (m_pUI->SelectTile(m_nTextureNum) == true)
		{

		}
		else if (m_pUI->getTileType() == TT_FLOOR)
		{
			if (m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapFloorTiles.end())
			{
				m_mapFloorTiles.erase(m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			}
			m_mapFloorTiles.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), m_stFloorTileTemplate));
		}
		else if (m_pUI->getTileType() == TT_OBJECT)
		{
			if (m_mapObjectTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapObjectTiles.end())
			{
				m_mapObjectTiles.erase(m_mapObjectTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			}
			m_mapObjectTiles.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), m_vecObjectSample));
		}
	}
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		if (m_pUI->getTileType() == TT_FLOOR)
		{
			if (m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapFloorTiles.end())
			{
				m_mapFloorTiles.erase(m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			}
		}
		else if (m_pUI->getTileType() == TT_OBJECT)
		{
			if (m_mapObjectTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapObjectTiles.end())
			{
				m_mapObjectTiles.erase(m_mapObjectTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			}
		}
	}
}

void cStageMapTool::LoadObject(LPCTSTR fullpath, vector<ST_TILE>& objectVector)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<D3DXVECTOR3> vecN;
	vector<ST_PNT_VERTEX> vecPNT;
	vector<DWORD> vecAttbuf;
	CString mtlName;
	char token[TOKEN_SIZE];

	ifstream fin;
	fin.open(fullpath);

	if (fin.is_open() == false)
		assert(false && "fin.is_open() == false");

	while (1)
	{
		if (fin.eof())
		{
			if (vecPNT.size() > 0)
			{
				ST_TILE tempObj;
				tempObj.vecVertex = vecPNT;
				objectVector.push_back(tempObj);
				vecPNT.clear();
			}
			break;
		}

		fin >> token;

		if (!strcmp(token, "g") && vecPNT.size() > 0)
		{
			ST_TILE tempObj;
			tempObj.vecVertex = vecPNT;
			objectVector.push_back(tempObj);
			vecPNT.clear();
		}
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

				vecPNT.push_back(pnt);
			}
		}
	}

	fin.close();
}