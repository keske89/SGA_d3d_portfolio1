#include "stdafx.h"
#include "cCharacterControl.h"
#include "cCharacter.h"
#include "cChefRoot.h"
cCharacterControl::cCharacterControl()
	: m_enmPlayerMod(PLAYERMOD_PLAY2P)
	, m_Bswitch(false)
	, m_fRotY1P(0.0f)
	, m_fRotY2P(0.0f)
	, m_vDirection1P(0, 0, 1)
	, m_vDirection2P(0, 0, 1)
	, m_vPosition1P(0, 0, 0)
	, m_vPosition2P(0, 0, 0)
{
	D3DXMatrixIdentity(&m_mat1P);
	D3DXMatrixIdentity(&m_mat2P);
}


cCharacterControl::~cCharacterControl()
{
	m_vecCharacter.clear();
}

void cCharacterControl::SetUp()
{
}

void cCharacterControl::Update()
{
}

void cCharacterControl::Render()
{
}

void cCharacterControl::Control()
{
	
	if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
	{
		if (m_Bswitch)
			m_Bswitch = false;
		
		else
			m_Bswitch = true;
	}
	
	Move();
}

void cCharacterControl::Move()
{
	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		if (!m_Bswitch)
		{
			if (KEYMANAGER->isStayKeyDown('F'))
			{
				m_fRotY1P -= 0.1f;
			}
			else if (KEYMANAGER->isStayKeyDown('H'))
			{
				m_fRotY1P += 0.1f;
			}

			if (KEYMANAGER->isStayKeyDown('T'))
			{
				m_vPosition1P += (m_vDirection1P * 0.1f);
			}
			else if (KEYMANAGER->isStayKeyDown('G'))
			{
				m_vPosition1P -= (m_vDirection1P * 0.1f);
			}

			D3DXMATRIX matR1P, matT1P;
			D3DXMatrixRotationY(&matR1P, m_fRotY1P);

			D3DXVec3TransformNormal(&m_vDirection1P, &D3DXVECTOR3(0, 0, 1), &matR1P);
			D3DXMatrixTranslation(&matT1P, m_vPosition1P.x, m_vPosition1P.y, m_vPosition1P.z);

			m_mat1P = matR1P * matT1P;
			m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_mat1P);
			
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
			{
				m_fRotY2P -= 0.1f;
			}
			else if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
			{
				m_fRotY2P += 0.1f;
			}

			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
			{
				m_vPosition2P += (m_vDirection2P * 0.1f);
			}
			else if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
			{
				m_vPosition2P -= (m_vDirection2P * 0.1f);
			}

			D3DXMATRIX matR2P, matT2P;
			D3DXMatrixRotationY(&matR2P, m_fRotY2P);

			D3DXVec3TransformNormal(&m_vDirection2P, &D3DXVECTOR3(0, 0, 1), &matR2P);
			D3DXMatrixTranslation(&matT2P, m_vPosition2P.x, m_vPosition2P.y, m_vPosition2P.z);

			m_mat2P = matR2P * matT2P;
			m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_mat2P);
		}
	}
	else if(PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{
		if (KEYMANAGER->isStayKeyDown('F'))
		{
			m_fRotY1P -= 0.1f;
		}
		else if (KEYMANAGER->isStayKeyDown('H'))
		{
			m_fRotY1P += 0.1f;
		}

		if (KEYMANAGER->isStayKeyDown('T'))
		{
			m_vPosition1P += (m_vDirection1P * 0.1f);
		}
		else if (KEYMANAGER->isStayKeyDown('G'))
		{
			m_vPosition1P -= (m_vDirection1P * 0.1f);
		}

		D3DXMATRIX matR1P, matT1P;
		D3DXMatrixRotationY(&matR1P, m_fRotY1P);

		D3DXVec3TransformNormal(&m_vDirection1P, &D3DXVECTOR3(0, 0, 1), &matR1P);
		D3DXMatrixTranslation(&matT1P, m_vPosition1P.x, m_vPosition1P.y, m_vPosition1P.z);

		m_mat1P = matR1P * matT1P;
		m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_mat1P);

		if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
		{
			m_fRotY2P -= 0.1f;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
		{
			m_fRotY2P += 0.1f;
		}

		if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
		{
			m_vPosition2P += (m_vDirection2P * 0.1f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
		{
			m_vPosition2P -= (m_vDirection2P * 0.1f);
		}

		D3DXMATRIX matR2P, matT2P;
		D3DXMatrixRotationY(&matR2P, m_fRotY2P);

		D3DXVec3TransformNormal(&m_vDirection2P, &D3DXVECTOR3(0, 0, 1), &matR2P);
		D3DXMatrixTranslation(&matT2P, m_vPosition2P.x, m_vPosition2P.y, m_vPosition2P.z);

		m_mat2P = matR2P * matT2P;
		m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_mat2P);
	}
}

D3DXMATRIX * cCharacterControl::Getworld(D3DXVECTOR3 positon, cCharacter * Chef)
{

	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		D3DXMATRIX matT;
		D3DXMatrixTranslation(&matT, positon.x, positon.y, positon.z);
		if (m_Bswitch && m_vecCharacter[0] == Chef)
		{
			m_mat2P *= matT;
			Chef->Setworld(m_mat2P);
			return &m_mat2P;
		}
		else if(!m_Bswitch && m_vecCharacter[1] == Chef)
		{
			m_mat1P *= matT;
			return &m_mat1P;
		}
	}
	else if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		D3DXMATRIX matT;
		D3DXMatrixTranslation(&matT, positon.x, positon.y, positon.z);
		if (m_vecCharacter[0] == Chef)
		{
			m_mat2P *= matT;
			return &m_mat1P;
		}
		else if (m_vecCharacter[1] == Chef)
		{
			m_mat1P *= matT;
			return &m_mat2P;
		}
	}
}

void cCharacterControl::SetPlaterMod(int num)
{
	if (num == 0 && num > 2) return;
	else
		m_enmPlayerMod = (PLAYERMOD)num;
	
}

void cCharacterControl::AddcCharacter(cCharacter * Chef)
{
	m_vecCharacter.push_back(Chef);
}
