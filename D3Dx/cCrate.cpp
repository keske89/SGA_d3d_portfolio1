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

void cCrate::Setup()
{
	m_bInteraction = false;
	m_bIsUse = false;
	//m_matWorld
	m_pMesh = ObJMANAGER->GetMesh(L"Crate_mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Crate.png");

	m_CrateLid = new cCrateLid;
	m_CrateLid->Setup();

	D3DXVECTOR3 temp;
	temp = m_vPos;
	temp.y += 3.0f;
	m_CrateLid->SetPos(temp);

	
}

void cCrate::Update()
{
	
	D3DXMATRIX matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 1.0f, 3.0f, 1.0f);
	
	m_matLocal = matS;


	m_matWorld = m_matLocal* m_matWorld;

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
