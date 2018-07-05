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
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(ObjLoader);
}

void cIGObj::Setup()
{
	ObjLoader = new cObjLoader;

	m_Tomato = new cTomato;
	m_Tomato->Setup();
	m_Tomato->m_pMesh = ObjLoader->LoadMesh(_T("./Resources/Mesh/IngameObj"), _T("/Tomato_Whole.obj"), &m_matWorld);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Resources/Texture2D/Tomato.png", &m_Tomato->m_pTexture);
	m_VecObj.push_back(m_Tomato);

	m_Knife = new cKnife;
	m_Knife->Setup();
	m_Knife->m_pMesh = ObjLoader->LoadMesh(_T("./Resources/Mesh/IngameObj"), _T("/Knife.obj"), &m_matWorld);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Resources/Texture2D/Knife.png", &m_Knife->m_pTexture);
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
			//p->Render();
		}
	}

	m_Knife->Render();
	
}
