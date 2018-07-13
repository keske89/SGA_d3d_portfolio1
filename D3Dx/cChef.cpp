#include "stdafx.h"
#include "cChef.h"
#include "cChefRoot.h"
#include "cCharacterControl.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
// parts
#include"cChefBody.h"
#include"cChefHead.h"
#include"cChefLeftHand.h"
#include"cChefRightHand.h"
#include "cChefKnife.h"

cChef::cChef()
	: m_pRoot(NULL)
	, m_vPosition(0, 0, 0)
	, m_pObjRoot(NULL)
	, m_fRadius(0.5f)
{
}


cChef::~cChef()
{
	
}

void cChef::SetUp(D3DXVECTOR3 vPos, cCharacterControl * _pControl)
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

}

void cChef::Relese()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cChef::Update()
{
	m_pControl->Control();
	Animation(m_pRoot);

	if (m_pRoot)
		m_pRoot->Update();

	runPuffCreate();
	/*for (auto p : m_vecPuff)
	{
		p->Update();
	}
	for (auto p : m_vecPuff)
	{
		if (p->Getscale() < 0)
			p = NULL;
		else if (p->Getscale() > 0)
			p->Getscale()--;
		if (p == NULL)
			m_vecPuff.remove(p);
	}*/

}

void cChef::Render()
{

	g_pD3DDevice->SetMaterial(&m_stMtl);
	//for (auto p : m_vecPuff)
	//{
	//	p->Render();
	//}

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
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

void cChef::SetcIGObject(cIGObj * _object)
{
}

void cChef::runPuffCreate()
{
	/*if (m_pRoot->GetCHEF_STATE() == CHEF_STATE_MOVE)
	{
		cChefRunPuff * _runPuff = new cChefRunPuff;
		_runPuff->SetUp(m_vPosition);
		m_vecPuff.insert(m_vecPuff.begin(), _runPuff);
	}*/
}

void cChef::OnAction(cIGObj * pSender)
{
}
