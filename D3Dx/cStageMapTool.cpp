#include "stdafx.h"
#include "cStageMapTool.h"
#include "cCamera.h"
#include "cStageGrid.h"
#include "cRay.h"
#include "cStageMapToolUI.h"
#include "cStageObjManager.h"
#include "cActionObj.h"
#include "cIGObj.h"
#include "cCrate.h"
#include "cBackground.h"


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
	, m_pSOM(NULL)
	, m_nNewObjNum(0)
	, m_nMenuNum(0)
	, m_nCharacterSelect(0)
	, m_pBG(NULL)
{
}


cStageMapTool::~cStageMapTool()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pUI);
	SAFE_DELETE(m_pSOM);
	SAFE_DELETE(m_pBG);
}

void cStageMapTool::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cStageGrid;
	m_pGrid->Setup();

	m_pUI = new cStageMapToolUI;
	m_pUI->Setup();

	m_pSOM = new cStageObjManager;
	m_pSOM->Setup();

	m_pBG = new cBackground;
	m_pBG->Setup(1);

	//바닥 타일의 기초가 되는 사각형 셋팅
	ST_PNT_VERTEX tempV;
	tempV.p = D3DXVECTOR3(-0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stFloorTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 0);
	m_stFloorTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stFloorTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stFloorTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stFloorTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 1);
	m_stFloorTemplate.vecVertex.push_back(tempV);
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matTrans;
	D3DXMATRIX matTransAfterRot;
	D3DXMatrixRotationY(&matRot, m_fRotAngle);
	D3DXMatrixTranslation(&matTransAfterRot, 0.5f, 0, 0.5f);
	D3DXMatrixTranslation(&matTrans, m_nIndexX, 0, m_nIndexZ);
	m_stFloorTemplate.matFinal = matRot * matTransAfterRot * matTrans;
	m_stFloorTemplate.wstrTexture = m_pUI->getTileTexture(m_nTextureNum);

	//방해 타일의 기초가 되는 직육면체 설정
	////위면
	tempV.p = D3DXVECTOR3(-0.5f, BLOCK_HEIGHT, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, BLOCK_HEIGHT, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, BLOCK_HEIGHT, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, BLOCK_HEIGHT, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, BLOCK_HEIGHT, 0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, BLOCK_HEIGHT, -0.5f);
	tempV.n = D3DXVECTOR3(0, 1, 0);
	tempV.t = D3DXVECTOR2(1, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	////왼쪽면
	tempV.p = D3DXVECTOR3(-0.5f, BLOCK_HEIGHT, -0.1f);
	tempV.n = D3DXVECTOR3(-1, 0, 0);
	tempV.t = D3DXVECTOR2(1, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, -0.1f);
	tempV.n = D3DXVECTOR3(-1, 0, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, BLOCK_HEIGHT, 0.1f);
	tempV.n = D3DXVECTOR3(-1, 0, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, BLOCK_HEIGHT, 0.1f);
	tempV.n = D3DXVECTOR3(-1, 0, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, -0.1f);
	tempV.n = D3DXVECTOR3(-1, 0, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.5f, 0, 0.1f);
	tempV.n = D3DXVECTOR3(-1, 0, 0);
	tempV.t = D3DXVECTOR2(0, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	////오른쪽면
	tempV.p = D3DXVECTOR3(0.5f, BLOCK_HEIGHT, -0.1f);
	tempV.n = D3DXVECTOR3(1, 0, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, BLOCK_HEIGHT, 0.1f);
	tempV.n = D3DXVECTOR3(1, 0, 0);
	tempV.t = D3DXVECTOR2(0, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, 0.1f);
	tempV.n = D3DXVECTOR3(1, 0, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, BLOCK_HEIGHT, -0.1f);
	tempV.n = D3DXVECTOR3(1, 0, 0);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, 0.1f);
	tempV.n = D3DXVECTOR3(1, 0, 0);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.5f, 0, -0.1f);
	tempV.n = D3DXVECTOR3(1, 0, 0);
	tempV.t = D3DXVECTOR2(1, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	////앞면
	tempV.p = D3DXVECTOR3(-0.1f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 0, -1);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.1f, BLOCK_HEIGHT, -0.5f);
	tempV.n = D3DXVECTOR3(0, 0, -1);
	tempV.t = D3DXVECTOR2(0, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.1f, BLOCK_HEIGHT, -0.5f);
	tempV.n = D3DXVECTOR3(0, 0, -1);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.1f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 0, -1);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.1f, BLOCK_HEIGHT, -0.5f);
	tempV.n = D3DXVECTOR3(0, 0, -1);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.1f, 0, -0.5f);
	tempV.n = D3DXVECTOR3(0, 0, -1);
	tempV.t = D3DXVECTOR2(1, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	////뒷면
	tempV.p = D3DXVECTOR3(-0.1f, BLOCK_HEIGHT, 0.5f);
	tempV.n = D3DXVECTOR3(0, 0, 1);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.1f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 0, 1);
	tempV.t = D3DXVECTOR2(0, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.1f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 0, 1);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(-0.1f, BLOCK_HEIGHT, 0.5f);
	tempV.n = D3DXVECTOR3(0, 0, 1);
	tempV.t = D3DXVECTOR2(1, 0);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.1f, 0, 0.5f);
	tempV.n = D3DXVECTOR3(0, 0, 1);
	tempV.t = D3DXVECTOR2(0, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	tempV.p = D3DXVECTOR3(0.1f, BLOCK_HEIGHT, 0.5f);
	tempV.n = D3DXVECTOR3(0, 0, 1);
	tempV.t = D3DXVECTOR2(1, 1);
	m_stBlockTemplate.vecVertex.push_back(tempV);
	m_stBlockTemplate.matFinal = matRot * matTransAfterRot * matTrans;
	m_stBlockTemplate.wstrTexture = L"./Resources/StageTexture/FloorTile_20.png";
	m_stChefLocation[0].vecVertex = m_stBlockTemplate.vecVertex;
	m_stChefLocation[1].vecVertex = m_stBlockTemplate.vecVertex;
	m_stChefLocation[0].matFinal = matRot * matTransAfterRot * matTrans;
	m_stChefLocation[1].matFinal = matRot * matTransAfterRot * matTrans;
	m_stChefLocation[0].wstrTexture = L"./Resources/Texture2D/Level_Character_Icon_Buck.png";
	m_stChefLocation[1].wstrTexture = L"./Resources/Texture2D/Level_Character_Icon_Mel.png";
	
	m_stNewObjTemplate.p = NULL;
	m_stNewObjTemplate.type = CRATE_ONION;
}

