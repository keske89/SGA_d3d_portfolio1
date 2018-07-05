#include "stdafx.h"
#include "cChefHead.h"


cChefHead::cChefHead()
{
}


cChefHead::~cChefHead()
{
	m_pTexture->Release();
}

void cChefHead::SetUp()
{

	D3DXMATRIX matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 3.45f, 0.0f, 0.0f);
	mat = matT;
	cObjLoader loader;
	m_pMesh = loader.LoadMesh(_T("./Resources/Mesh"), _T("/Chef_Bear.obj"), &mat);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/DLC_Chef_Bear.png", &m_pTexture);
}

void cChefHead::AniMation()
{
	if (m_ePartAnimation == PARTANIMATION_MOVE || m_ePartAnimation == PARTANIMATION_TRANCEPORT)
	{
		m_fRotY += m_fRotDeltaY;
		if (m_fRotY > D3DX_PI / 8.0f)
		{
			m_fRotY = D3DX_PI / 8.0f;
			m_fRotDeltaY *= -1.0;
		}

		if (m_fRotY < -D3DX_PI / 8.0f)
		{
			m_fRotY = -D3DX_PI / 8.0f;
			m_fRotDeltaY *= -1.0;
		}

		m_fRotX += m_fRotDeltaX;
		if (m_fRotX > D3DX_PI / 60.0f)
		{
			m_fRotX = D3DX_PI / 60.0f;
			m_fRotDeltaX *= -1.0f;
		}

		if (m_fRotX < -D3DX_PI / 60.0f)
		{
			m_fRotX = -D3DX_PI / 60.0f;
			m_fRotDeltaX *= -1.0f;
		}

		D3DXMATRIX matRY, matT, matT2, matT3;
		D3DXVECTOR3 temp = D3DXVECTOR3(0, m_fRotX, 0);
		D3DXMatrixIdentity(&matRY);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixIdentity(&matT2);

		D3DXMatrixRotationY(&matRY, m_fRotY);
		D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);
		D3DXMatrixTranslation(&matT2, temp.x, temp.y, temp.z);
		m_matLocalTM = matT2 * matRY * matT;
	}


}
