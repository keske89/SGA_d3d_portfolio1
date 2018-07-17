#include "stdafx.h"
#include "cWorldMapScene.h"

//#include "IDisplayObject.h"
//
//#include "cWorldGrid.h"
//#include "cWorldMapCar.h"
//#include "cSphere.h"
//#include "cPath.h"
//#include "cWorldTile.h"
//
//#include "cWMCloud.h"
//
//#include "cWorldStage.h"
//
//#include "SampleUI.h"

#include "cCamera.h"

cWorldMapScene::cWorldMapScene()
{
	D3DXMatrixIdentity(&m_matWorld);
}


cWorldMapScene::~cWorldMapScene()
{	
	SAFE_RELEASE(m_pFont);
	//SAFE_RELEASE(m_pWorldGrid);
	//SAFE_RELEASE(m_pCar);

	//for (auto p : m_pStage)
	//{
	//	SAFE_RELEASE(p);
	//}

	//SAFE_RELEASE(m_UI);

	//for (auto p : m_pCloud)
	//{
	//	SAFE_RELEASE(p);
	//}

}


void cWorldMapScene::Setup()
{
	//_alpha = 255;
	//_isChangeDone = false;

	//AddFontResource(L"궁서체.ttf");

	//D3DXCreateFont(g_pD3DDevice, 96, 48, FW_NORMAL, NULL, true, DEFAULT_CHARSET,
	//	OUT_DEFAULT_PRECIS, NULL, FF_DONTCARE, L"궁서체", &m_pFont);
	////=================================================================================

	//m_pWorldGrid = new cWorldGrid;
	//m_pWorldGrid->Init();

	//D3DXVECTOR3 temppos(40, 5, 20);


	//auto temp = DXUtil::Convert3DTo2D(temppos);
	//temppos.x = temp.x;
	//temppos.y = temp.y;
	//temppos.z = 0;

	//m_pCar = new cWorldMapCar;
	//m_pCar->Init();

	//m_pStage[0] = new cWorldStage; m_pStage[0]->setType(STAGE_WATER); 	 m_pStage[0]->SetNextPos(D3DXVECTOR3(40, 0, 20));	  m_pStage[0]->SetPosition(&D3DXVECTOR3(0, 0, 0));		 m_pStage[0]->setStageNum(DXUtil::MakePoint(1, 1)); m_pStage[0]->setCar(m_pCar);	m_pStage[0]->Init();
	//m_pStage[1] = new cWorldStage; m_pStage[1]->setType(STAGE_GRASS);														  m_pStage[1]->SetPosition(&D3DXVECTOR3(10, 0, 10));	 m_pStage[1]->setStageNum(DXUtil::MakePoint(1, 2)); m_pStage[1]->setCar(m_pCar);  m_pStage[1]->Init();
	//m_pStage[2] = new cWorldStage; m_pStage[2]->setType(STAGE_SAND);														  m_pStage[2]->SetPosition(&D3DXVECTOR3(20, 0, 20));	 m_pStage[2]->setStageNum(DXUtil::MakePoint(1, 3)); m_pStage[2]->setCar(m_pCar);	m_pStage[2]->Init();
	//m_pStage[3] = new cWorldStage; m_pStage[3]->setType(STAGE_WATER);														  m_pStage[3]->SetPosition(&D3DXVECTOR3(30, 0, 30));	 m_pStage[3]->setStageNum(DXUtil::MakePoint(1, 4)); m_pStage[3]->setCar(m_pCar);	m_pStage[3]->Init();
	//m_pStage[4] = new cWorldStage; m_pStage[4]->setType(STAGE_GRASS);														  m_pStage[4]->SetPosition(&D3DXVECTOR3(40, 0, 40));	 m_pStage[4]->setStageNum(DXUtil::MakePoint(2, 1)); m_pStage[4]->setCar(m_pCar);	m_pStage[4]->Init();
	//m_pStage[5] = new cWorldStage; m_pStage[5]->setType(STAGE_SAND);														  m_pStage[5]->SetPosition(&D3DXVECTOR3(-10, 0, -10));	 m_pStage[5]->setStageNum(DXUtil::MakePoint(2, 2)); m_pStage[5]->setCar(m_pCar);	m_pStage[5]->Init();
	//m_pStage[6] = new cWorldStage; m_pStage[6]->setType(STAGE_WATER);														  m_pStage[6]->SetPosition(&D3DXVECTOR3(-20, 0, -20));	 m_pStage[6]->setStageNum(DXUtil::MakePoint(2, 3)); m_pStage[6]->setCar(m_pCar);	m_pStage[6]->Init();
	//m_pStage[7] = new cWorldStage; m_pStage[7]->setType(STAGE_GRASS);														  m_pStage[7]->SetPosition(&D3DXVECTOR3(-30, 0, -30));	 m_pStage[7]->setStageNum(DXUtil::MakePoint(2, 3)); m_pStage[7]->setCar(m_pCar);	m_pStage[7]->Init();
	//m_pStage[8] = new cWorldStage; m_pStage[8]->setType(STAGE_SAND);														  m_pStage[8]->SetPosition(&D3DXVECTOR3(-40, 0, -40));	 m_pStage[8]->setStageNum(DXUtil::MakePoint(3, 1)); m_pStage[8]->setCar(m_pCar);	m_pStage[8]->Init();
	//m_pStage[9] = new cWorldStage; m_pStage[9]->setType(STAGE_GRASS);	 m_pStage[9]->SetPathType(PATH_CURVED);				  m_pStage[9]->SetPosition(&D3DXVECTOR3(10, 0, 30));	 m_pStage[9]->setStageNum(DXUtil::MakePoint(3, 2)); m_pStage[9]->setCar(m_pCar);  m_pStage[9]->Init();

	//m_UI = new SampleUI(); m_UI->SetPosition(&D3DXVECTOR3(0, 80, 0)); m_UI->Init();

	//m_pCloud[0] = new cWMCloud;  m_pCloud[0]->SetPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[0]->Init();
	//m_pCloud[1] = new cWMCloud;  m_pCloud[1]->SetPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[1]->Init();
	//m_pCloud[2] = new cWMCloud;  m_pCloud[2]->SetPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[2]->Init();
	//m_pCloud[3] = new cWMCloud;  m_pCloud[3]->SetPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[3]->Init();
	//m_pCloud[4] = new cWMCloud;  m_pCloud[4]->SetPosition(&D3DXVECTOR3(-rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[4]->Init();
	//m_pCloud[5] = new cWMCloud;  m_pCloud[5]->SetPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[5]->Init();
	//m_pCloud[6] = new cWMCloud;  m_pCloud[6]->SetPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, rand() % 600 / 10.0f)); m_pCloud[6]->Init();
	//m_pCloud[7] = new cWMCloud;  m_pCloud[7]->SetPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, -rand() % 600 / 10.0f)); m_pCloud[7]->Init();
	//m_pCloud[8] = new cWMCloud;  m_pCloud[8]->SetPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, -rand() % 600 / 10.0f)); m_pCloud[8]->Init();
	//m_pCloud[9] = new cWMCloud;  m_pCloud[9]->SetPosition(&D3DXVECTOR3(rand() % 600 / 10.0f, 0, -rand() % 600 / 10.0f)); m_pCloud[9]->Init();

	////=================================================================================
	//D3DXVECTOR3 dir(-1, -1, -1);
	//D3DXVec3Normalize(&dir, &dir);
	//D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	//g_pD3DDevice->SetLight(0, &light);
	//g_pD3DDevice->LightEnable(0, true);


}

