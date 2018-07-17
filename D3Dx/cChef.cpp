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
	, m_pIven(NULL)
	, m_pDetect(NULL)
	, m_fRadius(0.5f)
{
}


cChef::~cChef()
{
	std::list<cChefRunPuff*>::iterator iter;
	for (iter = m_listPuff.begin(); iter != m_listPuff.end(); iter++)
	{
		(*iter)->~cChefRunPuff();
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
	
	//if (m_pDetect)
	//{
	//	m_pDetect->SetInteraction(true);
	//	m_pDetect->Setplayer(this);
	//
	//}
	Animation(m_pRoot);

	if (m_pRoot)
		m_pRoot->Update();

	runPuffCreate();
	if (m_listPuff.size()>0)
		runPuffUpdate();

}

void cChef::Render()
{

	g_pD3DDevice->SetMaterial(&m_stMtl);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	for (auto p : m_listPuff)
	{
		if (p->Getscale() > 0)
			p->Render();
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

cIGObj * cChef::GetcIGObject()
{
	return nullptr;
}

void cChef::runPuffCreate()
{
	if (m_pRoot->GetCHEF_STATE() == CHEF_STATE_MOVE)
	{
		cChefRunPuff * _runPuff = new cChefRunPuff;
		_runPuff->SetUp(m_vPosition);
		m_listPuff.insert(m_listPuff.begin(), _runPuff);
	}
	else if (m_pRoot->GetCHEF_STATE() == CHEF_STATE_BOOSTER_MOVE)
	{
	}
}

void cChef::runPuffUpdate()
{
	std::list<cChefRunPuff *>::iterator iter;
	for (auto p : m_listPuff)
	{
		if (m_pRoot->GetCHEF_STATE() == CHEF_STATE_MOVE)
			p->Update();
		else if (m_pRoot->GetCHEF_STATE() == CHEF_STATE_BOOSTER_MOVE)
		{
			for (int i = 0; i < 6; i++)
			{
				p->BoomMod();
			}
		}
	}
	if (m_listPuff.size() > 0)
	{
		for (iter = m_listPuff.begin(); iter != m_listPuff.end(); iter++)
		{
			if ((*iter)->Getscale() >= 0)
				(*iter)->Getscale()--;
		}
	}
}

void cChef::runPuffDelete(IN std::list<cChefRunPuff*>::iterator cChefIter)
{
	m_listPuff.erase(cChefIter);
}

void cChef::OnAction(cIGObj * pSender)
{

}
