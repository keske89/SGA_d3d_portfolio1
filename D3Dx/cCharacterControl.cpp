#include "stdafx.h"
#include "cCharacterControl.h"
#include "cChef.h"
#include "cChefRoot.h"
cCharacterControl::cCharacterControl()
	: m_enmPlayerMod(PLAYERMOD_PLAY1P)
	, m_Bswitch(false)
	, m_vbooster(0, 0, 0)
	, m_fCharacterBOOSTERSpeed(0.0f)
	, m_fFrictional(0.0f)
	, m_pAnimation(NULL)
{
}


cCharacterControl::~cCharacterControl()
{
	m_vecCharacter.clear();
}

void cCharacterControl::SetUp()
{
	D3DXMatrixTranslation(&m_StPlayerAtrribute[0].st_matPlayer, m_vecCharacter[0]->GetPos().x, m_vecCharacter[0]->GetPos().y, m_vecCharacter[0]->GetPos().z);
	D3DXMatrixTranslation(&m_StPlayerAtrribute[1].st_matPlayer, m_vecCharacter[1]->GetPos().x, m_vecCharacter[1]->GetPos().y, m_vecCharacter[1]->GetPos().z);
	m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[0].st_matPlayer);
	m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[1].st_matPlayer);
}
void cCharacterControl::SetUp(std::map<pair<int, int>, bool> StageIndex)
{
	D3DXMatrixTranslation(&m_StPlayerAtrribute[0].st_matPlayer, m_vecCharacter[0]->GetPos().x, m_vecCharacter[0]->GetPos().y, m_vecCharacter[0]->GetPos().z);
	D3DXMatrixTranslation(&m_StPlayerAtrribute[1].st_matPlayer, m_vecCharacter[1]->GetPos().x, m_vecCharacter[1]->GetPos().y, m_vecCharacter[1]->GetPos().z);
	m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[0].st_matPlayer);
	m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[1].st_matPlayer);
	m_mapSatgeIndex = StageIndex;
}
void cCharacterControl::Update()
{
}

void cCharacterControl::Render()
{
}

void cCharacterControl::Control()
{
	ControlAction();
	Move();
	Booster();
}

