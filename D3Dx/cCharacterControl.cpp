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
	D3DXMatrixTranslation(&m_StPlayerAtrribute[0].ST_matPlayer, m_vecCharacter[0]->GetPos().x, m_vecCharacter[0]->GetPos().y, m_vecCharacter[0]->GetPos().z);
	D3DXMatrixTranslation(&m_StPlayerAtrribute[1].ST_matPlayer, m_vecCharacter[1]->GetPos().x, m_vecCharacter[1]->GetPos().y, m_vecCharacter[1]->GetPos().z);
	m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[0].ST_matPlayer);
	m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[1].ST_matPlayer);
}
void cCharacterControl::SetUp(std::map<pair<int, int>, bool> StageIndex)
{
	D3DXMatrixTranslation(&m_StPlayerAtrribute[0].ST_matPlayer, m_vecCharacter[0]->GetPos().x, m_vecCharacter[0]->GetPos().y, m_vecCharacter[0]->GetPos().z);
	D3DXMatrixTranslation(&m_StPlayerAtrribute[1].ST_matPlayer, m_vecCharacter[1]->GetPos().x, m_vecCharacter[1]->GetPos().y, m_vecCharacter[1]->GetPos().z);
	m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[0].ST_matPlayer);
	m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[1].ST_matPlayer);
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
	Booster(m_vbooster);
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
			//if (m_vecCharacter[(int)m_Bswitch]->GetcIGObject())
			m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_CHOP);
			//else if(m_vecCharacter[(int)m_Bswitch]->GetcIGObject())
			//	m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_DISHWASHING);
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			m_fFrictional = 0.05f;
			m_fCharacterBOOSTERSpeed = 0.5f;
			m_StPlayerAtrribute[m_Bswitch].ST_BisBooster = true;

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
			m_StPlayerAtrribute[m_Bswitch].St_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].St_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].St_vDirectionZ = D3DXVECTOR3(0, 0, 1);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].St_vDirectionZ = D3DXVECTOR3(0, 0, -1);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN) || KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].St_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetcIGObject())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].St_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}

	}
	else if (PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_CHOP);
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			if (m_vecCharacter[0]->GetcIGObject() == NULL)
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
			else
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		}
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			if (!m_vecCharacter[0]->GetcIGObject())
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

			m_StPlayerAtrribute[0].St_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyDown('H'))
		{
			if (!m_vecCharacter[0]->GetcIGObject())
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

			m_StPlayerAtrribute[0].St_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyUp('F') || KEYMANAGER->isOnceKeyUp('H'))
		{
			if (!m_vecCharacter[0]->GetcIGObject())
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
			m_StPlayerAtrribute[0].St_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyDown('T'))
		{
			if (!m_vecCharacter[0]->GetcIGObject())
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

			m_StPlayerAtrribute[0].St_vDirectionZ = D3DXVECTOR3(0, 0, 1);
		}
		else if (KEYMANAGER->isOnceKeyDown('G'))
		{
			if (!m_vecCharacter[0]->GetcIGObject())
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

			m_StPlayerAtrribute[0].St_vDirectionZ = D3DXVECTOR3(0, 0, -1);
		}
		else if (KEYMANAGER->isOnceKeyUp('T') || KEYMANAGER->isOnceKeyUp('G'))
		{
			if (!m_vecCharacter[0]->GetcIGObject())
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[0].St_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
		{
			if (!m_vecCharacter[1]->GetcIGObject())
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

			m_StPlayerAtrribute[1].St_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
		{
			if (!m_vecCharacter[1]->GetcIGObject())
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

			m_StPlayerAtrribute[1].St_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD4) || KEYMANAGER->isOnceKeyUp(VK_NUMPAD6))
		{
			if (!m_vecCharacter[1]->GetcIGObject())
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[1].St_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
		{
			if (!m_vecCharacter[1]->GetcIGObject())
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

			m_StPlayerAtrribute[1].St_vDirectionZ = D3DXVECTOR3(0, 0, 1);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		{
			if (!m_vecCharacter[1]->GetcIGObject())
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

			m_StPlayerAtrribute[1].St_vDirectionZ = D3DXVECTOR3(0, 0, -1);
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD8) || KEYMANAGER->isOnceKeyUp(VK_NUMPAD5))
		{
			if (!m_vecCharacter[1]->GetcIGObject())
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[1].St_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
	}

}
void cCharacterControl::Move()
{
	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		D3DXVec3Normalize(&m_StPlayerAtrribute[m_Bswitch].St_vDirection, &(m_StPlayerAtrribute[m_Bswitch].St_vDirectionX + m_StPlayerAtrribute[m_Bswitch].St_vDirectionZ));
		m_vbooster = m_StPlayerAtrribute[m_Bswitch].St_vDirection;
		m_StPlayerAtrribute[m_Bswitch].St_vPosition += m_StPlayerAtrribute[m_Bswitch].St_vDirection * (CharacterSpeed + m_fCharacterBOOSTERSpeed);

		D3DXMATRIX matWT, matR, matT;
		D3DXMatrixIdentity(&matWT);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);
		if (m_vecCharacter[m_Bswitch]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[m_Bswitch]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
		{
			m_StPlayerAtrribute[m_Bswitch].St_fAngle = atan2f(-m_StPlayerAtrribute[m_Bswitch].St_vDirection.z, m_StPlayerAtrribute[m_Bswitch].St_vDirection.x) + D3DX_PI / 2.0f;
		}
		D3DXMatrixRotationY(&matR, m_StPlayerAtrribute[m_Bswitch].St_fAngle);

		D3DXMatrixTranslation(&matWT,
			m_vecCharacter[m_Bswitch]->GetPos().x,
			m_vecCharacter[m_Bswitch]->GetPos().y,
			m_vecCharacter[m_Bswitch]->GetPos().z);

		D3DXMatrixTranslation(&matT, m_StPlayerAtrribute[m_Bswitch].St_vPosition.x, m_StPlayerAtrribute[m_Bswitch].St_vPosition.y, m_StPlayerAtrribute[m_Bswitch].St_vPosition.z);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[m_Bswitch].St_vDirection, &D3DXVECTOR3(0, 0, 1), &matT);


		m_StPlayerAtrribute[m_Bswitch].ST_matPlayer = matR * matWT *matT;
		m_vecCharacter[(int)m_Bswitch]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[m_Bswitch].ST_matPlayer);
	}
	else if (PLAYERMOD_PLAY2P == m_enmPlayerMod)
	{

		D3DXVec3Normalize(&m_StPlayerAtrribute[0].St_vDirection, &(m_StPlayerAtrribute[0].St_vDirectionX + m_StPlayerAtrribute[0].St_vDirectionZ));
		m_StPlayerAtrribute[0].St_vPosition += m_StPlayerAtrribute[0].St_vDirection * CharacterSpeed;

		D3DXMATRIX matR1P, matT1P;

		if (m_vecCharacter[0]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[0]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
		{
			m_StPlayerAtrribute[0].St_fAngle = atan2f(-m_StPlayerAtrribute[0].St_vDirection.z, m_StPlayerAtrribute[0].St_vDirection.x) + D3DX_PI / 2.0f;
		}
		D3DXMatrixRotationY(&matR1P, m_StPlayerAtrribute[0].St_fAngle);

		D3DXMatrixTranslation(&m_StPlayerAtrribute[0].ST_matPlayer,
			m_vecCharacter[0]->GetPos().x,
			m_vecCharacter[0]->GetPos().y,
			m_vecCharacter[0]->GetPos().z);

		D3DXMatrixTranslation(&matT1P, m_StPlayerAtrribute[0].St_vPosition.x, m_StPlayerAtrribute[0].St_vPosition.y, m_StPlayerAtrribute[0].St_vPosition.z);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[0].St_vDirection, &D3DXVECTOR3(0, 0, 1), &matT1P);


		m_StPlayerAtrribute[0].ST_matPlayer = matR1P * m_StPlayerAtrribute[0].ST_matPlayer *matT1P;
		m_vecCharacter[0]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[0].ST_matPlayer);
		//=================================================================================================================
		D3DXVec3Normalize(&m_StPlayerAtrribute[1].St_vDirection, &(m_StPlayerAtrribute[1].St_vDirectionX + m_StPlayerAtrribute[1].St_vDirectionZ));
		m_StPlayerAtrribute[1].St_vPosition += m_StPlayerAtrribute[1].St_vDirection * CharacterSpeed;

		D3DXMATRIX matR2P, matT2P;

		if (m_vecCharacter[1]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[1]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
		{
			m_StPlayerAtrribute[1].St_fAngle = atan2f(-m_StPlayerAtrribute[1].St_vDirection.z, m_StPlayerAtrribute[1].St_vDirection.x) + D3DX_PI / 2.0f;
		}
		D3DXMatrixRotationY(&matR2P, m_StPlayerAtrribute[1].St_fAngle);

		D3DXMatrixTranslation(&m_StPlayerAtrribute[1].ST_matPlayer,
			m_vecCharacter[1]->GetPos().x,
			m_vecCharacter[1]->GetPos().y,
			m_vecCharacter[1]->GetPos().z);

		D3DXMatrixTranslation(&matT2P, m_StPlayerAtrribute[1].St_vPosition.x, m_StPlayerAtrribute[1].St_vPosition.y, m_StPlayerAtrribute[1].St_vPosition.z);
		D3DXVec3TransformNormal(&m_StPlayerAtrribute[1].St_vDirection, &D3DXVECTOR3(0, 0, 1), &matT2P);


		m_StPlayerAtrribute[1].ST_matPlayer = matR2P * m_StPlayerAtrribute[1].ST_matPlayer *matT2P;
		m_vecCharacter[1]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[1].ST_matPlayer);

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
void cCharacterControl::Booster(D3DXVECTOR3 pos)
{

	if (PLAYERMOD_PLAY1P == m_enmPlayerMod)
	{
		if (m_StPlayerAtrribute[m_Bswitch].ST_BisBooster)
		{
			m_StPlayerAtrribute[m_Bswitch].St_vPosition += pos * m_fCharacterBOOSTERSpeed;
		}
		m_fCharacterBOOSTERSpeed -= m_fFrictional;

		if (m_fCharacterBOOSTERSpeed <= 0.0f)
		{
			m_StPlayerAtrribute[m_Bswitch].ST_BisBooster = false;
			m_fCharacterBOOSTERSpeed = 0.0f;

		}
	}
}