#include "stdafx.h"
#include "cIGObj.h"
#include "cTomato.h"
#include "cKnife.h"
#include "cObjLoader.h"

cIGObj::cIGObj()
	:m_bInteraction(false)
	,m_pMesh(NULL)
	,m_pTexture(NULL)
	,m_vPos(0.0f, 0.0f, 0.0f)
	, m_VecObj(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cIGObj::~cIGObj()
{
	SAFE_DELETE(m_Tomato);
	SAFE_DELETE(m_Knife);
	m_VecObj.clear();
	SAFE_DELETE(ObjLoader);
}

void cIGObj::Setup()
{

	m_Knife = new cKnife;
	m_Knife->Setup();
	m_Knife->m_pMesh = ObJMANAGER->GetMesh(L"Knife.obj");
	m_Knife->m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Knife.png"); 
	m_VecObj.push_back(m_Knife);

	
}

void cIGObj::Update()
{
	m_Knife->Update();
}

void cIGObj::Render()
{
	if (m_VecObj.size() !=NULL)
	{
		for (auto p : m_VecObj)
		{
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

			g_pD3DDevice->SetTexture(0, p->m_pTexture);
			p->m_pMesh->DrawSubset(0);

			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
			p->Render();
		}
	}

	m_Knife->Render();
	
}
