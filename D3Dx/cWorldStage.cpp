#include "stdafx.h"
#include "cWorldStage.h"

#include "cWMDefinition.h"

#include "cSphere.h"
#include "cWorldTile.h"
#include "cWMStarBoard.h"
#include "cWMStageNum.h"

#include "cPathMaker.h"

#include "cWorldMapCar.h"

cWorldStage::cWorldStage()
	:m_bAnimation(false)
	, m_NextPos(0, 0, 0)
	, m_Type(STAGE_GRASS)
	, m_pathType(PATH_CURVED)
{
	m_pCar = NULL;
	m_pSphere = NULL;

	for (auto p : m_pTile)
	{
		if (p) p = NULL;
	}

	//stage number initialize
	m_Stage.x = 1;
	m_Stage.y = 1;
}


cWorldStage::~cWorldStage()
{
}

void cWorldStage::Setup()
{
	//Sphere Setting
	m_pSphere = new cSphere; m_pSphere->SetCar(m_pCar); m_pSphere->setPosition(&D3DXVECTOR3(m_vPosition.x, 0, m_vPosition.z)); m_pSphere->Setup();

	//UI Setting
	m_pStarBoard = new cWMStarBoard;
	m_pStarBoard->SetAddressLinkWithSphere(m_pSphere);
	m_pStarBoard->setPosition(&D3DXVECTOR3(m_vPosition.x, 2, m_vPosition.z));
	m_pStarBoard->Setup();
	m_pStarBoard->setScore(m_nStar);

	//map Tile Setting
	if (m_Type == STAGE_GRASS)
	{
		m_pTile[0] = new cWorldTile; m_pTile[0]->SetType(TILE_GRASS);	 m_pTile[0]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[0]->Setup();
		m_pTile[1] = new cWorldTile; m_pTile[1]->SetType(TILE_GRASS);	 m_pTile[1]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[1]->Setup();
		m_pTile[2] = new cWorldTile; m_pTile[2]->SetType(TILE_GRASS);	 m_pTile[2]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[2]->Setup();
		m_pTile[3] = new cWorldTile; m_pTile[3]->SetType(TILE_GRASS);	 m_pTile[3]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[3]->Setup();
		m_pTile[4] = new cWorldTile; m_pTile[4]->SetType(TILE_GRASS);	 m_pTile[4]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[4]->Setup();
		m_pTile[5] = new cWorldTile; m_pTile[5]->SetType(TILE_GRASS);	 m_pTile[5]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[5]->Setup();
		m_pTile[6] = new cWorldTile; m_pTile[6]->SetType(TILE_GRASS);	 m_pTile[6]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[6]->Setup();
		m_pTile[7] = new cWorldTile; m_pTile[7]->SetType(TILE_GRASS);	 m_pTile[7]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[7]->Setup();
		m_pTile[8] = new cWorldTile; m_pTile[8]->SetType(TILE_GRASS);	 m_pTile[8]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[8]->Setup();
		m_pTile[9] = new cWorldTile; m_pTile[9]->SetType(TILE_GRASS);	 m_pTile[9]->setPosition(&D3DXVECTOR3(m_vPosition.x, 0, m_vPosition.z));	m_pTile[9]->Setup();
		m_pTile[10] = new cWorldTile; m_pTile[10]->SetType(TILE_GRASS);  m_pTile[10]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[10]->Setup();
		m_pTile[11] = new cWorldTile; m_pTile[11]->SetType(TILE_GRASS);  m_pTile[11]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[11]->Setup();
		m_pTile[12] = new cWorldTile; m_pTile[12]->SetType(TILE_GRASS);  m_pTile[12]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[12]->Setup();
		m_pTile[13] = new cWorldTile; m_pTile[13]->SetType(TILE_GRASS);  m_pTile[13]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[13]->Setup();
		m_pTile[14] = new cWorldTile; m_pTile[14]->SetType(TILE_GRASS);  m_pTile[14]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[14]->Setup();
		m_pTile[15] = new cWorldTile; m_pTile[15]->SetType(TILE_GRASS);  m_pTile[15]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[15]->Setup();
		m_pTile[16] = new cWorldTile; m_pTile[16]->SetType(TILE_GRASS);  m_pTile[16]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[16]->Setup();
		m_pTile[17] = new cWorldTile; m_pTile[17]->SetType(TILE_GRASS);  m_pTile[17]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[17]->Setup();
		m_pTile[18] = new cWorldTile; m_pTile[18]->SetType(TILE_GRASS);  m_pTile[18]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[18]->Setup();
		m_pTile[19] = new cWorldTile; m_pTile[19]->SetType(TILE_GRASS);  m_pTile[19]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[19]->Setup();
	}
	else if (m_Type == STAGE_WATER)
	{
		m_pTile[0] = new cWorldTile; m_pTile[0]->SetType(TILE_WATER);  m_pTile[0]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 20.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[0]->Setup();
		m_pTile[1] = new cWorldTile; m_pTile[1]->SetType(TILE_WATER);  m_pTile[1]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 20.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[1]->Setup();
		m_pTile[2] = new cWorldTile; m_pTile[2]->SetType(TILE_WATER);  m_pTile[2]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 20.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[2]->Setup();
		m_pTile[3] = new cWorldTile; m_pTile[3]->SetType(TILE_WATER);  m_pTile[3]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 20.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[3]->Setup();
		m_pTile[4] = new cWorldTile; m_pTile[4]->SetType(TILE_WATER);  m_pTile[4]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 20.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[4]->Setup();
		m_pTile[5] = new cWorldTile; m_pTile[5]->SetType(TILE_WATER);  m_pTile[5]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 20.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[5]->Setup();
		m_pTile[6] = new cWorldTile; m_pTile[6]->SetType(TILE_WATER);  m_pTile[6]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 20.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[6]->Setup();
		m_pTile[7] = new cWorldTile; m_pTile[7]->SetType(TILE_WATER);  m_pTile[7]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 20.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[7]->Setup();
		m_pTile[8] = new cWorldTile; m_pTile[8]->SetType(TILE_WATER);  m_pTile[8]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 20.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[8]->Setup();
		m_pTile[9] = new cWorldTile; m_pTile[9]->SetType(TILE_WATER);  m_pTile[9]->setPosition(&D3DXVECTOR3(m_vPosition.x, 0, m_vPosition.z));													m_pTile[9]->Setup();
		m_pTile[10] = new cWorldTile; m_pTile[10]->SetType(TILE_WATER);  m_pTile[10]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[10]->Setup();
		m_pTile[11] = new cWorldTile; m_pTile[11]->SetType(TILE_WATER);  m_pTile[11]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[11]->Setup();
		m_pTile[12] = new cWorldTile; m_pTile[12]->SetType(TILE_WATER);  m_pTile[12]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[12]->Setup();
		m_pTile[13] = new cWorldTile; m_pTile[13]->SetType(TILE_WATER);  m_pTile[13]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[13]->Setup();
		m_pTile[14] = new cWorldTile; m_pTile[14]->SetType(TILE_WATER);  m_pTile[14]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[14]->Setup();
		m_pTile[15] = new cWorldTile; m_pTile[15]->SetType(TILE_WATER);  m_pTile[15]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[15]->Setup();
		m_pTile[16] = new cWorldTile; m_pTile[16]->SetType(TILE_WATER);  m_pTile[16]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[16]->Setup();
		m_pTile[17] = new cWorldTile; m_pTile[17]->SetType(TILE_WATER);  m_pTile[17]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[17]->Setup();
		m_pTile[18] = new cWorldTile; m_pTile[18]->SetType(TILE_WATER);  m_pTile[18]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[18]->Setup();
		m_pTile[19] = new cWorldTile; m_pTile[19]->SetType(TILE_WATER);  m_pTile[19]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[19]->Setup();

	}
	else if (m_Type == STAGE_SAND)
	{
		m_pTile[0] = new cWorldTile; m_pTile[0]->SetType(TILE_SAND);  m_pTile[0]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f)); m_pTile[0]->Setup();
		m_pTile[1] = new cWorldTile; m_pTile[1]->SetType(TILE_SAND);  m_pTile[1]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f)); m_pTile[1]->Setup();
		m_pTile[2] = new cWorldTile; m_pTile[2]->SetType(TILE_SAND);  m_pTile[2]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f)); m_pTile[2]->Setup();
		m_pTile[3] = new cWorldTile; m_pTile[3]->SetType(TILE_SAND);  m_pTile[3]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f)); m_pTile[3]->Setup();
		m_pTile[4] = new cWorldTile; m_pTile[4]->SetType(TILE_SAND);  m_pTile[4]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f)); m_pTile[4]->Setup();
		m_pTile[5] = new cWorldTile; m_pTile[5]->SetType(TILE_SAND);  m_pTile[5]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f)); m_pTile[5]->Setup();
		m_pTile[6] = new cWorldTile; m_pTile[6]->SetType(TILE_SAND);  m_pTile[6]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f)); m_pTile[6]->Setup();
		m_pTile[7] = new cWorldTile; m_pTile[7]->SetType(TILE_SAND);  m_pTile[7]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f)); m_pTile[7]->Setup();
		m_pTile[8] = new cWorldTile; m_pTile[8]->SetType(TILE_SAND);  m_pTile[8]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f)); m_pTile[8]->Setup();
		m_pTile[9] = new cWorldTile; m_pTile[9]->SetType(TILE_SAND);  m_pTile[9]->setPosition(&D3DXVECTOR3(m_vPosition.x, 0, m_vPosition.z)); m_pTile[9]->Setup();
		m_pTile[10] = new cWorldTile; m_pTile[10]->SetType(TILE_SAND);  m_pTile[10]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[10]->Setup();
		m_pTile[11] = new cWorldTile; m_pTile[11]->SetType(TILE_SAND);  m_pTile[11]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[11]->Setup();
		m_pTile[12] = new cWorldTile; m_pTile[12]->SetType(TILE_SAND);  m_pTile[12]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[12]->Setup();
		m_pTile[13] = new cWorldTile; m_pTile[13]->SetType(TILE_SAND);  m_pTile[13]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[13]->Setup();
		m_pTile[14] = new cWorldTile; m_pTile[14]->SetType(TILE_SAND);  m_pTile[14]->setPosition(&D3DXVECTOR3(m_vPosition.x - rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[14]->Setup();
		m_pTile[15] = new cWorldTile; m_pTile[15]->SetType(TILE_SAND);  m_pTile[15]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[15]->Setup();
		m_pTile[16] = new cWorldTile; m_pTile[16]->SetType(TILE_SAND);  m_pTile[16]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[16]->Setup();
		m_pTile[17] = new cWorldTile; m_pTile[17]->SetType(TILE_SAND);  m_pTile[17]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[17]->Setup();
		m_pTile[18] = new cWorldTile; m_pTile[18]->SetType(TILE_SAND);  m_pTile[18]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z + rand() % 100 / 20.0f));	m_pTile[18]->Setup();
		m_pTile[19] = new cWorldTile; m_pTile[19]->SetType(TILE_SAND);  m_pTile[19]->setPosition(&D3DXVECTOR3(m_vPosition.x + rand() % 100 / 10.0f, 0, m_vPosition.z - rand() % 100 / 20.0f));	m_pTile[19]->Setup();

	}

	//Path Setting
	cPathMaker maker;
	maker.CreatePath(m_pathType, m_vPosition, m_NextPos, m_vecPath);

	//Stage Number Setting
	m_pStageNum[0] = new cWMStageNum; m_pStageNum[0]->SetType(m_Stage.x); m_pStageNum[0]->setPosition(&D3DXVECTOR3(m_vPosition.x - 1, 0.3, m_vPosition.z - 2)); m_pStageNum[0]->Setup();
	m_pStageNum[1] = new cWMStageNum; m_pStageNum[1]->SetType(7);		  m_pStageNum[1]->setPosition(&D3DXVECTOR3(m_vPosition.x, 0.3, m_vPosition.z - 2));   m_pStageNum[1]->Setup();
	m_pStageNum[2] = new cWMStageNum; m_pStageNum[2]->SetType(m_Stage.y); m_pStageNum[2]->setPosition(&D3DXVECTOR3(m_vPosition.x + 1, 0.3, m_vPosition.z - 2)); m_pStageNum[2]->Setup();

}

