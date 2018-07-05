#include "stdafx.h"
#include "cChefRoot.h"


cChefRoot::cChefRoot()
	: m_pTexture(NULL)
	, m_pMesh(NULL)
	, m_ePartAnimation(PARTANIMATION_IDLE)
	, m_vLocalPos(0, 0, 0)
	, m_fRotX(0.0f)
	, m_fRotY(0.0f)
	, m_fRotDeltaY(0.0f)
	, m_fRotDeltaX(0.0f)
	, m_pParentWorldTM(NULL)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}

cChefRoot::~cChefRoot()
{
}

void cChefRoot::AddChild(cChefRoot * pChild)
{
	m_vecChild.push_back(pChild);

	pChild->m_pParentWorldTM = &m_matWorldTM;
}

void cChefRoot::Destroy()
{
	for (int i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->m_pTexture->Release();
		m_vecChild[i]->Destroy();
	}
	delete this;
}

void cChefRoot::SetUp()
{

}

void cChefRoot::Update()
{

	AniMation();
	m_matWorldTM = m_matLocalTM;
	if (m_pParentWorldTM)
	{
		m_matWorldTM *= (*m_pParentWorldTM);
	}

	for (int i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Update();
	}
}

void cChefRoot::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);

	for (int i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Render();
	}

}

void cChefRoot::AniMation()
{

}

void cChefRoot::ImageChange()
{
}

