#include "stdafx.h"
#include "cChefRunPuff.h"

cChefRunPuff::cChefRunPuff()
			: m_fangle(0)
			, m_fScale(10.0f)
			, m_pDelegate(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocal);
}


cChefRunPuff::~cChefRunPuff()
{
	m_pMesh->Release();
	m_pTexture->Release();
	SAFE_RELEASE(m_pDelegate);
}

void cChefRunPuff::SetUp(D3DXVECTOR3 vPos)
{
	m_pMesh = ObJMANAGER->GetMesh(L"RunPuff.obj");
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/RunningPuff.png", &m_pTexture);
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y+0.3, vPos.z);
	m_matLocal = matT;
}

void cChefRunPuff::Update()
{
	if (m_fangle < D3DX_PI)
		m_fangle += 0.2f;
	
	D3DXMATRIX matS, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	
	D3DXMatrixScaling(&matS, m_fScale, m_fScale, m_fScale);
	D3DXMatrixRotationX(&matR, m_fangle);
	

	m_matWorld = matS * matR ;
}

void cChefRunPuff::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matWorld * m_matLocal));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}
