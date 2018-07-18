#include "stdafx.h"
#include "cCounterTop.h"
#include "cPlate.h"
#include "cChoppingBoard.h"

cCounterTop::cCounterTop()
{
}


cCounterTop::~cCounterTop()
{
}

void cCounterTop::Setup()
{
}

void cCounterTop::Update()
{
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	Inventory();
}

void cCounterTop::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}

void cCounterTop::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int objectType)
{
	
	D3DXMATRIX matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 0.9f, 1.0f, 0.9f);
	m_matLocal = matS;
	m_eState = OBJ_STATIC;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matWorld;
	m_pMesh = ObJMANAGER->GetMesh(L"CounterTop_Isolated.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Counter_Texture.png");
}

void cCounterTop::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}

void cCounterTop::Inventory()
{
	if (m_Inven != NULL)
	{
		D3DXMATRIX matT;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, 0, 0.45f, 0);

		m_Inven->SetWorldMatrix(matT * m_matLocal * m_matWorld);
	}
}