#include "stdafx.h"
#include "cStageScene.h"
#include "cStage.h"
#include "cCamera.h"
#include "cStageGrid.h"
#include "cStageObjManager.h"
#include "cChef.h"
#include "cCharacterControl.h"
#include "cCollision.h"
#include "cBackground.h"
#include "cStageUI.h"


cStageScene::cStageScene()
	: m_pStage(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_vecPos(0, 0, 0)
	, m_pSOM(NULL)
	, m_pControl(NULL)
	, m_pCollision(NULL)
	, m_pBG(NULL)
	, m_pStageUI(NULL)
	, m_nTimer(0)
	, m_bPause(false)
{
	m_pChef[0] = NULL;
	m_pChef[1] = NULL;
}


cStageScene::~cStageScene()
{
	SAFE_DELETE(m_pStage);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pSOM);
	SAFE_DELETE(m_pControl);
	SAFE_DELETE(m_pChef[0]);
	SAFE_DELETE(m_pChef[1]);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pBG);
	SAFE_DELETE(m_pStageUI);
}

void cStageScene::Setup()
{
	m_pStage = new cStage;
	m_pStage->Setup(DATABASE->GetstageNum(), m_vNewObjData, m_vSetObjData, m_mapIsBlockedData, m_vecChefPos[0], m_vecChefPos[1]);

	DATABASE->SetTip(0);

	m_pStageUI = new cStageUI;
	m_pStageUI->Setup();

	m_pBG = new cBackground;
	m_pBG->Setup(DATABASE->GetstageNum());

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
		m_pControl->AddcCharacter(m_pChef[i]);
		m_pChef[i]->SetUp(m_vecChefPos[i], m_pControl);
		m_pChef[i]->setcStageObjManagerAdressLink(m_pSOM);
	}
	m_pSOM->Setplayer1(m_pChef[0]);
	m_pSOM->Setplayer2(m_pChef[1]);

	m_pCamera->setVLookAt(m_pControl->GetControlPlayer()->GetPos());
	m_pCamera->setRotX(D3DX_PI / 4);
	m_pCamera->setDistance(10.0f);

	m_pCollision = new cCollision;
	m_pCollision->setPlayerMemoryAddressLink(0, m_pChef[0]);
	m_pCollision->setPlayerMemoryAddressLink(1, m_pChef[1]);
	m_pCollision->setStageObjManagerMemoryAddressLink(m_pSOM);
	m_pCollision->setMapIsBlockedData(m_mapIsBlockedData);
	m_pCollision->Setup();

	m_bCameraSetting = false;
	m_fCameraAngle = 240.0f;
}

void cStageScene::Update()
{
	if (m_pCamera)
	{
		m_pCamera->Update();
		if (m_pControl->GetPlayerMod() == PLAYERMOD_PLAY2P)
		{
			D3DXVECTOR3 cameraPos = (m_pChef[0]->GetPos() + m_pChef[1]->GetPos()) / 2;
			m_pCamera->setDistance(10.0f + GetDistance(m_pChef[0]->GetPos(), m_pChef[1]->GetPos()));
			m_pCamera->setVLookAt(cameraPos);
		}
		else if (m_pControl->GetPlayerMod() == PLAYERMOD_PLAY1P)
		{
			m_pCamera->setVLookAt(m_pControl->GetControlPlayer()->GetPos());
		}
		if (m_bCameraSetting == false)
		{
			m_pCamera->setRotY(m_fCameraAngle * 0.03f);
			m_pCamera->setRotX(D3DX_PI / 4 - (m_fCameraAngle * D3DX_PI / 3 / 240.0f));
			m_pCamera->setDistance(10.0f + m_fCameraAngle * 5.0f);
			m_fCameraAngle--;
			if (m_fCameraAngle < 1)
			{
				m_bCameraSetting = true;
				m_pCamera->setRotY(0);
				m_pCamera->setRotX(D3DX_PI / 4);
				m_pCamera->setDistance(10.0f);
			}
		}
		Control();
	}

	if (m_bCameraSetting == true && m_bPause == false)
	{
		if (m_pSOM)
			m_pSOM->Update();

		if (m_pControl)
		{
			m_pControl->Control();
		}


		for (int i = 0; i < 2; i++)
		{
			m_pChef[i]->Update();
		}

		if (m_pCollision)
			m_pCollision->Update();

		if (m_pStageUI)
			m_pStageUI->Update();

		if (m_pStage)
			m_pStage->Update();
	}

	m_nTimer++;
}

void cStageScene::Render()
{
	if (m_pStageUI->getTimeUp() == true)
	{
		m_bPause = true;
		if (m_pStageUI->StageOutro() == false)
		{
			SCENEMANAGER->ChangeScene("WMScene");
		}
	}

	if (m_pStage)
		m_pStage->Render();

	if (m_pStageUI)
	{
		m_pStageUI->StageIntro(m_nTimer);
		m_pStageUI->Render();
	}

	//if (m_pGrid)
	//	m_pGrid->Render();

	if (m_pSOM)
		m_pSOM->Render();

	for (int i = 0; i < 2; i++)
	{
		m_pChef[i]->Render();
	}

	if (m_pBG)
		m_pBG->Render(DATABASE->GetstageNum());
}

void cStageScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cStageScene::Control()
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
