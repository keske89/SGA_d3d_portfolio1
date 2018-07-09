#include "stdafx.h"
#include "cCrate.h"
#include "cCrateLid.h"

cCrate::cCrate()
	:m_CrateLid(NULL)
{
}


cCrate::~cCrate()
{
}

void cCrate::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos)
{
	m_CrateLid = new cCrateLid;
	m_CrateLid->Setup(m_matWorld, m_vPos);

	D3DXMATRIX matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 1.0f, 2.5f, 1.0f);

	m_matLocal = matS;

	m_matWorld = matS * matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Crate_mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Crate.png");
}


void cCrate::Setup()
{
	
	
}

void cCrate::Update()
{
	if (m_CrateLid)
		m_CrateLid->Update();
}

void cCrate::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);

	if (m_CrateLid)
		m_CrateLid->Render();
}
