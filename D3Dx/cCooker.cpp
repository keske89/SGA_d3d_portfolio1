#include "stdafx.h"
#include "cCooker.h"


cCooker::cCooker()
{
}


cCooker::~cCooker()
{
}

void cCooker::Setup()
{
	
	

}

void cCooker::Update()
{
}

void cCooker::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}

void cCooker::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	m_vPos = pos;
	m_matWorld = matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Cooker.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Cooker_Texture.png");
}

void cCooker::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = m_matLocal * matWorld;
}
