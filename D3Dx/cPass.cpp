#include "stdafx.h"
#include "cPass.h"
#include "cPassScroll.h"
#include "cStageObjManager.h"
#include "cOrder.h"
#include "cPot.h"

class cPlate;

cPass::cPass()
	:m_Pot(NULL)
{
	m_vec.clear();
}


cPass::~cPass()
{
}

void cPass::Setup()
{
}

void cPass::Update()
{
	m_player = NULL;
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	m_vec = m_SOM->GetvecOrder();
	Inventory();
}

void cPass::Render()
{
	SetLight();
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);

	if (m_PassScroll)
		m_PassScroll->Render();
}

void cPass::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXMATRIX matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 0.9f, 1.0f, 0.6f);
	m_matLocal = matS;
	m_eState = OBJ_STATIC;
	m_nObjectType = lidtype;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"ThePass_FatScrolling.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/ThePass_Scrolling.png");
	m_Inven = NULL;
	
	m_PassScroll = new cPassScroll;
	m_PassScroll->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
}

void cPass::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}

void cPass::SetLight()
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

void cPass::Inventory()
{
	if (m_Inven)
	{
		if (m_Inven->GetInven())
		{
			m_Pot = (cPot*)m_Inven->GetInven()->GetParent();
			m_Pot->DestroyRecipe();
			m_Pot = NULL;
			m_Inven->SetInven(NULL);
			Present();
		}
		
	}

}

void cPass::Present()
{
	for (int i = 0; i<m_vec.size(); i++)
	{
		if (m_Inven->GetCost() == m_vec[i]->GetCost())
		{
			//m_SOM->OnAction(this);
			m_SOM->EraseOrder(i);
			break;
		}
		
	}
	
}
