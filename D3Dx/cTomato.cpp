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
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;
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

	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matWorld;
	m_eState = OBJ_DYNAMIC;
	m_pMesh = ObJMANAGER->GetMesh(L"Tomato_Whole.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Tomato.png");
}

void cTomato::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}
