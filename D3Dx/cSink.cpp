#include "stdafx.h"
#include "cSink.h"


cSink::cSink()
{
}


cSink::~cSink()
{
}

void cSink::Setup()
{
	
	
}

void cSink::Update()
{
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;
}

void cSink::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture2);
	m_pMesh->DrawSubset(1);
}

void cSink::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;

}

void cSink::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Sink1.obj");
	m_pMesh2 = ObJMANAGER->GetMesh(L"Sink_Counter.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Sink_Counter_Texture.png");
	m_pTexture2 = g_pTextureManager->GetTexture(L"Resources/Texture2D/Sink_Texture.png");
}
