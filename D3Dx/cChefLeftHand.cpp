#include "stdafx.h"
#include "cChefLeftHand.h"


cChefLeftHand::cChefLeftHand()
{
}


cChefLeftHand::~cChefLeftHand()
{
	m_pTexture->Release();
}

void cChefLeftHand::SetUp()
{
	D3DXMATRIX matS, matT, mat;
	D3DXMatrixTranslation(&matT, -0.05f, 0.05f, 0.0f);
	mat = matT;
	cObjLoader loader;
	m_pMesh = loader.LoadMesh(_T("./Resources/Mesh"), _T("/Hand_Open_L1.obj"), &mat);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/DLC_Chef_Bear.png", &m_pTexture);

}

void cChefLeftHand::AniMation()
{
	if (PARTANIMATION_MOVE == m_ePartAnimation)
	{
		m_fRotX += m_fRotDeltaX;

		if (m_fRotX > D3DX_PI / 8.0f)
		{
			m_fRotX = D3DX_PI / 8.0f;
			m_fRotDeltaX *= -1.0;
		}

		if (m_fRotX < -D3DX_PI / 8.0f)
		{
			m_fRotX = -D3DX_PI / 8.0f;
			m_fRotDeltaX *= -1.0;
		}

		D3DXMATRIX matR, matT;
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);

		D3DXMatrixRotationX(&matR, m_fRotX);
		D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

		m_matLocalTM = matR * matT;
	}
}
