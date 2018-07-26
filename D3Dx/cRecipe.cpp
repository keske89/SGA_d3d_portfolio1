#include "stdafx.h"
#include "cRecipe.h"



cRecipe::cRecipe()
{
}


cRecipe::~cRecipe()
{
}

void cRecipe::Setup()
{
}


void cRecipe::Setup(D3DXMATRIX matWorld, int type)
{
	m_Type = type;
	m_Cost = type;
	m_matWorld = matWorld;

	m_pMesh = ObJMANAGER->GetMesh(L"Recipe.obj");
	switch (type)
	{
	case 300: // 양파
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Onion_Soup.png");
		break;

	case 3000:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Tomato_Soup.png");
		break; // 토마토
	default:
		break;
	}

}

void cRecipe::Update()
{
	if (!m_Inven)
	{
		m_Cost = 0;
	}
}

void cRecipe::Render()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);
}

void cRecipe::Destroy()
{
}


