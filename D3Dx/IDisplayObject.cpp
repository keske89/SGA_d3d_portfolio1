#include "stdafx.h"
#include "IDisplayObject.h"


IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);

	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(1, 1, 1);
}

IDisplayObject::~IDisplayObject()
{
}

void IDisplayObject::Release()
{
	SAFE_RELEASE(m_pParent);

	for (auto child : m_vecChild)
	{
		if (child)
			child->Release();
	}
}

void IDisplayObject::AddChild(IDisplayObject * pChild)
{
	if (pChild == NULL) return;

	m_vecChild.push_back(pChild);
	pChild->m_pParent = this;
}

IDisplayObject * IDisplayObject::FindChildByName(LPCTSTR name)
{
	if (m_name == name) return this;

	for (auto p : m_vecChild)
	{
		IDisplayObject* pChild = p->FindChildByName(name);

		if (pChild) return pChild;
	}

	return NULL;
}
