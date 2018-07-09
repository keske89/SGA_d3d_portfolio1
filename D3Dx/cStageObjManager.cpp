#include "stdafx.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
#include "cCharacter.h"
#include "cCrate.h"
#include "cKnife.h"
#include "cPot.h"
#include "cSink.h"

cStageObjManager::cStageObjManager()
{
}


cStageObjManager::~cStageObjManager()
{
}

void cStageObjManager::Setup()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR3 mPos(0, 0, 0);

	m_crate = new cCrate;
	m_crate->Setup(matWorld, mPos);

	m_vecObj.push_back(m_crate);
}

void cStageObjManager::Update()
{
	//for (int i = 0; i < m_vecObj.size(); i++);
	//{
	//	m_vecObj[i].
	//}

	for (auto p : m_vecObj)
	{
		p->Update();
	}
}

void cStageObjManager::Render()
{
	for (auto p : m_vecObj)
	{
		p->Render();
	}
}


void cStageObjManager::DeleteObject(cIGObj* object)
{
	for (int i = 0; i < m_vecObj.size(); i++)
	{
		if (m_vecObj[i] == object)
		{
			SAFE_DELETE(m_vecObj[i]);
			m_vecObj.erase(m_vecObj.begin()+i);
			break;
		}
	}
	
}
