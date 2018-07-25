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

	m_player = NULL;
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	Inventory();
}

void cSink::Render()
{
	SetLight();
	g_pD3DDevice->SetMaterial(&m_stMtl);
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
	m_eState = OBJ_STATIC;
	D3DXMATRIX matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 0.8f, 1.0f, 1.0f);
	m_matLocal = matS;
	m_matWorld =  matWorld;
	m_nObjectType = lidtype;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Sink1.obj");
	m_pMesh2 = ObJMANAGER->GetMesh(L"Sink_Counter.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Sink_Counter_Texture.png");
	m_pTexture2 = g_pTextureManager->GetTexture(L"Resources/Texture2D/Sink_Texture.png");
}

void cSink::SetLight()
{
	if (m_player) // 플레이어 연결됐음
	{
		ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
		m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stMtl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	}
	else
	{
		ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
		m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
}

void cSink::Inventory()
{
	if (m_Inven != NULL)
	{
		D3DXMATRIX matT, RotX;
		D3DXVECTOR3 v(1, 0, 0);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixRotationAxis(&RotX,&v, D3DX_PI / 2);
		D3DXMatrixTranslation(&matT, 0, 0, 0);

		m_Inven->SetWorldMatrix(RotX * matT * m_matLocal * m_matWorld);
	}
}
