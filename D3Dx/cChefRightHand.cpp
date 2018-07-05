#include "stdafx.h"
#include "cChefRightHand.h"


cChefRightHand::cChefRightHand()
{
}


cChefRightHand::~cChefRightHand()
{
	m_pTexture->Release();
}

void cChefRightHand::SetUp()
{
	ImageChange();

	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/DLC_Chef_Bear.png", &m_pTexture);

}

void cChefRightHand::AniMation()
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
	else if (PARTANIMATION_TRANCEPORT == m_ePartAnimation)
	{

	}
}

void cChefRightHand::ImageChange()
{

	D3DXMATRIX matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0.07f, 0.05f, 0.0f);
	mat = matT;
	cObjLoader loader;
	if (PARTANIMATION_CHOP != m_ePartAnimation)
		m_pMesh = loader.LoadMesh(_T("./Resources/Mesh"), _T("/Hand_Open_R #000539.obj"), &mat);
	else
		m_pMesh = loader.LoadMesh(_T("./Resources/Mesh"), _T("/Hand_Grip_R #010449.obj"), &mat);
}