void cStageMapTool::Update()
{
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pUI)
		m_pUI->Update();

	if (m_pSOM)
		m_pSOM->Update();

	Control();
}

void cStageMapTool::Render()
{
	if (m_pGrid)
		m_pGrid->Render();

	if (m_pUI)
		m_pUI->Render();

	if (m_pBG)
		m_pBG->Render(1);


	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	//바닥 타일 그려준다.
	for (m_iterFloorTiles = m_mapFloorTiles.begin(); m_iterFloorTiles != m_mapFloorTiles.end(); ++m_iterFloorTiles)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_iterFloorTiles->second.matFinal);
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_iterFloorTiles->second.wstrTexture.c_str()));
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_iterFloorTiles->second.vecVertex.size() / 3, &m_iterFloorTiles->second.vecVertex[0], sizeof(ST_PNT_VERTEX));
	}
	//오브젝트 타일 그려준다.
	for (m_iterObjectTiles = m_mapObjectTiles.begin(); m_iterObjectTiles != m_mapObjectTiles.end(); ++m_iterObjectTiles)
	{
		for (int i = 0; i < m_iterObjectTiles->second.size(); ++i)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_iterObjectTiles->second[i].matFinal);
			g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_iterObjectTiles->second[i].wstrTexture.c_str()));
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_iterObjectTiles->second[i].vecVertex.size() / 3, &m_iterObjectTiles->second[i].vecVertex[0], sizeof(ST_PNT_VERTEX));
		}
	}
	
	if (m_pUI->getTileType() == TT_FLOOR)	//커서 위치의 샘플 타일을 그려준다.
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_stFloorTemplate.matFinal);
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_stFloorTemplate.wstrTexture.c_str()));
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_stFloorTemplate.vecVertex.size() / 3, &m_stFloorTemplate.vecVertex[0], sizeof(ST_PNT_VERTEX));
	}
	else if (m_pUI->getTileType() == TT_OBJECT)	//커서 위치의 샘플 오브젝트를 그려준다.
	{
		for (int i = 0; i < m_vecObjectTemplate.size(); ++i)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecObjectTemplate[i].matFinal);
			if (m_vecObjectTemplate[i].wstrTexture.size() > 0)
			{
				g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_vecObjectTemplate[i].wstrTexture.c_str()));
			}
			else
			{
				g_pD3DDevice->SetTexture(0, NULL);
			}
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecObjectTemplate[i].vecVertex.size() / 3, &m_vecObjectTemplate[i].vecVertex[0], sizeof(ST_PNT_VERTEX));
		}
	}
	else if (m_pUI->getTileType() == TT_NEWOBJ)
	{

	}
	else if (m_pUI->getTileType() == TT_BLOCK) //커서 위치의 방해 타일과 깔린 방해 타일들을 그린다.
	{
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_stBlockTemplate.wstrTexture.c_str()));
		for (m_iterBlockTiles = m_mapBlockTiles.begin(); m_iterBlockTiles != m_mapBlockTiles.end(); ++m_iterBlockTiles)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_iterBlockTiles->second.matFinal);
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_iterBlockTiles->second.vecVertex.size() / 3, &m_iterBlockTiles->second.vecVertex[0], sizeof(ST_PNT_VERTEX));
		}
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_stBlockTemplate.matFinal);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_stBlockTemplate.vecVertex.size() / 3, &m_stBlockTemplate.vecVertex[0], sizeof(ST_PNT_VERTEX));
	}

	for (int i = 0; i < 2; ++i)
	{
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_stChefLocation[i].wstrTexture.c_str()));
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_stChefLocation[i].matFinal);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_stChefLocation[i].vecVertex.size() / 3, &m_stChefLocation[i].vecVertex[0], sizeof(ST_PNT_VERTEX));
	}

	if (m_pSOM)
		m_pSOM->Render();

}

