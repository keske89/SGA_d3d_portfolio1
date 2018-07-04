#include "stdafx.h"
#include "cChefRoot.h"


cChefRoot::cChefRoot()
	: m_fRotX(0.0f)
	, m_pTexture(NULL)
	, m_pMesh(NULL)
	, m_vLocalPos(0, 0, 0)
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

	m_fRotX += m_fRotDeltaX;


	D3DXMATRIX matR, matT;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixRotationX(&matR, m_fRotX);
	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

	m_matLocalTM = matR * matT;

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
	g_pD3DDevice->SetTexture(0,m_pTexture);
	m_pMesh->DrawSubset(0);

	for (int i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Render();
	}

}

