#include "stdafx.h"
#include "iUIObject.h"


iUIObject::iUIObject(LPD3DXSPRITE pSprite)
	: m_bDrawBorder(false)
	, m_pSprite(pSprite)
	, m_color(D3DXCOLOR(1,1,1,1))
{
}


iUIObject::~iUIObject()
{
}

void iUIObject::Release()
{
}

void iUIObject::Setup()
{
}

void iUIObject::Update()
{
	UpdateCombinedPosition();

	for (auto p : m_vecChild)
	{
		if (p) p->Update();
	}
}

void iUIObject::Render()
{
	if (m_bDrawBorder) DrawBorder();

	for (auto p : m_vecChild)
	{
		if (p) p->Render();
	}

}

void iUIObject::UpdateCombinedPosition()
{
	m_combinedPos = m_vPosition;
	if (m_pParent)
	{
		m_combinedPos += *(static_cast<iUIObject*>(m_pParent)->GetCombinedPos());
	}
}

void iUIObject::DrawBorder()
{
	RECT rect;
	GetFinalRect(&rect);

	vector<ST_RHWC_VERTEX> vecVertex;	// RH - ¿ª¼ö
	D3DCOLOR c = WHITE;
	vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(rect.left, rect.top, 0, 1), c));
	vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(rect.right, rect.top, 0, 1), c));
	vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(rect.right, rect.bottom, 0, 1), c));
	vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(rect.left, rect.bottom, 0, 1), c));
	vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(rect.left, rect.top, 0, 1), c));

	g_pD3DDevice->SetFVF(ST_RHWC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, vecVertex.size() - 1, &vecVertex[0], sizeof(ST_RHWC_VERTEX));
}

void iUIObject::GetFinalRect(RECT * rect)
{
	D3DXMATRIX mat;
	m_pSprite->GetTransform(&mat);

	int left = mat._41 + m_combinedPos.x * mat._11;
	int top = mat._42 + m_combinedPos.y * mat._22;
	int right = left + m_size.x * mat._11;
	int bottom = top + m_size.y * mat._22;

	SetRect(rect, left, top, right, bottom);
}
