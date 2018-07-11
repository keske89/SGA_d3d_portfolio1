#include "stdafx.h"
#include "cIGObj.h"


cIGObj::cIGObj()
	: m_bInteraction(false)
	, m_pMesh(NULL)
	, m_pTexture(NULL)
	, m_vPos(0.0f, 0.0f, 0.0f)
	, m_pDelegate(NULL)
{	
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);
}


cIGObj::~cIGObj()
{
	SAFE_RELEASE(m_pDelegate);
}

void cIGObj::Update()
{
}

void cIGObj::Render()
{
}