void cCharacterControl::ControlAction()
{
	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
		{
			if (m_Bswitch)
			{
				m_Bswitch = false;
			}
			else
			{
				m_Bswitch = true;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
		{
			//if (m_vecCharacter[(int)m_Bswitch]->GetcIGObject())
			m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_CHOP);
			//else if(m_vecCharacter[(int)m_Bswitch]->GetcIGObject())
			//	m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_DISHWASHING);
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			m_StPlayerAtrribute[m_Bswitch].st_fFrictional = 0.05f;
			m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed = 0.5f;
			m_StPlayerAtrribute[m_Bswitch].st_BisBooster = true;

		}
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (m_vecCharacter[m_Bswitch]->GetcIGObject() == NULL)
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		}


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}

	}
	else if (PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{
		Control1P();
		Control2P();
	}

}
void cCharacterControl::Control1P()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		m_StPlayerAtrribute[0].st_fFrictional = 0.05f;
		m_StPlayerAtrribute[0].st_fCharacterBOOSTERSpeed = 0.5f;
		m_StPlayerAtrribute[0].st_BisBooster = true;
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		//if (m_vecCharacter[(int)m_Bswitch]->GetcIGObject())
		m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_CHOP);
		//else if(m_vecCharacter[(int)m_Bswitch]->GetcIGObject())
		//	m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_DISHWASHING);
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (m_vecCharacter[0]->GetcIGObject() == NULL)
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
	}
	if (KEYMANAGER->isStayKeyDown('F'))
	{
		if (!m_vecCharacter[0]->GetcIGObject())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown('H'))
	{
		if (!m_vecCharacter[0]->GetcIGObject())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('F'))
	{
		if (!m_vecCharacter[0]->GetcIGObject())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('H'))
	{
		if (!m_vecCharacter[0]->GetcIGObject())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown('T'))
	{
		if (!m_vecCharacter[0]->GetcIGObject())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
	}
	if (KEYMANAGER->isStayKeyDown('G'))
	{
		if (!m_vecCharacter[0]->GetcIGObject())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
	}
	if (KEYMANAGER->isOnceKeyUp('T'))
	{
		if (!m_vecCharacter[0]->GetcIGObject())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('G'))
	{
		if (!m_vecCharacter[0]->GetcIGObject())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
}
void cCharacterControl::Control2P()
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		m_StPlayerAtrribute[1].st_fFrictional = 0.05f;
		m_StPlayerAtrribute[1].st_fCharacterBOOSTERSpeed = 0.5f;
		m_StPlayerAtrribute[1].st_BisBooster = true;
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		//if (m_vecCharacter[(int)m_Bswitch]->GetcIGObject())
		m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_CHOP);
		//else if(m_vecCharacter[(int)m_Bswitch]->GetcIGObject())
		//	m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_DISHWASHING);
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		if (m_vecCharacter[1]->GetcIGObject() == NULL)
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
	{
		if (!m_vecCharacter[1]->GetcIGObject())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
	{
		if (!m_vecCharacter[1]->GetcIGObject())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD4))
	{
		if (!m_vecCharacter[1]->GetcIGObject())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD6))
	{
		if (!m_vecCharacter[1]->GetcIGObject())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
	{
		if (!m_vecCharacter[1]->GetcIGObject())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
	{
		if (!m_vecCharacter[1]->GetcIGObject())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD8))
	{
		if (!m_vecCharacter[1]->GetcIGObject())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD5))
	{
		if (!m_vecCharacter[1]->GetcIGObject())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
}
void cCharacterControl::Move()
{
	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		D3DXVec3Normalize(&m_StPlayerAtrribute[m_Bswitch].st_vDirection, &(m_StPlayerAtrribute[m_Bswitch].st_vDirectionX + m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ));

		if (CheckChefIntersect())
			ChefIntersectMove();
		else
			m_vecCharacter[m_Bswitch]->GetPos() += m_StPlayerAtrribute[m_Bswitch].st_vDirection * (CharacterSpeed + m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed);


		D3DXMATRIX matWT, matR, matT;
		D3DXMatrixIdentity(&matWT);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);
		if (m_vecCharacter[m_Bswitch]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[m_Bswitch]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
		{
			m_StPlayerAtrribute[m_Bswitch].st_fAngle = atan2f(-m_StPlayerAtrribute[m_Bswitch].st_vDirection.z, m_StPlayerAtrribute[m_Bswitch].st_vDirection.x) + D3DX_PI / 2.0f;
		}
		D3DXMatrixRotationY(&matR, m_StPlayerAtrribute[m_Bswitch].st_fAngle);
		D3DXMatrixTranslation(&matT, m_vecCharacter[m_Bswitch]->GetPos().x, m_vecCharacter[m_Bswitch]->GetPos().y, m_vecCharacter[m_Bswitch]->GetPos().z);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[m_Bswitch].st_vDirection, &D3DXVECTOR3(0, 0, 1), &matT);

		m_StPlayerAtrribute[m_Bswitch].st_matPlayer = matR * matT;

		m_vecCharacter[m_Bswitch]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[m_Bswitch].st_matPlayer);

	}
	else if (PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{

		D3DXVec3Normalize(&m_StPlayerAtrribute[0].st_vDirection, &(m_StPlayerAtrribute[0].st_vDirectionX + m_StPlayerAtrribute[0].st_vDirectionZ));
		if (CheckChefIntersect())
			ChefIntersectMove();
		else
			m_vecCharacter[0]->GetPos() += m_StPlayerAtrribute[0].st_vDirection *  (CharacterSpeed + m_StPlayerAtrribute[0].st_fCharacterBOOSTERSpeed);

		D3DXMATRIX matR1P, matT1P;

		if (m_vecCharacter[0]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[0]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
		{
			m_StPlayerAtrribute[0].st_fAngle = atan2f(-m_StPlayerAtrribute[0].st_vDirection.z, m_StPlayerAtrribute[0].st_vDirection.x) + D3DX_PI / 2.0f;
		}
		D3DXMatrixRotationY(&matR1P, m_StPlayerAtrribute[0].st_fAngle);

		D3DXMatrixTranslation(&matT1P, m_vecCharacter[0]->GetPos().x, m_vecCharacter[0]->GetPos().y, m_vecCharacter[0]->GetPos().z);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[0].st_vDirection, &D3DXVECTOR3(0, 0, 1), &matT1P);


		m_StPlayerAtrribute[0].st_matPlayer = matR1P * matT1P;
		m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[0].st_matPlayer);
		//=================================================================================================================
		D3DXVec3Normalize(&m_StPlayerAtrribute[1].st_vDirection, &(m_StPlayerAtrribute[1].st_vDirectionX + m_StPlayerAtrribute[1].st_vDirectionZ));
		if (CheckChefIntersect())
			ChefIntersectMove();
		else
			m_vecCharacter[1]->GetPos() += m_StPlayerAtrribute[1].st_vDirection *  (CharacterSpeed + m_StPlayerAtrribute[1].st_fCharacterBOOSTERSpeed);

		D3DXMATRIX matR2P, matT2P;

		if (m_vecCharacter[1]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[1]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
		{
			m_StPlayerAtrribute[1].st_fAngle = atan2f(-m_StPlayerAtrribute[1].st_vDirection.z, m_StPlayerAtrribute[1].st_vDirection.x) + D3DX_PI / 2.0f;
		}
		D3DXMatrixRotationY(&matR2P, m_StPlayerAtrribute[1].st_fAngle);



		D3DXMatrixTranslation(&matT2P, m_vecCharacter[1]->GetPos().x, m_vecCharacter[1]->GetPos().y, m_vecCharacter[1]->GetPos().z);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[1].st_vDirection, &D3DXVECTOR3(0, 0, 1), &matT2P);


		m_StPlayerAtrribute[1].st_matPlayer = matR2P * matT2P;
		m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[1].st_matPlayer);

	}
}

