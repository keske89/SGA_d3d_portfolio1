#include "stdafx.h"
#include "cCrate.h"


cCrate::cCrate()
{
}


cCrate::~cCrate()
{
}

void cCrate::Setup()
{
	m_bInteraction = false;
	m_bIsUse = false;
	//m_matWorld
	m_pMesh = ObJMANAGER->GetMesh(L"Crate_mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Crate.png");
	
}

void cCrate::Update()
{
	
	m_matLocal = m_matS * m_matR * m_matT;


	m_matWorld = m_matLocal* m_matWorld;
}

void cCrate::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}
