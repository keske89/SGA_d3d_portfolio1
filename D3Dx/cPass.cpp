#include "stdafx.h"
#include "cPass.h"
#include "cPassScroll.h"


cPass::cPass()
{
}


cPass::~cPass()
{
}

void cPass::Setup()
{
}

void cPass::Update()
{
}

void cPass::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}

void cPass::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	m_matWorld = m_matLocal * matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"ThePass.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/ThePass.png");

	m_PassScroll = new cPassScroll;
	m_PassScroll->Setup(matWorld, pos, lidtype);
}

void cPass::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = m_matLocal * matWorld;
}