void cStageMapTool::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cStageMapTool::Control()
{
	//카메라 위치 조작
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
	//타일의 각도 조작
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
	//타일 회전 전 위치 보정 컨트롤
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
	//레이 설정
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
	m_stFloorTemplate.matFinal = matRot * matTransAfterRot * matTrans;
	m_stFloorTemplate.wstrTexture = m_pUI->getTileTexture(m_nTextureNum);
	m_stBlockTemplate.matFinal = matRot * matTransAfterRot * matTrans;

	if (m_stNewObjTemplate.p)
	{
		m_stNewObjTemplate.p->SetWorldMatrix(matTransBeforeRot * matRot * matTransAfterRot * matTrans);
	}

	for (int i = 0; i < m_vecObjectTemplate.size(); ++i)
	{
		m_vecObjectTemplate[i].matFinal = matTransBeforeRot * matRot * matTransAfterRot * matTrans;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		int menuNum;
		D3DXMATRIX matIden;
		D3DXMatrixIdentity(&matIden);
		if (m_pUI->SelectMenu(menuNum) == true)
		{
			if (menuNum != MT_NEWOBJ && m_stNewObjTemplate.p != NULL)
			{
				m_pSOM->DeleteObject(m_stNewObjTemplate.iter);
				m_stNewObjTemplate.p = NULL;
			}
			else if (m_nMenuNum != menuNum && menuNum == MT_NEWOBJ)
			{
				m_stNewObjTemplate.iter = m_pSOM->SetIngameObject((OBJECTTYPE)m_stNewObjTemplate.type, matIden);
				m_stNewObjTemplate.p = (*m_stNewObjTemplate.iter);
			}
			if (menuNum == MT_OPEN)
			{
				MenuOpen();
			}
			else if (menuNum == MT_SAVE)
			{
				MenuSave();
			}
			else if (menuNum == MT_LOAD)
			{
				MenuLoad();
			}
			else if (menuNum == MT_TEXTURE1 || menuNum == MT_TEXTURE2 || menuNum == MT_TEXTURE3)
			{
				MenuTexture(menuNum);
			}
			m_nMenuNum = menuNum;
		}
		else if (m_nMenuNum == MT_LOAD)
		{
			m_stChefLocation[m_nCharacterSelect % 2].matFinal = matRot * matTransAfterRot * matTrans;
			m_nCharacterSelect++;
		}
		else if (m_nMenuNum == MT_FLOOR && m_pUI->SelectTile(m_nTextureNum) == true)
		{
			
		}
		else if (m_nMenuNum == MT_NEWOBJ && m_nNewObjNum == NOT_CRATE && m_pUI->SelectSubMenu() == true)
		{
			bool temp;
			m_pSOM->DeleteObject(m_stNewObjTemplate.iter);
			m_stNewObjTemplate.type = getObjectType(temp);
			m_stNewObjTemplate.iter = m_pSOM->SetIngameObject((OBJECTTYPE)m_stNewObjTemplate.type, matIden);
			m_stNewObjTemplate.p = (*m_stNewObjTemplate.iter);
		}
		else if (m_nMenuNum == MT_NEWOBJ && m_pUI->SelectNewObj(m_nNewObjNum) == true)
		{
			if (m_nNewObjNum == NOT_CRATE)
			{
				bool temp;
				m_pSOM->DeleteObject(m_stNewObjTemplate.iter);
				m_stNewObjTemplate.type = getObjectType(temp);
				m_stNewObjTemplate.iter = m_pSOM->SetIngameObject((OBJECTTYPE)m_stNewObjTemplate.type, matIden);
				m_stNewObjTemplate.p = (*m_stNewObjTemplate.iter);
			}
		}
		else if (m_pUI->getTileType() == TT_FLOOR)
		{
			//if (m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapFloorTiles.end())
			//{
			//	m_mapFloorTiles.erase(m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			//}
			//m_mapFloorTiles.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), m_stFloorTemplate));
		}
		else if (m_pUI->getTileType() == TT_OBJECT)
		{
			if (m_mapObjectTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapObjectTiles.end())
			{
				m_mapObjectTiles.erase(m_mapObjectTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			}
			m_mapObjectTiles.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), m_vecObjectTemplate));
		}
		else if (m_pUI->getTileType() == TT_NEWOBJ)
		{
			bool isSetObj;
			ST_NEWOBJ temp;
			temp.matFinal = matTransBeforeRot * matRot * matTransAfterRot * matTrans;
			temp.type = getObjectType(isSetObj);
			if (isSetObj == true)
			{
				m_iterSetObject = m_mapSetObject.find(make_pair(m_nIndexX, m_nIndexZ));
				if (m_iterSetObject != m_mapSetObject.end())
				{
					m_pSOM->DeleteObject(m_iterSetObject->second.iter);
					m_mapSetObject.erase(m_iterSetObject);
				}
			}
			else
			{
				m_iterNewObject = m_mapNewObject.find(make_pair(m_nIndexX, m_nIndexZ));
				if (m_iterNewObject != m_mapNewObject.end())
				{
					m_pSOM->DeleteObject(m_iterNewObject->second.iter);
					m_mapNewObject.erase(m_iterNewObject);
				}
			}
			temp.iter = m_pSOM->SetIngameObject((OBJECTTYPE)temp.type, temp.matFinal);
			temp.p = (*temp.iter);
			if (isSetObj == true)
			{
				m_iterNewObject = m_mapNewObject.find(make_pair(m_nIndexX, m_nIndexZ));
				if (m_iterNewObject != m_mapNewObject.end())
				{
					m_iterNewObject->second.p->SetInven(temp.p);
				}
				m_mapSetObject.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), temp));
			}
			else
			{
				m_mapNewObject.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), temp));
			}
		}
		else if (m_pUI->getTileType() == TT_BLOCK)
		{
			if (m_mapBlockTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapBlockTiles.end())
			{
				m_mapBlockTiles.erase(m_mapBlockTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			}
			m_mapBlockTiles.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), m_stBlockTemplate));
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (m_pUI->getTileType() == TT_FLOOR)
		{
			if (m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapFloorTiles.end())
			{
				m_mapFloorTiles.erase(m_mapFloorTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
			}
			m_mapFloorTiles.insert(make_pair(make_pair(m_nIndexX, m_nIndexZ), m_stFloorTemplate));
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
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
		else if (m_pUI->getTileType() == TT_NEWOBJ)
		{
			m_iterNewObject = m_mapNewObject.find(make_pair(m_nIndexX, m_nIndexZ));
			if (m_iterNewObject != m_mapNewObject.end())
			{
				m_pSOM->DeleteObject(m_iterNewObject->second.iter);
				m_mapNewObject.erase(m_iterNewObject);
			}
			m_iterNewObject = m_mapSetObject.find(make_pair(m_nIndexX, m_nIndexZ));
			if (m_iterNewObject != m_mapSetObject.end())
			{
				m_pSOM->DeleteObject(m_iterNewObject->second.iter);
				m_mapSetObject.erase(m_iterNewObject);
			}
		}
		else if (m_pUI->getTileType() == TT_BLOCK)
		{
			if (m_mapBlockTiles.find(make_pair(m_nIndexX, m_nIndexZ)) != m_mapBlockTiles.end())
			{
				m_mapBlockTiles.erase(m_mapBlockTiles.find(make_pair(m_nIndexX, m_nIndexZ)));
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

void cStageMapTool::MenuOpen()
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
	m_vecObjectTemplate.clear();
	LoadObject(FullPath.c_str(), m_vecObjectTemplate);

	m_pUI->setTextureNum(m_vecObjectTemplate.size());
}

void cStageMapTool::MenuSave()
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
	ofn.lpstrFilter = L"MAP Files(*.map)\0*.map\0";
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == false) return;

	wstring curMapFileName = ofn.lpstrFile;
	file = CreateFile(curMapFileName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	map<wstring, int> mapAttributeNum;
	map<wstring, int>::iterator iterAttributeNum;
	int attributeNum = 0;
	int maxVectorSize = 0;
	vector<ST_PNT_VERTEX>		vecVertex;
	vector<WORD>				vecIndex;
	vector<DWORD>				vecAttribute;
	ST_PNT_VERTEX tempVertex;
	vector<ST_PNT_VERTEX> tempVector;
	for (m_iterFloorTiles = m_mapFloorTiles.begin(); m_iterFloorTiles != m_mapFloorTiles.end(); ++m_iterFloorTiles)
	{
		iterAttributeNum = mapAttributeNum.find(m_iterFloorTiles->second.wstrTexture);
		if (iterAttributeNum == mapAttributeNum.end())
		{
			mapAttributeNum[m_iterFloorTiles->second.wstrTexture] = attributeNum;
			attributeNum++;
			iterAttributeNum = mapAttributeNum.find(m_iterFloorTiles->second.wstrTexture);
		}
		for (int i = 0; i < m_iterFloorTiles->second.vecVertex.size(); ++i)
		{
			tempVertex = m_iterFloorTiles->second.vecVertex[i];
			D3DXVec3TransformCoord(
				&tempVertex.p,
				&m_iterFloorTiles->second.vecVertex[i].p,
				&m_iterFloorTiles->second.matFinal);
			vecVertex.push_back(tempVertex);
			vecIndex.push_back(maxVectorSize);
			maxVectorSize++;
			if (i % 3 == 0) vecAttribute.push_back(iterAttributeNum->second);
		}
	}
	for (m_iterObjectTiles = m_mapObjectTiles.begin(); m_iterObjectTiles != m_mapObjectTiles.end(); ++m_iterObjectTiles)
	{
		for (int i = 0; i < m_iterObjectTiles->second.size(); ++i)
		{
			WCHAR* token = NULL;
			wstring buffer = m_iterObjectTiles->second[i].wstrTexture;
			WCHAR* text = &buffer[0];
			wstring RelativePath = L"./Resources/Texture2D/";
			while (1)
			{
				token = wcstok_s(NULL, L"\\", &text);
				if (wcscmp(token, L"Texture2D") == 0) break;
			}
			RelativePath = RelativePath + text;
			iterAttributeNum = mapAttributeNum.find(RelativePath);
			if (iterAttributeNum == mapAttributeNum.end())
			{
				mapAttributeNum[RelativePath] = attributeNum;
				attributeNum++;
				iterAttributeNum = mapAttributeNum.find(RelativePath);
			}
			for (int j = 0; j < m_iterObjectTiles->second[i].vecVertex.size(); ++j)
			{
				tempVertex = m_iterObjectTiles->second[i].vecVertex[j];
				D3DXVec3TransformCoord(
					&tempVertex.p,
					&m_iterObjectTiles->second[i].vecVertex[j].p,
					&m_iterObjectTiles->second[i].matFinal);
				vecVertex.push_back(tempVertex);
				vecIndex.push_back(maxVectorSize);
				maxVectorSize++;
				if (j % 3 == 0) vecAttribute.push_back(iterAttributeNum->second);
			}
		}
	}

	int maxTexture = mapAttributeNum.size();
	WriteFile(file, &maxTexture, sizeof(int), &write, NULL);
	for (iterAttributeNum = mapAttributeNum.begin(); iterAttributeNum != mapAttributeNum.end(); ++iterAttributeNum)
	{
		int num = iterAttributeNum->second;
		wstring wstr = iterAttributeNum->first;
		WriteFile(file, &num, sizeof(int), &write, NULL);
		int length = wstr.size();
		WriteFile(file, &length, sizeof(int), &write, NULL);
		WriteFile(file, &wstr[0], length * sizeof(WCHAR), &write, NULL);
	}
	WriteFile(file, &maxVectorSize, sizeof(int), &write, NULL);
	WriteFile(file, &vecVertex[0], sizeof(ST_PNT_VERTEX) * vecVertex.size(), &write, NULL);
	WriteFile(file, &vecIndex[0], sizeof(WORD) * vecIndex.size(), &write, NULL);
	WriteFile(file, &vecAttribute[0], sizeof(DWORD) * vecAttribute.size(), &write, NULL);

	int maxNewObjSize = m_mapNewObject.size();
	WriteFile(file, &maxNewObjSize, sizeof(int), &write, NULL);
	for (m_iterNewObject = m_mapNewObject.begin(); m_iterNewObject != m_mapNewObject.end(); ++m_iterNewObject)
	{
		WriteFile(file, &m_iterNewObject->second.matFinal, sizeof(D3DXMATRIX), &write, NULL);
		WriteFile(file, &m_iterNewObject->second.type, sizeof(int), &write, NULL);
	}
	int maxSetObjSize = m_mapSetObject.size();
	WriteFile(file, &maxSetObjSize, sizeof(int), &write, NULL);
	for (m_iterSetObject = m_mapSetObject.begin(); m_iterSetObject != m_mapSetObject.end(); ++m_iterSetObject)
	{
		WriteFile(file, &m_iterSetObject->second.matFinal, sizeof(D3DXMATRIX), &write, NULL);
		WriteFile(file, &m_iterSetObject->second.type, sizeof(int), &write, NULL);
	}

	int maxBlockSize = m_mapBlockTiles.size();
	WriteFile(file, &maxBlockSize, sizeof(int), &write, NULL);
	for (m_iterBlockTiles = m_mapBlockTiles.begin(); m_iterBlockTiles != m_mapBlockTiles.end(); ++m_iterBlockTiles)
	{
		WriteFile(file, &m_iterBlockTiles->first, sizeof(pair<int, int>), &write, NULL);
	}

	D3DXVECTOR3 vecTemp(0, 0, 0);
	vecTemp.x = m_stChefLocation[0].matFinal._41;
	vecTemp.z = m_stChefLocation[0].matFinal._43;
	WriteFile(file, &vecTemp, sizeof(D3DXVECTOR3), &write, NULL);
	vecTemp.x = m_stChefLocation[1].matFinal._41;
	vecTemp.z = m_stChefLocation[1].matFinal._43;
	WriteFile(file, &vecTemp, sizeof(D3DXVECTOR3), &write, NULL);

	CloseHandle(file);
}

void cStageMapTool::MenuLoad()
{

}

void cStageMapTool::MenuTexture(int menuNum)
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
	m_vecObjectTemplate[menuNum - MT_TEXTURE1].wstrTexture = FullPath;
}

int cStageMapTool::getObjectType(bool& isSetObject)
{
	switch (m_pUI->getNewObjTileType())
	{
		case(NOT_CRATE):
		{
			isSetObject = false;
			switch (m_pUI->getCrateType())
			{
			case(CT_MUSHROOM):
			{
				return(CRATE_MUSHROOM);
			}
			break;
			case(CT_ONION):
			{
				return(CRATE_ONION);
			}
			break;
			case(CT_POTATO):
			{
				return(CRATE_POTATO);
			}
			break;
			case(CT_TOMATO):
			{
				return(CRATE_TOMATO);
			}
			break;
			}
		}
		break;
		case(NOT_BIN):
		{
			isSetObject = false;
			return(AOBJ_BIN);
		}
		break;
		case(NOT_CHOPPINGBOARD):
		{
			isSetObject = false;
			return(AOBJ_TABLE3);
		}
		break;
		case(NOT_COOKER):
		{
			isSetObject = false;
			return(AOBJ_COOKER);
		}
		break;
		case(NOT_PASS):
		{
			isSetObject = false;
			return(AOBJ_PASS);
		}
		break;
		case(NOT_PLATE):
		{
			isSetObject = false;
			return(AOBJ_TABLE2);
		}
		break;
		case(NOT_PLATERETURNBOX):
		{
			isSetObject = false;
			return(AOBJ_PLATERETURNBOX);
		}
		break;
		case(NOT_POT):
		{
			isSetObject = false;
			return(AOBJ_POT);
		}
		break;
		case(NOT_SINK):
		{
			isSetObject = false;
			return(AOBJ_SINK);
		}
		break;
		case(NOT_TABLE):
		{
			isSetObject = false;
			return(AOBJ_TABLE);
		}
		break;
	}

	return CRATE_ONION;
}
