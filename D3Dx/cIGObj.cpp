#include "stdafx.h"
#include "cIGObj.h"
#include "cTomato.h"
#include "cKnife.h"
#include "cPot.h"
#include "cCrate.h"


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
	
}

void cIGObj::Setup()
{

	//m_Knife = new cKnife;
	//m_Knife->Setup();
	//m_VecObj.push_back(m_Knife);
	//
	//
	//m_Pot = new cPot;
	//m_Pot->Setup();
	//m_VecObj.push_back(m_Pot);
	//
	//m_Tomato = new cTomato;
	//m_Tomato->Setup();
	//m_VecObj.push_back(m_Tomato);

	m_Crate = new cCrate;
	m_Crate->Setup();
	m_VecObj.push_back(m_Crate);
	
}

void cIGObj::Update()
{
	for (auto p : m_VecObj)
	{
		p->Update();
	}
	
}

void cIGObj::Render()
{
	if (m_VecObj.size() !=NULL)
	{
		for (auto p : m_VecObj)
		{
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

			g_pD3DDevice->SetTexture(0, p->m_pTexture);
			p->m_pMesh->DrawSubset(0);

			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
			

			p->Render();
		}
	}

	
	
}
