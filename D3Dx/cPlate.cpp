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
	m_player = NULL;
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	Inventory();
}

void cPlate::Render()
{
	if(m_bIsUse) m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/DirtyPlate.png");
	if (!m_bIsUse) m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Plate_Texture.png");
	SetLight();
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}

void cPlate::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 0.05f, 0);
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matLocal = matT;
	m_matWorld = matWorld;
	m_eState = OBJ_DYNAMIC;
	m_nObjectType = lidtype;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Plate.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Plate_Texture.png");
	
}

void cPlate::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = m_matLocal * matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}

void cPlate::SetLight()
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

void cPlate::Inventory()
{
	if (m_Inven != NULL)
	{
		D3DXMATRIX matT;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		m_Cost = m_Inven->GetCost();
		m_Inven->SetWorldMatrix(matT * m_matLocal * m_matWorld);
	}
}
