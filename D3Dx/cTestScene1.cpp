#include "stdafx.h"
#include "cTestScene1.h"
#include "cStage.h"
#include "cCamera.h"
#include "cStageGrid.h"
#include "cStageObjManager.h"
#include "cChef.h"
#include "cCharacterControl.h"
#include "cCollision.h"
#include "cChefRoot.h"


cTestScene1::cTestScene1()
	: m_pStage(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_vecPos(0, 0, 0)
	, m_pSOM(NULL)
	, m_pControl(NULL)
	, m_pCollision(NULL)
{
	m_pChef[0] = NULL;
	m_pChef[1] = NULL;
}


cTestScene1::~cTestScene1()
{
	SAFE_DELETE(m_pStage);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pSOM);
	SAFE_DELETE(m_pControl);
	SAFE_DELETE(m_pChef[0]);
	SAFE_DELETE(m_pChef[1]);
	SAFE_DELETE(m_pCollision);
}

void cTestScene1::Setup()
{
	m_pStage = new cStage;
	m_pStage->Setup(4, m_vNewObjData, m_vSetObjData, m_mapIsBlockedData, m_vecChefPos[0], m_vecChefPos[1]);

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cStageGrid;
	m_pGrid->Setup();

	m_pSOM = new cStageObjManager;
	m_pSOM->Setup();
	for (int i = 0; i < m_vNewObjData.size(); ++i)
	{
		m_pSOM->SetIngameObject((OBJECTTYPE)m_vNewObjData[i].first, m_vNewObjData[i].second);
	}
	for (int i = 0; i < m_vSetObjData.size(); ++i)
	{
		m_pSOM->SetIngameObject((OBJECTTYPE)m_vSetObjData[i].first, m_vSetObjData[i].second);
	}

	m_pControl = new cCharacterControl;
	for (int i = 0; i < 2; i++)
	{
		m_pChef[i] = new cChef;
		m_pChef[i]->SetUp(m_vecChefPos[i], m_pControl);
		m_pControl->AddcCharacter(m_pChef[i]);
		m_pChef[i]->setcStageObjManagerAdressLink(m_pSOM);
		
	}
	m_pSOM->Setplayer1(m_pChef[0]);
	m_pSOM->Setplayer2(m_pChef[1]);

	m_pCollision = new cCollision;
	m_pCollision->setPlayerMemoryAddressLink(0, m_pChef[0]);
	m_pCollision->setPlayerMemoryAddressLink(1, m_pChef[1]);
	m_pCollision->setStageObjManagerMemoryAddressLink(m_pSOM);
	m_pCollision->setMapIsBlockedData(m_mapIsBlockedData);
	m_pCollision->Setup();


	AddFontResource(L"궁서체.ttf");

	D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, L"궁서체", &m_pFont);

}

void cTestScene1::Update()
{
	if (m_pCamera)
	{
		m_pCamera->Update();
		Control();
	}

	if (m_pSOM)
		m_pSOM->Update();
	
	for (int i = 0; i < 2; i++)
	{
		m_pChef[i]->Update();
	}
	if (m_pControl)
		m_pControl->Control();

	if (m_pCollision)
		m_pCollision->Update();


}

void cTestScene1::Render()
{
	RECT rc;
	SetRect(&rc, 10, 100, 1000, 1000);
	bool chef =m_pChef[0]->GetDetect();
	if (chef)
		chef = m_pChef[0]->GetDetect()->GetInven();
	char str[128];
	sprintf_s(str, "inven :: %d", chef);
	WCHAR strX[1024];
	MultiByteToWideChar(CP_ACP, 0, str, -1, strX, 1024);

	m_pFont->DrawText(NULL, strX, strlen(str), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	RECT rcz;
	SetRect(&rcz, 10, 300, 1000, 1000);
	bool chefs = m_pChef[1]->GetDetect();
	if (chefs)
		chefs = m_pChef[1]->GetDetect()->GetInven();
	char strs[128];
	sprintf_s(strs, " inven :: %d", chefs);
	WCHAR strXs[1024];
	MultiByteToWideChar(CP_ACP, 0, strs, -1, strXs, 1024);

	m_pFont->DrawText(NULL, strXs, strlen(strs), &rcz,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	if (m_pStage)
		m_pStage->Render();

	if (m_pGrid)
		m_pGrid->Render();

	if (m_pSOM)
		m_pSOM->Render();

	for (int i = 0; i < 2; i++)
	{
		m_pChef[i]->Render();
	}
}

void cTestScene1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cTestScene1::Control()
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
}
