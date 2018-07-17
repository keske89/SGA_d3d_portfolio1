#include "stdafx.h"
#include "cPassScroll.h"


cPassScroll::cPassScroll()
{
}


cPassScroll::~cPassScroll()
{
}

void cPassScroll::Setup()
{
}

void cPassScroll::Update()
{
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;
}

void cPassScroll::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}

void cPassScroll::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXMATRIX matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 0.9f, 1.0f, 0.6f);
	m_matLocal = matS;
	m_eState = OBJ_STATIC;
	m_nObjectType = lidtype;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"ThePass_FatScrolling.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/ThePass_Scrolling.png");
}

void cPassScroll::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}
