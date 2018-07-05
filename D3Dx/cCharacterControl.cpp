#include "stdafx.h"
#include "cCharacterControl.h"
#include "cCharacter.h"
#include "cChefRoot.h"
cCharacterControl::cCharacterControl()
	: m_enmPlayerMod(PLAYERMOD_PLAY1P)
	, m_Bswitch(false)
	, m_vDirectionX(0, 0, 0)
	, m_vDirectionZ(0, 0, 0)
	, m_vDirection1P(0, 0, 1)
	, m_vDirection2P(0, 0, 1)
	, m_vPosition1P(0, 0, 0)
	, m_vPosition2P(0, 0, 0)
	, m_fangle1P(0.0f)
	, m_fangle2P(0.0f)
{
	D3DXMatrixIdentity(&m_mat1P);
	D3DXMatrixIdentity(&m_mat2P);
}


cCharacterControl::~cCharacterControl()
{
}

void cCharacterControl::SetUp()
{
	D3DXMatrixTranslation(&m_mat1P, m_vecCharacter[0]->GetPos().x, m_vecCharacter[0]->GetPos().y, m_vecCharacter[0]->GetPos().z);
	D3DXMatrixTranslation(&m_mat2P, m_vecCharacter[1]->GetPos().x, m_vecCharacter[1]->GetPos().y, m_vecCharacter[1]->GetPos().z);
	m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_mat1P);
	m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_mat2P);
}

void cCharacterControl::Update()
{
}

void cCharacterControl::Render()
{
}

void cCharacterControl::Control()
{
	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vecCharacter[(int)m_Bswitch]->GetRoot()->SetPart_AniMation(1);
			m_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_IDLE);
			for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_IDLE);
			m_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionZ = D3DXVECTOR3(0, 0, 1);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionZ = D3DXVECTOR3(0, 0, -1);
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_DOWN) || KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_IDLE);
			for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_IDLE);
			m_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
	}
	else if (PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			m_vecCharacter[0]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[0]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[0]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyDown('H'))
		{
			m_vecCharacter[0]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[0]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[0]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyUp('F') || KEYMANAGER->isOnceKeyUp('H'))
		{
			m_vecCharacter[0]->SetCHEF_STATE(CHEF_STATE_IDLE);
			for (int i = 0; i < m_vecCharacter[0]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[0]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_IDLE);
			m_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyDown('T'))
		{
			m_vecCharacter[0]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[0]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[0]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionZ = D3DXVECTOR3(0, 0, 1);
		}
		else if (KEYMANAGER->isOnceKeyDown('G'))
		{
			m_vecCharacter[0]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[0]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[0]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionZ = D3DXVECTOR3(0, 0, -1);
		}
		else if (KEYMANAGER->isOnceKeyUp('T') || KEYMANAGER->isOnceKeyUp('G'))
		{
			m_vecCharacter[0]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[0]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[0]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_IDLE);
			m_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
		{
			m_vecCharacter[1]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[1]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[1]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
		{
			m_vecCharacter[1]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[1]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[1]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD4) || KEYMANAGER->isOnceKeyUp(VK_NUMPAD6))
		{
			m_vecCharacter[1]->SetCHEF_STATE(CHEF_STATE_IDLE);
			for (int i = 0; i < m_vecCharacter[1]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[1]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_IDLE);
			m_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
		{
			m_vecCharacter[1]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[1]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[1]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionX = D3DXVECTOR3(0, 0, 1);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		{
			m_vecCharacter[1]->SetCHEF_STATE(CHEF_STATE_MOVE);
			for (int i = 0; i < m_vecCharacter[1]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[1]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_MOVE);
			m_vDirectionX = D3DXVECTOR3(0, 0, -1);
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD8) || KEYMANAGER->isOnceKeyUp(VK_NUMPAD5))
		{
			m_vecCharacter[1]->SetCHEF_STATE(CHEF_STATE_IDLE);
			for (int i = 0; i < m_vecCharacter[1]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[1]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_IDLE);
			m_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}
	}
	ControlAction();
	Move();

}

void cCharacterControl::ControlAction()
{
	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
		{
			if (m_Bswitch)
				m_Bswitch = false;
			else
				m_Bswitch = true;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
		{
			m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_CHOP);
			for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
				m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_CHOP);
			m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[2]->ImageChange();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			if (m_vecCharacter[(int)m_Bswitch]->GetObjectW())
			{
				m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_TRANCEPORT_IDLE);
				for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
					m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_TRANCEPORT);
			}
			else
			{
				m_vecCharacter[(int)m_Bswitch]->SetCHEF_STATE(CHEF_STATE_IDLE);
				for (int i = 0; i < m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild().size(); i++)
					m_vecCharacter[(int)m_Bswitch]->GetRoot()->GetChild()[i]->SetPart_AniMation(PARTANIMATION_IDLE);
			}
		}
	}
}

