#include "stdafx.h"
#include "cChefRunPuff.h"

cChefRunPuff::cChefRunPuff()
	: m_fangle(0)
	, m_fScale(10.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocal);
}


cChefRunPuff::~cChefRunPuff()
{
	m_pTexture->Release();
}

void cChefRunPuff::SetUp(D3DXVECTOR3 vPos)
{
	m_pMesh = ObJMANAGER->GetMesh(L"RunPuff.obj");
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/RunningPuff.png", &m_pTexture);
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y, vPos.z);
	m_matLocal = matT;
}

void cChefRunPuff::Update()
{
	if (m_fangle < D3DX_PI)
		m_fangle += 0.2f;
	if (m_fScale > 0)
		m_fScale -= 0.5f;
	else
		m_fScale = 0;
	D3DXMATRIX matS, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);

	D3DXMatrixScaling(&matS, m_fScale, m_fScale, m_fScale);
	D3DXMatrixRotationX(&matR, m_fangle);


	m_matWorld = matS * matR *m_matLocal;
}

void cChefRunPuff::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}

void cChefRunPuff::BoomMod(D3DXVECTOR3 dir)
{
	if (m_fangle < D3DX_PI * 2)
		m_fangle += 1.0f;
	if (m_fScale > 0)
		m_fScale -= 0.5f;
	else
		m_fScale = 0;
	D3DXMATRIX matS, matR, matR2, matT, matT2;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, m_fScale, m_fScale, m_fScale);
	D3DXMatrixRotationY(&matR, m_fangle);
	if (abs(dir.x) <abs(dir.z))
		D3DXMatrixTranslation(&matT, -sinf(m_fangle), -cosf(m_fangle), 0);
	else if (abs(dir.x) > abs(dir.z))
		D3DXMatrixTranslation(&matT, 0, -cosf(m_fangle), -sinf(m_fangle));
	else if (dir.x > dir.z)
		D3DXMatrixTranslation(&matT, -sinf(m_fangle), -cosf(m_fangle), -sinf(m_fangle));
	else if (dir.x <= dir.z)
		D3DXMatrixTranslation(&matT, -sinf(m_fangle), -cosf(m_fangle), sinf(m_fangle));
	m_matWorld = matS * matT *m_matLocal;
}