void cCharacterControl::SetPlaterMod(int num)
{
	if (num == 0 && num > 2) return;
	else
		m_enmPlayerMod = (PLAYERMOD)num;

}

void cCharacterControl::AddcCharacter(cChef * Chef)
{
	m_vecCharacter.push_back(Chef);

}
void cCharacterControl::Booster()
{

	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		if (m_StPlayerAtrribute[m_Bswitch].st_BisBooster)
		{
			m_StPlayerAtrribute[m_Bswitch].st_vPosition += m_StPlayerAtrribute[m_Bswitch].st_vBooster * m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed;
			m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed -= m_StPlayerAtrribute[m_Bswitch].st_fFrictional;
		}
		if (m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed <= 0.0f)
		{
			m_StPlayerAtrribute[m_Bswitch].st_BisBooster = false;
			m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed = 0.0f;
		}
	}
	else if (PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{
		for (int i = 0; i < 2; i++)
		{
			if (m_StPlayerAtrribute[i].st_BisBooster)
			{
				m_StPlayerAtrribute[i].st_vPosition += m_StPlayerAtrribute[i].st_vBooster * m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed;
				m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed -= m_StPlayerAtrribute[i].st_fFrictional;
			}
			if (m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed <= 0.0f)
			{
				m_StPlayerAtrribute[i].st_BisBooster = false;
				m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed = 0.0f;
			}
		}
	}
}

BOOL cCharacterControl::CheckChefIntersect()
{
	float fDistance;
	D3DXVECTOR3 vDiff;

	vDiff = m_vecCharacter[0]->GetPos() - m_vecCharacter[1]->GetPos();
	fDistance = D3DXVec3Length(&vDiff);

	if (fDistance <= (m_vecCharacter[0]->Getradius() + m_vecCharacter[1]->Getradius()))
		return true;
	return false;
}

void cCharacterControl::ChefIntersectMove()
{
	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		D3DXVECTOR3 vChefIntersect = -(m_vecCharacter[m_Bswitch]->GetPos() - m_vecCharacter[!m_Bswitch]->GetPos());
		D3DXVec3Normalize(&vChefIntersect, &vChefIntersect);
		m_vecCharacter[!m_Bswitch]->GetPos() += vChefIntersect * (CharacterSpeed + m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed);
		D3DXMATRIX  matR, matT;
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixRotationY(&matR, m_StPlayerAtrribute[!m_Bswitch].st_fAngle);
		D3DXMatrixTranslation(&matT, m_vecCharacter[!m_Bswitch]->GetPos().x, m_vecCharacter[!m_Bswitch]->GetPos().y, m_vecCharacter[!m_Bswitch]->GetPos().z);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[!m_Bswitch].st_vDirection, &D3DXVECTOR3(0, 0, 1), &matT);
		m_StPlayerAtrribute[!m_Bswitch].st_matPlayer = matR * matT;
		m_vecCharacter[!m_Bswitch]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[!m_Bswitch].st_matPlayer);
	}
	else if (PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{
		D3DXVECTOR3 vChefIntersect1 = -(m_vecCharacter[0]->GetPos() - m_vecCharacter[1]->GetPos());
		D3DXVec3Normalize(&vChefIntersect1, &vChefIntersect1);
		m_vecCharacter[1]->GetPos() += vChefIntersect1 * (CharacterSpeed + m_StPlayerAtrribute[0].st_fCharacterBOOSTERSpeed);
		D3DXMATRIX  matR1, matT1;
		D3DXMatrixIdentity(&matT1);
		D3DXMatrixRotationY(&matR1, m_StPlayerAtrribute[1].st_fAngle);
		D3DXMatrixTranslation(&matT1, m_vecCharacter[1]->GetPos().x, m_vecCharacter[1]->GetPos().y, m_vecCharacter[1]->GetPos().z);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[1].st_vDirection, &D3DXVECTOR3(0, 0, 1), &matT1);
		m_StPlayerAtrribute[1].st_matPlayer = matR1 * matT1;
		m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[1].st_matPlayer);


		D3DXVECTOR3 vChefIntersect2 = -(m_vecCharacter[1]->GetPos() - m_vecCharacter[0]->GetPos());
		D3DXVec3Normalize(&vChefIntersect2, &vChefIntersect2);
		m_vecCharacter[0]->GetPos() += vChefIntersect2 * (CharacterSpeed + m_StPlayerAtrribute[1].st_fCharacterBOOSTERSpeed);
		D3DXMATRIX matR2, matT2;
		D3DXMatrixIdentity(&matT2);
		D3DXMatrixTranslation(&matT2, m_vecCharacter[0]->GetPos().x, m_vecCharacter[0]->GetPos().y, m_vecCharacter[0]->GetPos().z);
		D3DXMatrixRotationY(&matR2, m_StPlayerAtrribute[0].st_fAngle);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[0].st_vDirection, &D3DXVECTOR3(0, 0, 1), &matT2);
		m_StPlayerAtrribute[0].st_matPlayer = matR2 * matT2;
		m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[0].st_matPlayer);
	}
}