void cCharacterControl::Move()
{
	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{

		if (!m_Bswitch)
		{
			D3DXVec3Normalize(&m_vDirection1P, &(m_vDirectionX + m_vDirectionZ));
			m_vPosition1P += m_vDirection1P * CharacterSpeed;

			D3DXMATRIX matWT1P, matR1P, matT1P;

			if (m_vecCharacter[(int)m_Bswitch]->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[(int)m_Bswitch]->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
			{
				m_fangle1P = atan2f(-m_vDirection1P.z, m_vDirection1P.x) + D3DX_PI / 2.0f;
			}
			D3DXMatrixRotationY(&matR1P, m_fangle1P);

			D3DXMatrixTranslation(&matWT1P,
				m_vecCharacter[(int)m_Bswitch]->GetPos().x,
				m_vecCharacter[(int)m_Bswitch]->GetPos().y,
				m_vecCharacter[(int)m_Bswitch]->GetPos().z);

			D3DXMatrixTranslation(&matT1P, m_vPosition1P.x, m_vPosition1P.y, m_vPosition1P.z);
			D3DXVec3TransformNormal(&m_vDirection1P, &D3DXVECTOR3(0, 0, 1), &matT1P);


			m_mat1P = matR1P * matWT1P *matT1P;
			m_vecCharacter[(int)m_Bswitch]->GetRoot()->SetParentWorldTM(&m_mat1P);
		}
		else
		{
			D3DXVec3Normalize(&m_vDirection2P, &(m_vDirectionX + m_vDirectionZ));
			m_vPosition2P += m_vDirection2P * CharacterSpeed;

			D3DXMATRIX matWT2P, matR2P, matT2P;

			if (m_vecCharacter[(int)m_Bswitch]->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[(int)m_Bswitch]->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
			{
				m_fangle2P = atan2f(-m_vDirection2P.z, m_vDirection2P.x) + D3DX_PI / 2.0f;
			}
			D3DXMatrixRotationY(&matR2P, m_fangle2P);

			D3DXMatrixTranslation(&matWT2P,
				m_vecCharacter[(int)m_Bswitch]->GetPos().x,
				m_vecCharacter[(int)m_Bswitch]->GetPos().y,
				m_vecCharacter[(int)m_Bswitch]->GetPos().z);

			D3DXMatrixTranslation(&matT2P, m_vPosition2P.x, m_vPosition2P.y, m_vPosition2P.z);
			D3DXVec3TransformNormal(&m_vDirection1P, &D3DXVECTOR3(0, 0, 1), &matT2P);


			m_mat2P = matR2P * matWT2P *matT2P;
			m_vecCharacter[(int)m_Bswitch]->GetRoot()->SetParentWorldTM(&m_mat2P);
		}
	}
	else if (PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{

		D3DXVec3Normalize(&m_vDirection1P, &(m_vDirectionX + m_vDirectionZ));
		m_vPosition1P += m_vDirection1P * CharacterSpeed;

		D3DXMATRIX matWT1P, matR1P, matT1P;

		if (m_vecCharacter[0]->GetCHEF_STATE() != CHEF_STATE_IDLE)
		{
			m_fangle1P = atan2f(-m_vDirection1P.z, m_vDirection1P.x) + D3DX_PI / 2.0f;

		}
		D3DXMatrixRotationY(&matR1P, m_fangle1P);

		D3DXMatrixTranslation(&matWT1P,
			m_vecCharacter[0]->GetPos().x,
			m_vecCharacter[0]->GetPos().y,
			m_vecCharacter[0]->GetPos().z);

		D3DXMatrixTranslation(&matT1P, m_vPosition1P.x, m_vPosition1P.y, m_vPosition1P.z);
		D3DXVec3TransformNormal(&m_vDirection1P, &D3DXVECTOR3(0, 0, 1), &matT1P);


		m_mat1P = matR1P * matT1P;
		m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_mat1P);

		D3DXVec3Normalize(&m_vDirection2P, &(m_vDirectionX + m_vDirectionZ));
		m_vPosition2P += m_vDirection2P * CharacterSpeed;

		D3DXMATRIX matWT2P, matR2P, matT2P;

		if (m_vecCharacter[1]->GetCHEF_STATE() != CHEF_STATE_IDLE)
		{
			m_fangle2P = atan2f(-m_vDirection2P.z, m_vDirection2P.x) + D3DX_PI / 2.0f;
		}
		D3DXMatrixRotationY(&matR2P, m_fangle2P);

		D3DXMatrixTranslation(&matWT2P,
			m_vecCharacter[1]->GetPos().x,
			m_vecCharacter[1]->GetPos().y,
			m_vecCharacter[1]->GetPos().z);

		D3DXMatrixTranslation(&matT2P, m_vPosition2P.x, m_vPosition2P.y, m_vPosition2P.z);
		D3DXVec3TransformNormal(&m_vDirection2P, &D3DXVECTOR3(0, 0, 1), &matT2P);


		m_mat2P = matR2P * matWT2P *matT2P;
		m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_mat2P);

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
