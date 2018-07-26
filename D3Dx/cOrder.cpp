#include "stdafx.h"
#include "cOrder.h"


cOrder::cOrder()
	: m_vPosition(0, 0, 0)
	, m_pParent(NULL)
	, m_stSize(0, 0)
{
}


cOrder::~cOrder()
{
}

void cOrder::AddChild(cOrder * pChild)
{
	m_vecChild.push_back(pChild);
	pChild->SetParent(this);
}

void cOrder::Destroy()
{
	for (auto child : m_vecChild)
	{
		child->Destroy();
	}
	delete this;
}

void cOrder::Update()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	for (auto child : m_vecChild)
	{
		child->Update();
	}
}

void cOrder::Render(LPD3DXSPRITE pSprite)
{
	for (auto child : m_vecChild)
	{
		child->Render(pSprite);
	}
}
