#include "stdafx.h"
#include "cIGObj.h"
#include "cTomato.h"
#include "cKnife.h"
#include "cPot.h"
#include "cCrate.h"


cIGObj::cIGObj()
	: m_bInteraction(false)
	, m_pMesh(NULL)
	, m_pTexture(NULL)
	, m_vPos(0.0f, 0.0f, 0.0f)
{	
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
	D3DXMatrixIdentity(&m_matLocal);
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

	//
	//m_Tomato = new cTomato;
	//m_Tomato->Setup();
	//m_VecObj.push_back(m_Tomato);

	
}

void cIGObj::Update()
{
	if (m_VecObj.size() != NULL)
	{
		for (auto p : m_VecObj)
		{
			p->Update();
		}
	}
	
}

void cIGObj::Render()
{

	if (m_VecObj.size() != NULL)
	{
		for (auto p : m_VecObj)
		{
			p->Render();
		}
	}
}

void cIGObj::Destroy(cIGObj* target)
{

	vector<cIGObj*> ::iterator m_viobj;
	
	
	for (m_viobj = m_VecObj.begin(); m_viobj != m_VecObj.end(); m_viobj++)
	{
		if (*m_viobj == target)
		{
			SAFE_DELETE(*m_viobj);

			m_viobj = m_VecObj.erase(m_viobj);
			break;
		}
	}
}

cIGObj* cIGObj::CreateCrate()
{
	cIGObj* crate;
	crate = new cCrate;
	crate->Setup();

	return crate;
}
