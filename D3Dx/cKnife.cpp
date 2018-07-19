#include "stdafx.h"
#include "cKnife.h"


cKnife::cKnife()
{

}


cKnife::~cKnife()
{
}

void cKnife::Setup()
{
	
}

void cKnife::Update()
{
	m_player = NULL;
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;
}

void cKnife::Render()
{
	SetLight();
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);

}

void cKnife::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXVECTOR3 vY(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vX(0.0f, 0.0f, 1.0f);
	D3DXMATRIX matS, rotX, rotY, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&rotX);
	D3DXMatrixIdentity(&rotY);

	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&matT, -0.3f, -0.28f, 0.3f);
	D3DXMatrixRotationAxis(&rotX, &vX, -D3DX_PI / 2);
	D3DXMatrixRotationAxis(&rotY, &vY, D3DX_PI / 2);

	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matLocal = matS * rotX * rotY * matT;
	m_matWorld = matWorld;
	m_eState = OBJ_STATIC;
	m_nObjectType = lidtype;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Knife.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Knife.png");
}

void cKnife::SetLight()
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

void cKnife::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;

}