void cWorldStage::Update()
{
	if (m_pSphere)
		m_pSphere->Update();

	for (auto p : m_pTile)
	{
		if (p)
			p->Update();
	}

	//Tile 에니메이션 순차 효과 적용 함수
	this->AnimationStart(m_bAnimation);

	for (auto p : m_vecPath)
	{
		if (p)
			p->Update();

		if (m_bAnimation)
		{
			if (p)
				p->SetAnimation(true);
		}

	}

	for (auto p : m_pStageNum)
	{
		if (p)
			p->Update();
	}

	if (m_pStarBoard)
		m_pStarBoard->Update();
	m_pStarBoard->setScore(m_nStar);
}

void cWorldStage::Render()
{
	if (m_pSphere)
		m_pSphere->Render();

	if (m_bAnimation)
	{
		for (auto p : m_pTile)
		{
			if (p)
				p->Render();
		}

		for (auto p : m_vecPath)
		{
			if (p) p->Render();
		}

	}

	if (m_pStarBoard)
		m_pStarBoard->Render();

	for (auto p : m_pStageNum)
	{
		if (p) p->Render();
	}
}

void cWorldStage::Release()
{
	SAFE_RELEASE(m_pCar);
	SAFE_RELEASE(m_pSphere);

	for (auto p : m_pTile)
	{
		SAFE_RELEASE(p);
	}

	for (auto p : m_vecPath)
	{
		SAFE_RELEASE(p);
	}

	for (auto p : m_pStageNum)
	{
		SAFE_RELEASE(p);
	}

	SAFE_RELEASE(m_pStarBoard);
}

void cWorldStage::AnimationStart(bool ani)
{
	for (int i = 0; i<20; i++)
	{
		m_pTile[i]->SetAnimation(ani, i);
	}
}
