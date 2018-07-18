#include "stdafx.h"
#include "cChef.h"
#include "cChefRoot.h"
#include "cCharacterControl.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
#include "cCollision.h"
// parts
#include"cChefBody.h"
#include"cChefHead.h"
#include"cChefLeftHand.h"
#include"cChefRightHand.h"
#include "cChefKnife.h"

cChef::cChef()
	: m_pRoot(NULL)
	, m_vPosition(0, 0, 0)
	, m_vdir(0, 0, 0)
	, m_vToGo(0, 0, 0)
	, m_pInven(NULL)
	, m_pDetect(NULL)
	, m_fRadius(0.5f)
{
}


cChef::~cChef()
{
	for (m_vecItPuff = m_vecPuff.begin(); m_vecItPuff != m_vecPuff.end();)
	{
		if ((*m_vecItPuff)->Getscale() < 0)
			m_vecItPuff = m_vecPuff.erase(m_vecItPuff);
	}
}

void cChef::SetUp(IN D3DXVECTOR3 vPos, cCharacterControl * _pControl)
{
	m_pControl = _pControl;
	m_vPosition = vPos;
	SetMaterial();
	cChefBody* pBody = new cChefBody;
	pBody->SetUp();
	m_pRoot = pBody;
	cChefHead* pHead = new cChefHead;
	pHead->SetUp();
	m_pRoot->AddChild(pHead);
	cChefLeftHand * pLHand = new cChefLeftHand;
	pLHand->SetUp();
	m_pRoot->AddChild(pLHand);
	cChefRightHand* pRHand = new cChefRightHand;
	pRHand->SetUp();
	m_pRoot->AddChild(pRHand);
	cChefKnife * pKnife = new cChefKnife;
	pKnife->SetUp();
	m_pRoot->AddChild(pKnife);
	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y, vPos.z);
	m_pRoot->SetParentWorldTM(&matT);

}

void cChef::Relese()
{
}

void cChef::Update()
{

	if (m_pControl)
		m_pControl->Control(this);
	runPuffCreate();
	if (m_pInven)
	{
		D3DXVECTOR3 vtemp = m_vPosition + (m_vdir*0.5f);
		D3DXMATRIX matT, mat;
		mat = m_pRoot->GetmatLocal();
		D3DXMatrixTranslation(&matT, vtemp.x, vtemp.y, vtemp.z);
		mat *= matT;
		m_pInven->SetWorldMatrix(mat);
	}

	Animation(m_pRoot);

	if (m_pRoot)
		m_pRoot->Update();

	for (int i = 0; i < m_vecPuff.size(); i++)
	{
		if (m_pRoot->GetCHEF_STATE() == CHEF_STATE_BOOSTER_MOVE)
			m_vecPuff[i]->BoomMod(m_vdir);
		else
			m_vecPuff[i]->Update();
	}

}

void cChef::Render()
{

	g_pD3DDevice->SetMaterial(&m_stMtl);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	for (int i = 0; i < m_vecPuff.size(); i++)
	{
		m_vecPuff[i]->Render();
	}
	if (m_pRoot)
		m_pRoot->Render();
}

void cChef::SetMaterial()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
}


void cChef::runPuffCreate()
{
	if (m_pRoot->GetCHEF_STATE() == CHEF_STATE_MOVE || m_pRoot->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
	{
		cChefRunPuff * _runPuff = new cChefRunPuff;
		_runPuff->SetUp(D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 0.3f, m_vPosition.z));
		m_vecPuff.push_back(_runPuff);
	}
	else if (m_pRoot->GetCHEF_STATE() == CHEF_STATE_BOOSTER_MOVE)
	{
		for (int i = 0; i < 10; i++)
		{
			cChefRunPuff * _runPuff = new cChefRunPuff;
			_runPuff->SetUp(m_pControl->GetAtribute(this)->st_vBooster);
			m_vecPuff.push_back(_runPuff);
		}
	}
}



void cChef::runPuffDelete(IN int num)
{
	m_vecPuff.at(num)->~cChefRunPuff();
	m_vecPuff.erase(m_vecPuff.begin() + num);
}

void cChef::OnAction(cIGObj * pSender)
{

}
