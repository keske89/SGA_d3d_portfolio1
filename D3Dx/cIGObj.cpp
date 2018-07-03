#include "stdafx.h"
#include "cIGObj.h"


cIGObj::cIGObj()
	:m_bInteraction(false)
	,m_pMesh(NULL)
	,m_pTexture(NULL)
	,m_vPos(0.0f, 0.0f, 0.0f)
{
	D3DXMatrixIdentity(&m_mMat);
}


cIGObj::~cIGObj()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture);
}

void cIGObj::Setup()
{
	//g_pFontManager->GetFont(cFontManager::FT_DEFAULT);
}

void cIGObj::Update()
{
}

void cIGObj::Render()
{
}
