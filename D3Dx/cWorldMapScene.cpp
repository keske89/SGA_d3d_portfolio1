#include "stdafx.h"
#include "cWorldMapScene.h"

#include "cWMDefinition.h"
#include "IDisplayObject.h"

#include "cWorldGrid.h"
#include "cWorldMapCar.h"
#include "cSphere.h"
#include "cPath.h"
#include "cWorldTile.h"

#include "cWMCloud.h"

#include "cWorldStage.h"

#include "cWMapMenu.h"

#include "cCamera.h"

cWorldMapScene::cWorldMapScene()
{
	D3DXMatrixIdentity(&m_matWorld);
}


cWorldMapScene::~cWorldMapScene()
{	
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pWorldGrid);
	SAFE_RELEASE(m_pCar);

	for (auto p : m_pStage)
	{
		SAFE_RELEASE(p);
	}

	SAFE_RELEASE(m_UI);

	for (auto p : m_pCloud)
	{
		SAFE_RELEASE(p);
	}

}


void cWorldMapScene::Setup()
{
	_alpha = 255;
	_isChangeDone = false;

	//=================================================================================
	IMAGEMANAGER->addImage(_T("blackMask"), _T(".\\Resources\\ui\\blackMask.png"));

	m_pWorldGrid = new cWorldGrid;
	m_pWorldGrid->Setup();

	D3DXVECTOR3 temppos(40, 5, 20);

	auto temp = DXUtil::Convert3DTo2D(temppos);
	temppos.x = temp.x;
	temppos.y = temp.y;
	temppos.z = 0;

	m_pCar = new cWorldMapCar;
	m_pCar->Setup();

	m_pStage[0] = new cWorldStage; m_pStage[0]->setType(STAGE_WATER); 	 m_pStage[0]->SetNextPos(D3DXVECTOR3(40, 0, 20));	  m_pStage[0]->setPosition(&D3DXVECTOR3(0, 0, 0));		 m_pStage[0]->setStageNum(DXUtil::MakePoint(1, 1)); m_pStage[0]->setCar(m_pCar);	m_pStage[0]->Setup();
	m_pStage[1] = new cWorldStage; m_pStage[1]->setType(STAGE_GRASS);														  m_pStage[1]->setPosition(&D3DXVECTOR3(10, 0, 10));	 m_pStage[1]->setStageNum(DXUtil::MakePoint(1, 2)); m_pStage[1]->setCar(m_pCar);	m_pStage[1]->Setup();
	m_pStage[2] = new cWorldStage; m_pStage[2]->setType(STAGE_SAND);														  m_pStage[2]->setPosition(&D3DXVECTOR3(20, 0, 20));	 m_pStage[2]->setStageNum(DXUtil::MakePoint(1, 3)); m_pStage[2]->setCar(m_pCar);	m_pStage[2]->Setup();
	m_pStage[3] = new cWorldStage; m_pStage[3]->setType(STAGE_WATER);														  m_pStage[3]->setPosition(&D3DXVECTOR3(30, 0, 30));	 m_pStage[3]->setStageNum(DXUtil::MakePoint(1, 4)); m_pStage[3]->setCar(m_pCar);	m_pStage[3]->Setup();
	m_pStage[4] = new cWorldStage; m_pStage[4]->setType(STAGE_GRASS);														  m_pStage[4]->setPosition(&D3DXVECTOR3(40, 0, 40));	 m_pStage[4]->setStageNum(DXUtil::MakePoint(2, 1)); m_pStage[4]->setCar(m_pCar);	m_pStage[4]->Setup();
	m_pStage[5] = new cWorldStage; m_pStage[5]->setType(STAGE_SAND);														  m_pStage[5]->setPosition(&D3DXVECTOR3(-10, 0, -10));	 m_pStage[5]->setStageNum(DXUtil::MakePoint(2, 2)); m_pStage[5]->setCar(m_pCar);	m_pStage[5]->Setup();
	m_pStage[6] = new cWorldStage; m_pStage[6]->setType(STAGE_WATER);														  m_pStage[6]->setPosition(&D3DXVECTOR3(-20, 0, -20));	 m_pStage[6]->setStageNum(DXUtil::MakePoint(2, 3)); m_pStage[6]->setCar(m_pCar);	m_pStage[6]->Setup();
	m_pStage[7] = new cWorldStage; m_pStage[7]->setType(STAGE_GRASS);														  m_pStage[7]->setPosition(&D3DXVECTOR3(-30, 0, -30));	 m_pStage[7]->setStageNum(DXUtil::MakePoint(2, 3)); m_pStage[7]->setCar(m_pCar);	m_pStage[7]->Setup();
	m_pStage[8] = new cWorldStage; m_pStage[8]->setType(STAGE_SAND);														  m_pStage[8]->setPosition(&D3DXVECTOR3(-40, 0, -40));	 m_pStage[8]->setStageNum(DXUtil::MakePoint(3, 1)); m_pStage[8]->setCar(m_pCar);	m_pStage[8]->Setup();
	m_pStage[9] = new cWorldStage; m_pStage[9]->setType(STAGE_GRASS);	 m_pStage[9]->SetPathType(PATH_CURVED);				  m_pStage[9]->setPosition(&D3DXVECTOR3(10, 0, 30));	 m_pStage[9]->setStageNum(DXUtil::MakePoint(3, 2)); m_pStage[9]->setCar(m_pCar);	m_pStage[9]->Setup();

	m_UI = new cWMapMenu(); m_UI->setPosition(&D3DXVECTOR3(0, 80, 0)); m_UI->Setup();

	m_pCloud[0] = new cWMCloud;  m_pCloud[0]->setPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[0]->Setup();
	m_pCloud[1] = new cWMCloud;  m_pCloud[1]->setPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[1]->Setup();
	m_pCloud[2] = new cWMCloud;  m_pCloud[2]->setPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[2]->Setup();
	m_pCloud[3] = new cWMCloud;  m_pCloud[3]->setPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[3]->Setup();
	m_pCloud[4] = new cWMCloud;  m_pCloud[4]->setPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[4]->Setup();
	m_pCloud[5] = new cWMCloud;  m_pCloud[5]->setPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f));  m_pCloud[5]->Setup();
	m_pCloud[6] = new cWMCloud;  m_pCloud[6]->setPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f));  m_pCloud[6]->Setup();
	m_pCloud[7] = new cWMCloud;  m_pCloud[7]->setPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, -rand() % 600 / 10.0f)); m_pCloud[7]->Setup();
	m_pCloud[8] = new cWMCloud;  m_pCloud[8]->setPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, -rand() % 600 / 10.0f)); m_pCloud[8]->Setup();
	m_pCloud[9] = new cWMCloud;  m_pCloud[9]->setPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, -rand() % 600 / 10.0f)); m_pCloud[9]->Setup();

	//=================================================================================
	D3DXVECTOR3 dir(-1, -1, -1);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	//=================================================================================
	_isChange = false;
	_alpha1 = 0;

	for (int i = 0; i  < 10 ; i++)
	{
		m_bIsStageclear[i] = DATABASE->getIsStageClear(i);
		m_nStar[i] = DATABASE->getStageStar(i);
		//m_pStage[i]->setStar(DATABASE->getStageStar(i));
	}

	SOUNDMANAGER->addSound("WMBGM", "./sound/OnionHouseMusic.mp3", true, true);
	SOUNDMANAGER->play("WMBGM", CH_BGM, 1.0f);
}

