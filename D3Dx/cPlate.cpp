#include "stdafx.h"
#include "cPlate.h"


cPlate::cPlate()
{
}


cPlate::~cPlate()
{
}

void cPlate::Setup()
{
}

void cPlate::Update()
{
}

void cPlate::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}

void cPlate::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	m_matWorld = m_matLocal * matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Plate.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Plate_Texture.png");
}

void cPlate::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = m_matLocal * matWorld;
}