void cWorldMapScene::Update()
{
	/*if (!_isChangeDone)
	{
		_alpha--;
		if (_alpha <= 0)
		{
			_alpha = 0;
			_isChangeDone = true;
		}
	}
	else
	{
		D3DXVECTOR3 camera = m_pCar->GetPosition();
		m_pCamera->Update(&camera);

		m_pWorldGrid->Update();

		m_pCar->Update();

		for (auto p : m_pStage)
		{
			if (p)
				p->Update();
		}

		for (int i = 0; i < 10; i++)
		{
			if (m_pStage[i]->getSphere()->getBS().isPicked)
			{
				m_pStage[i]->SetAnimation(true);
			}
		}

		m_UI->Update();

		for (auto p : m_pCloud)
		{
			p->Update();
			D3DXMATRIX mat = p->GetWorldMatrix()*m_matWorld;
			p->SetWorldMatrix(&mat);
		}
	}*/
}

DWORD FtoDw(float f) { return *((DWORD*)&f); }

void cWorldMapScene::Render()
{
	//===============================================================
	//g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, true);
	//g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, 0xffffffff);
	//g_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, FtoDw(0.1f));         // 안개의 강도
	//g_pD3DDevice->SetRenderState(D3DRS_FOGSTART, FtoDw(22.0f));         // 안개의 시작 위치
	//g_pD3DDevice->SetRenderState(D3DRS_FOGEND, FtoDw(50.0f));         // 안개 강도의 최대값 위치
	//g_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);      // 안개 중간 보간값

	//================================================FOG START=======
//	m_pWorldGrid->Render();
//
//	m_pCar->Render();
//
//	for (auto p : m_pCloud)
//	{
//		if (p) p->Render();
//	}
//
//	for (auto p : m_pStage)
//	{
//		if (p)
//			p->Render();
//	}
//
//	//===============================================FOG END=========
//	//g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, false);
//	//===============================================================
//
//	m_UI->Render();
//
//	if (!_isChangeDone)
//	{
//		IMAGEMANAGER->alphaRender(_T("blackMask"), _alpha);
//	}
}
