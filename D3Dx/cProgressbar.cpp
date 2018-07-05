#include "stdafx.h"
#include "cProgressbar.h"


cProgressbar::cProgressbar()
{
	m_vecVertexBottom.clear();
	m_vecVertexTop.clear();
}


cProgressbar::~cProgressbar()
{
	SAFE_RELEASE(m_pTexture);
}

void cProgressbar::Setup(D3DXVECTOR3 pos)
{
	m_fCurrentWidth = 0.0f;
	m_fMaxWidth = 2.0f;
	m_fHeight = 0.3f;
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Progressbar.png");

	


}

void cProgressbar::Update(D3DXVECTOR3 pos)
{
	m_vecVertexBottom.clear();
	m_vecVertexTop.clear();
	///////////////////// bottom///////////////
	ST_PT_VERTEX v[4];

	v[0].p = D3DXVECTOR3(pos.x - m_fMaxWidth / 2.0f, pos.y - m_fHeight / 2.0f, pos.z);
	
	v[1].p = D3DXVECTOR3(pos.x - m_fMaxWidth / 2.0f, pos.y + m_fHeight / 2.0f, pos.z);
	
	v[2].p = D3DXVECTOR3(pos.x + m_fMaxWidth / 2.0f, pos.y + m_fHeight / 2.0f, pos.z);
	
	v[3].p = D3DXVECTOR3(pos.x + m_fMaxWidth / 2.0f, pos.y - m_fHeight / 2.0f, pos.z);
	
	m_vecVertexBottom.push_back(v[0]);
	m_vecVertexBottom.push_back(v[1]);
	m_vecVertexBottom.push_back(v[2]);
	
	m_vecVertexBottom.push_back(v[3]);
	m_vecVertexBottom.push_back(v[0]);
	m_vecVertexBottom.push_back(v[2]);
	
	m_vecVertexBottom[0].t.x = 0.1f; m_vecVertexBottom[0].t.y = 0.4f;
	m_vecVertexBottom[1].t.x = 0.1f; m_vecVertexBottom[1].t.y = 0.1f;
	m_vecVertexBottom[2].t.x = 1.0f; m_vecVertexBottom[2].t.y = 0.1f;
	
	m_vecVertexBottom[3].t.x = 1.0f; m_vecVertexBottom[3].t.y = 0.4f;
	m_vecVertexBottom[4].t.x = 0.1f; m_vecVertexBottom[4].t.y = 0.4f;
	m_vecVertexBottom[5].t.x = 1.0f; m_vecVertexBottom[5].t.y = 0.1f;

	//////////////////////////// top ///////////////////////////
	v[0].p = D3DXVECTOR3(pos.x - m_fMaxWidth / 2.0f + 0.1f, pos.y - m_fHeight / 2.0f + 0.05f, pos.z);

	v[1].p = D3DXVECTOR3(pos.x - m_fMaxWidth / 2.0f + 0.1f, pos.y + m_fHeight / 2.0f - 0.05f, pos.z);

	v[2].p = D3DXVECTOR3(pos.x - m_fMaxWidth / 2.0f + 0.1f + m_fCurrentWidth, pos.y + m_fHeight / 2.0f - 0.05f, pos.z);

	v[3].p = D3DXVECTOR3(pos.x - m_fMaxWidth / 2.0f + 0.1f + m_fCurrentWidth, pos.y - m_fHeight / 2.0f + 0.05f, pos.z);

	m_vecVertexTop.push_back(v[0]);
	m_vecVertexTop.push_back(v[1]);
	m_vecVertexTop.push_back(v[2]);

	m_vecVertexTop.push_back(v[3]);
	m_vecVertexTop.push_back(v[0]);
	m_vecVertexTop.push_back(v[2]);

	m_vecVertexTop[0].t.x = 0.0f; m_vecVertexTop[0].t.y = 1.0f;
	m_vecVertexTop[1].t.x = 0.0f; m_vecVertexTop[1].t.y = 0.5f;
	m_vecVertexTop[2].t.x = 1.0f; m_vecVertexTop[2].t.y = 0.5f;

	m_vecVertexTop[3].t.x = 1.0f; m_vecVertexTop[3].t.y = 1.0f;
	m_vecVertexTop[4].t.x = 0.0f; m_vecVertexTop[4].t.y = 1.0f;
	m_vecVertexTop[5].t.x = 1.0f; m_vecVertexTop[5].t.y = 0.5f;
		
	m_vPos = pos;


}

void cProgressbar::Render(D3DXVECTOR3 pos)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertexBottom.size() / 3,
		&m_vecVertexBottom[0],
		sizeof(ST_PT_VERTEX));


	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertexTop.size() / 3,
		&m_vecVertexTop[0],
		sizeof(ST_PT_VERTEX));
}

void cProgressbar::SetProgress()
{
	if (m_fCurrentWidth < m_fMaxWidth - 0.2f)
	{
		m_fCurrentWidth += 0.05f; // m_fCurrentWidth = m_fMaxWidth;
	}
	if (m_fCurrentWidth >= m_fMaxWidth - 0.2f)
	{
		m_fCurrentWidth = m_fMaxWidth - 0.2f; // m_fCurrentWidth = m_fMaxWidth;
	}
}
