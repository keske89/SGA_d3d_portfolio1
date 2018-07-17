#include "stdafx.h"
#include "cChoppingBoard.h"


cChoppingBoard::cChoppingBoard()
{
}


cChoppingBoard::~cChoppingBoard()
{
}

void cChoppingBoard::Setup()
{
}

void cChoppingBoard::Update()
{
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;
}

void cChoppingBoard::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal *m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}

void cChoppingBoard::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXMATRIX matR;
	D3DXVECTOR3 v(1.0f, 0, 0);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationAxis(&matR, &v, (float)3.14 * 0.5f);

	m_eState = OBJ_STATIC;
	m_nObjectType = lidtype;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matR * matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Chopping_Board.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/ChoppingBoard.png");
}

void cChoppingBoard::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld =  matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}
