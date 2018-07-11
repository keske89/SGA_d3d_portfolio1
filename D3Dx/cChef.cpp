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
{
}


cChef::~cChef()
{
	if (m_pRoot)
		m_pRoot->Destroy();
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

void cChef::Update()
{
	m_pControl->Control();
	Animation(m_pRoot);
	if (m_pRoot)
		m_pRoot->Update();
}

void cChef::Render()
{

	g_pD3DDevice->SetMaterial(&m_stMtl);
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
