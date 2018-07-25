#include "stdafx.h"
#include "cOnion.h"


cOnion::cOnion()
{
}


cOnion::~cOnion()
{
	SAFE_RELEASE(m_pSprite);
}

void cOnion::Setup()
{
}

void cOnion::Update()
{
	m_player = NULL;
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

}

void cOnion::Render()
{
	SetLight();
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);


	
}

void cOnion::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matWorld;
	m_eState = OBJ_DYNAMIC;
	m_nObjectType = lidtype;
	m_pMesh = ObJMANAGER->GetMesh(L"Onion_Whole.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Onion.png");
	//m_pSprite = g_pTextureManager->GetTexture(L"Resources/Texture2D/Onion_Icon");
	m_Cost = 100;
	m_Icon = new UIObject;
	m_Icon->SetPosition(m_vPos);
	m_Icon->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_OnionHouse_Background_Small.png")));

}

void cOnion::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}

void cOnion::SetLight()
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

D3DXVECTOR2 cOnion::Convert3DTo2D()
{
	D3DXMATRIX Own, proj, view, world;
	D3DVIEWPORT9 vp;
	Own = m_matLocal * m_matWorld;
	D3DXVECTOR3 v = D3DXVECTOR3(Own._41, Own._42, Own._43);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &proj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);
	g_pD3DDevice->GetViewport(&vp);
	D3DXMatrixIdentity(&world);
	D3DXVec3Project(&v, &v, &vp, &proj, &view, &world);
	return D3DXVECTOR2(v.x, v.y);

}
