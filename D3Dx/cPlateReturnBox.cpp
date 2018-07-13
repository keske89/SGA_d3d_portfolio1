#include "stdafx.h"
#include "cPlateReturnBox.h"


cPlateReturnBox::cPlateReturnBox()
{
}


cPlateReturnBox::~cPlateReturnBox()
{
}

void cPlateReturnBox::Setup()
{
}

void cPlateReturnBox::Update()
{
}

void cPlateReturnBox::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}

void cPlateReturnBox::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXVECTOR3 trans(0, -0.5f, 0);
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	m_matLocal = matT;
	m_vPos = pos;

	m_matWorld = matWorld;

	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"PlateReturnBox.obj");
	// ¶Ñ°Ï ¾Æ·¡ÂÊ ÀÌ¹ÌÁö
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Plate_Return.png");
}

void cPlateReturnBox::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
}
