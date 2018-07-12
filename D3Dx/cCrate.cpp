#include "stdafx.h"
#include "cCrate.h"
#include "cCrateLid.h"

cCrate::cCrate()
{
}

cCrate::~cCrate()
{
}

void cCrate::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int objectType)
{
	D3DXVECTOR3 trans(0, 0.5f, 0);
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	m_matLocal = matT;

	m_matWorld = matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Crate_mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Crate.png");

	m_nObjectType = objectType;

}

void cCrate::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
}


void cCrate::Setup()
{


}

void cCrate::Update()
{	
}

void cCrate::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}
