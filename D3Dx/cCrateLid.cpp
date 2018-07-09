#include "stdafx.h"
#include "cCrateLid.h"


cCrateLid::cCrateLid()
{
}


cCrateLid::~cCrateLid()
{
}

void cCrateLid::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos)
{
	
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, -1.2f, 0);
	m_matWorld = matT * matWorld;
	m_vPos = pos;


	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"CrateLid_mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/CrateLid.png");
	
}

void cCrateLid::Setup()
{
}

void cCrateLid::Update()
{
}


void cCrateLid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}