void cWorldMapScene::Update()
{
	/*if (!SOUNDMANAGER->isPlaySound("WMBGM"))
	{
		SOUNDMANAGER->play("WMBGM", CH_BGM, 1.0f);
	}*/
	
	if (!_isChangeDone)
	{
		_alpha--;
		if (_alpha <= 0)
		{
			_alpha = 0;
			_isChangeDone = true;
		}
	}
	else if (_isChange)
	{
		_alpha1+=3;
		if (_alpha1 >= 255)
		{
			if (_nextScene == "SelectScene")
			{
				DATABASE->SetstageNum(2);
				SCENEMANAGER->ChangeScene("SelectScene");
				SCENEMANAGER->Setup();
			}
		}
	}
	else
	{
		if (m_pCamera)
		{
			m_pCamera->Update();
			Control();
		}

		m_pWorldGrid->Update();

		m_pCar->Update();

		for (auto p : m_pStage)
		{
			if (p)
				p->Update();
		}

		for (int i = 0; i < 10; i++)
		{
			if (m_pStage[i]->getSphere()->getBS().isPicked) //차& 스테이지구 충돌
			{
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					_nextScene = "SelectScene";
					_isChange = true;
				}

				//if (m_bIsStageclear[i])
				//{
				//	m_pStage[i]->SetAnimation(true); //path & tile animation setting 함수
				//}

			}
			
			if (m_bIsStageclear[i])
			{
				m_pStage[i]->SetAnimation(true); //path & tile animation setting 함수
			}

		}

		m_UI->Update();

		for (auto p : m_pCloud)
		{
			p->Update();
			D3DXMATRIX mat = p->GetWorldMatrix()*m_matWorld;
			p->setWorldMatrix(&mat);
		}

		for (int i = 0; i <10; i++)
		{
			m_bIsStageclear[i] = DATABASE->getIsStageClear(i);
			m_nStar[i] = DATABASE->getStageStar(i);
			m_pStage[i]->setStar(m_nStar[i]);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		m_bIsStageclear[5] = true;
	}
}

DWORD FtoDw(float f) { return *((DWORD*)&f); }

void cWorldMapScene::Render()
{
	////===============================================================
	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, 0xffffffff);
	g_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, FtoDw(0.1f));         // 안개의 강도
	g_pD3DDevice->SetRenderState(D3DRS_FOGSTART, FtoDw(22.0f));         // 안개의 시작 위치
	g_pD3DDevice->SetRenderState(D3DRS_FOGEND, FtoDw(50.0f));         // 안개 강도의 최대값 위치
	g_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);      // 안개 중간 보간값

	////================================================FOG START=======
	m_pWorldGrid->Render();
	m_pCar->Render();

	for (auto p : m_pCloud)
	{
		if (p) p->Render();
	}

	for (auto p : m_pStage)
	{
		if (p)
			p->Render();
	}

	////===============================================FOG END=========
	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, false);
	////===============================================================

	m_UI->Render();

	if (!_isChangeDone)
	{
		IMAGEMANAGER->alphaRender(_T("blackMask"), _alpha);
	}


	if (_isChange)
	{
		IMAGEMANAGER->alphaRender(_T("blackMask"), _alpha1);
	}

}

void cWorldMapScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cWorldMapScene::Control()
{
	//카메라 위치 조작
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		//m_pCar-.z += 0.1f;
		m_pCamera->setVLookAt(m_pCar->GetPosition());
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		//m_vecPos.z -= 0.1f;
		m_pCamera->setVLookAt(m_pCar->GetPosition());
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//m_vecPos.x += 0.1f;
		m_pCamera->setVLookAt(m_pCar->GetPosition());
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		//m_vecPos.x -= 0.1f;
		m_pCamera->setVLookAt(m_pCar->GetPosition());
	}
}