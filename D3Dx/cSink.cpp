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
}

void cSink::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	g_pD3DDevice->SetTexture(0, m_pTexture2);
	m_pMesh->DrawSubset(1);

	/*g_pD3DDevice->SetTexture(0, m_pTexture2);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh2->DrawSubset(0);*/

}

void cSink::SetWorldMat(D3DXMATRIX matWorld)
{
}

void cSink::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	m_vPos = pos;
	m_matWorld = matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Sink1.obj");
	m_pMesh2 = ObJMANAGER->GetMesh(L"Sink_Counter.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Sink_Counter_Texture.png");
	m_pTexture2 = g_pTextureManager->GetTexture(L"Resources/Texture2D/Sink_Texture.png");
}
