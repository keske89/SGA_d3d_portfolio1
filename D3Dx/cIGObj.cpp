#include "stdafx.h"
#include "cIGObj.h"


cIGObj::cIGObj()
	: m_bInteraction(false)
	, m_pSprite(NULL)
	, m_pIcon(NULL)
	, m_pTexture(NULL)
	, m_pMesh(NULL)
	, m_vPos(0.0f, 0.0f, 0.0f)
	, m_Inven(NULL)
	, m_pChild(NULL)
	, m_bIsEquipped(false)
	, m_IsSet(false)
	, m_vecRoll(0, 0, 0)
	
{	
	m_parent = NULL;
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRoll);
	
}


cIGObj::~cIGObj()
{
	
	//SAFE_RELEASE(m_pDelegate);
}


void cIGObj::AddChild(cIGObj * childNode)
{
	m_pChild = childNode;
}

void cIGObj::SetWorldMatrix(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;

	if (m_pChild)
		m_pChild->SetWorldMatrix(matWorld);
}

void cIGObj::Destroy(cIGObj * pSender)
{
	SAFE_DELETE(pSender);
}

