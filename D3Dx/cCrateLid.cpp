#include "stdafx.h"
#include "cCrateLid.h"


cCrateLid::cCrateLid()
{
}


cCrateLid::~cCrateLid()
{
}

void cCrateLid::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	// 0 양파
	// 1 토마토
	// 2 버섯
	// 3 감자
	
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, -1.2f, 0);
	m_matWorld = matT * matWorld;
	m_vPos = pos;


	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"CrateLid_mesh.obj");
	switch (lidtype)
	{
	case 0:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Onion_Texture.png");
		break;

	case 1:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Tomato_Texture.png");
		break;

	case 2:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Mushroom_Texture.png");
		break;

	case 3:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Potato_Texture.png");
		break;

	default:
		break;
	}
	
	
}

void cCrateLid::SetWorldMat(D3DXMATRIX matWorld)
{
}

void cCrateLid::Setup()
{
}

void cCrateLid::Update()
{
}


void cCrateLid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}
