#include "stdafx.h"
#include "cProgressbar.h"


cProgressbar::cProgressbar()
	: m_isComplete(false)
{
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);
	m_vecVertexBottom.clear();
	m_vecVertexTop.clear();
	m_vecComplete.clear();
}

cProgressbar::~cProgressbar()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pUITexture);
}

void cProgressbar::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos)
{
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 1.5f, 0);
	m_matLocal = matT;
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;

	m_fBottomGauge = 1.0f;
	m_fTopGauge = 0.0f;
	m_fProgress = 0.0f;
	m_fHeight = 0.3f; 
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Progressbar.png");
	

	///////////////////// bottom///////////////
	ST_PT_VERTEX v[4];

	v[0].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f, m_vPos.y - m_fHeight / 2.0f, m_vPos.z);

	v[1].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f, m_vPos.y + m_fHeight / 2.0f, m_vPos.z);

	v[2].p = D3DXVECTOR3(m_vPos.x + m_fBottomGauge / 2.0f, m_vPos.y + m_fHeight / 2.0f, m_vPos.z);

	v[3].p = D3DXVECTOR3(m_vPos.x + m_fBottomGauge / 2.0f, m_vPos.y - m_fHeight / 2.0f, m_vPos.z);

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
	v[0].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f + 0.1f, m_vPos.y - m_fHeight / 2.0f + 0.05f, m_vPos.z);

	v[1].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f + 0.1f, m_vPos.y + m_fHeight / 2.0f - 0.05f, m_vPos.z);

	v[2].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f + 0.1f + m_fProgress, m_vPos.y + m_fHeight / 2.0f - 0.05f, m_vPos.z);

	v[3].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f + 0.1f + m_fProgress, m_vPos.y - m_fHeight / 2.0f + 0.05f, m_vPos.z);

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
    //D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}

void cProgressbar::Update(D3DXVECTOR3 pos , int size)
{
	m_vecVertexBottom.clear();
	m_vecVertexTop.clear();
	m_vPos = pos;
	
	Complete();
	SetGauge(size);


	if (Complete()) // 
	{
		ST_PT_VERTEX v2[4];

		v2[0].p = D3DXVECTOR3(m_vPos.x - 1.0f / 2.0f, m_vPos.y - 1.0f / 2.0f, m_vPos.z);
		v2[1].p = D3DXVECTOR3(m_vPos.x - 1.0f / 2.0f, m_vPos.y + 1.0f / 2.0f, m_vPos.z);
		v2[2].p = D3DXVECTOR3(m_vPos.x + 1.0f / 2.0f, m_vPos.y + 1.0f / 2.0f, m_vPos.z);
		v2[3].p = D3DXVECTOR3(m_vPos.x + 1.0f / 2.0f, m_vPos.y - 1.0f / 2.0f, m_vPos.z);

		m_vecComplete.push_back(v2[0]);
		m_vecComplete.push_back(v2[1]);
		m_vecComplete.push_back(v2[2]);

		m_vecComplete.push_back(v2[3]);
		m_vecComplete.push_back(v2[0]);
		m_vecComplete.push_back(v2[2]);

		m_vecComplete[0].t.x = 0.0f; m_vecComplete[0].t.y = 1.0f - 0.0f;
		m_vecComplete[1].t.x = 0.0f; m_vecComplete[1].t.y = 1.0f - 1.0f;
		m_vecComplete[2].t.x = 1.0f; m_vecComplete[2].t.y = 1.0f - 1.0f;

		m_vecComplete[3].t.x = 1.0f; m_vecComplete[3].t.y = 1.0f- 0.0f;
		m_vecComplete[4].t.x = 0.0f; m_vecComplete[4].t.y = 1.0f- 0.0f;
		m_vecComplete[5].t.x = 1.0f; m_vecComplete[5].t.y = 1.0f- 1.0f;

		
	}
	else
	{
		m_fTopGauge += 0.05f;
		///////////////////// bottom///////////////
		ST_PT_VERTEX v[4];

		v[0].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f, m_vPos.y - m_fHeight / 2.0f, m_vPos.z);

		v[1].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f, m_vPos.y + m_fHeight / 2.0f, m_vPos.z);

		v[2].p = D3DXVECTOR3(m_vPos.x + m_fBottomGauge / 2.0f, m_vPos.y + m_fHeight / 2.0f, m_vPos.z);

		v[3].p = D3DXVECTOR3(m_vPos.x + m_fBottomGauge / 2.0f, m_vPos.y - m_fHeight / 2.0f, m_vPos.z);

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
		v[0].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f + 0.1f, m_vPos.y - m_fHeight / 2.0f + 0.05f, m_vPos.z);

		v[1].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f + 0.1f, m_vPos.y + m_fHeight / 2.0f - 0.05f, m_vPos.z);

		v[2].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f + 0.1f + m_fProgress, m_vPos.y + m_fHeight / 2.0f - 0.05f, m_vPos.z);

		v[3].p = D3DXVECTOR3(m_vPos.x - m_fBottomGauge / 2.0f + 0.1f + m_fProgress, m_vPos.y - m_fHeight / 2.0f + 0.05f, m_vPos.z);

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

		
	}
	
}

void cProgressbar::Render()
{
	if (!Complete())
		{
			D3DXMATRIX mat;
			D3DXMatrixIdentity(&mat);
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * mat));
			g_pD3DDevice->SetTexture(0, m_pTexture);
			g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
				m_vecVertexBottom.size() / 3,
				&m_vecVertexBottom[0],
				sizeof(ST_PT_VERTEX));

			g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal* mat));
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
				m_vecVertexTop.size() / 3,
				&m_vecVertexTop[0],
				sizeof(ST_PT_VERTEX));
		}
		else if (Complete())
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
			m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/CookingTick.png");
			g_pD3DDevice->SetTexture(0, m_pTexture);
			g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecComplete.size() / 3,
			&m_vecComplete[0],
			sizeof(ST_PT_VERTEX));
		}
}


float cProgressbar::SetGauge(int size)
{
	m_fProgress = (m_fTopGauge / (m_fBottomGauge * (float)size));

	return m_fProgress;
}

bool cProgressbar::Complete()
{
	if (m_fProgress >= 0.8f)
	{
		m_fProgress = 0.8f;

		return true;
	}
	return false;


}
