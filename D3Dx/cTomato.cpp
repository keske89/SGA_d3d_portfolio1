#include "stdafx.h"
#include "cTomato.h"


cTomato::cTomato()
{
}


cTomato::~cTomato()
{
}

void cTomato::Setup()
{
	

}

void cTomato::Update()
{
	
}

void cTomato::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}

void cTomato::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{

	m_vPos = pos;
	m_matWorld = matWorld;
	m_pMesh = ObJMANAGER->GetMesh(L"Tomato_Whole.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Tomato.png");
}

void cTomato::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
}
