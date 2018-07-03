#include "stdafx.h"
#include "cIGObj.h"
#include "cTomato.h"
#include "cObjLoader.h"

cIGObj::cIGObj()
	:m_bInteraction(false)
	,m_pMesh(NULL)
	,m_pTexture(NULL)
	,m_vPos(0.0f, 0.0f, 0.0f)
	, m_VecObj(NULL)
{
	D3DXMatrixIdentity(&m_matT);
}


cIGObj::~cIGObj()
{
	delete m_Tomato;
	m_VecObj.clear();
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(ObjLoader);
}

void cIGObj::Setup()
{
	ObjLoader = new cObjLoader;

	m_Tomato = new cTomato;
	m_Tomato->m_pMesh = ObjLoader->LoadMesh(_T("./Resources/Mesh/IngameObj"), _T("/Tomato_Whole.obj"), &m_matT);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Resources/Texture2D/Tomato.png", &m_Tomato->m_pTexture);
	m_VecObj.push_back(m_Tomato);
}

void cIGObj::Update()
{
}

void cIGObj::Render()
{
	if (m_VecObj.size() !=NULL)
	{
		for (auto p : m_VecObj)
		{
			p->Render();
		}
	}
	
}
