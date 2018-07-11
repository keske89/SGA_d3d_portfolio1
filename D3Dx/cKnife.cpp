#include "stdafx.h"
#include "cKnife.h"


cKnife::cKnife()
{

}


cKnife::~cKnife()
{
	
}

void cKnife::Setup()
{
	
}

void cKnife::Update()
{
	
	
}

void cKnife::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);

}

void cKnife::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	m_matWorld = m_matLocal * matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Knife.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Knife.png");
}

void cKnife::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = m_matLocal * matWorld;
}


