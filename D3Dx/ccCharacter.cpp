#include "stdafx.h"
#include "cCharacter.h"
#include "cChefRoot.h"
#include "cCharacterControl.h"
// parts
#include"cChefBody.h"
#include"cChefHead.h"
#include"cChefLeftHand.h"
#include"cChefRightHand.h"


cCharacter::cCharacter()
	: m_pRoot(NULL)
	, m_vPosition(0, 0, 0)
	, m_eChefState(CHEF_STATE_IDLE)
	, m_pObjRoot(NULL)
{
}


cCharacter::~cCharacter()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cCharacter::SetUp(D3DXVECTOR3 vPos, cCharacterControl * _pControl)
{
	m_pControl = _pControl;
	m_vPosition = vPos;
	SetMaterial();
	cChefBody* pBody = new cChefBody;
	pBody->SetUp();
	m_pRoot = pBody;
	cChefHead* pHead = new cChefHead;
	pHead->SetUp();
	pHead->SetRotDeltaY(0.05f);
	pHead->SetRotDeltaX(0.01f);
	m_pRoot->AddChild(pHead);
	cChefLeftHand * pLHand = new cChefLeftHand;
	pLHand->SetUp();
	pLHand->SetRotDeltaX(0.05f);
	m_pRoot->AddChild(pLHand);
	cChefRightHand* pRHand = new cChefRightHand;
	pRHand->SetUp();
	pRHand->SetRotDeltaX(0.05f);
	m_pRoot->AddChild(pRHand);

}

void cCharacter::Update()
{
	m_pControl->Control();
	if (m_pRoot)
		m_pRoot->Update();
}

void cCharacter::Render()
{

	g_pD3DDevice->SetMaterial(&m_stMtl);
	if (m_pRoot)
		m_pRoot->Render();

}

void cCharacter::SetMaterial()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
}

cIGObj * cCharacter::GetcIGObject()
{
	return nullptr;
}

void cCharacter::SetcIGObject(cIGObj * _object)
{
}
