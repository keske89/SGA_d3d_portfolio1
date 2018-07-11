#include "stdafx.h"
#include "cCrate.h"
#include "cCrateLid.h"

cCrate::cCrate()
	: m_CrateLid(NULL)
{
}

cCrate::~cCrate()
{
}

void cCrate::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	
	
	D3DXMATRIX matS, matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0.0f, 0.5f, 0.0f);
	
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 1.0f, 2.5f, 1.0f);
	
	m_matLocal = matT * matS;
	
	m_matWorld = m_matLocal * matWorld;

	
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Crate_mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Crate.png");


	m_CrateLid = new cCrateLid;
	m_LidType = (LIDTYPE)lidtype;
	m_CrateLid->Setup(matWorld, pos + D3DXVECTOR3(0, 0.07f, 0), lidtype);
}

void cCrate::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = m_matLocal * matWorld;
	m_CrateLid->SetMatWorld(matWorld);

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
