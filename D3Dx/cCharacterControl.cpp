#include "stdafx.h"
#include "cCharacterControl.h"
#include "cChef.h"
#include "cChefRoot.h"
cCharacterControl::cCharacterControl()
	: m_enmPlayerMod(PLAYERMOD_PLAY1P)
	, m_Bswitch(false)
{
}


cCharacterControl::~cCharacterControl()
{
	for (int i = 0; i < m_vecCharacter.size(); i++)
	{
		m_vecCharacter[i]->Relese();
	}
}

void cCharacterControl::SetUp()
{
}
void cCharacterControl::SetUp(std::map<pair<int, int>, bool> StageIndex)
{
	m_mapSatgeIndex = StageIndex;
}
void cCharacterControl::Update()
{
}

void cCharacterControl::Render()
{
}

void cCharacterControl::Control(IN cChef * _Chef)
{
	ControlAction();
	Move(_Chef);
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
			if (!m_StPlayerAtrribute[m_Bswitch].st_BisBooster)
			{
				m_StPlayerAtrribute[m_Bswitch].st_fFrictional = 0.05f;
				m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed = 0.5f;
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_BOOSTER_MOVE);
				m_StPlayerAtrribute[m_Bswitch].st_BisBooster = true;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (m_vecCharacter[m_Bswitch]->GetInven() == NULL)
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
			else
			{
				m_vecCharacter[m_Bswitch]->SetInven(NULL);
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			}
		}


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
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
		m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_BOOSTER_MOVE);
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
		if (m_vecCharacter[0]->GetInven() == NULL)
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
	}
	if (KEYMANAGER->isStayKeyDown('F'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown('H'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('F'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('H'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown('T'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
	}
	if (KEYMANAGER->isStayKeyDown('G'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
	}
	if (KEYMANAGER->isOnceKeyUp('T'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('G'))
	{
		if (!m_vecCharacter[0]->GetInven())
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
		m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_BOOSTER_MOVE);
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
		if (m_vecCharacter[1]->GetInven() == NULL)
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD4))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD6))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD8))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD5))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->GetRoot()->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
}
void cCharacterControl::SetPos1P(D3DXVECTOR3 _pos)
{
	m_vecCharacter[0]->SetPos(_pos);
}
void cCharacterControl::SetPos2P(D3DXVECTOR3 _pos)
{
	m_vecCharacter[1]->SetPos(_pos);
}
void cCharacterControl::Move(IN cChef * _Chef)
{
	for (int i = 0; i < 2; i++)
	{
		if (m_vecCharacter[i] == _Chef)
		{
			_Chef->GetDir() = m_StPlayerAtrribute[i].st_vDirectionX + m_StPlayerAtrribute[i].st_vDirectionZ;
			
			D3DXVec3Normalize(&m_StPlayerAtrribute[i].st_vDirection, &(m_StPlayerAtrribute[i].st_vDirectionX + m_StPlayerAtrribute[i].st_vDirectionZ));
			if (m_StPlayerAtrribute[i].st_vDirection == D3DXVECTOR3(0, 0, 0))
			{
				if (m_StPlayerAtrribute[i].st_fAngle == 0.0f)
					_Chef->GetDir() = D3DXVECTOR3(0, 0, 1);
				//45도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI / 4)
					_Chef->GetDir() = D3DXVECTOR3(1, 0, 1);
				//90도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI / 2)
					_Chef->GetDir() = D3DXVECTOR3(1, 0, 0);
				//135도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI / 4 * 3)
					_Chef->GetDir() = D3DXVECTOR3(1, 0, -1);
				//180도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI)
					_Chef->GetDir() = D3DXVECTOR3(0, 0, -1);
				//225도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI / 4 * 5)
					_Chef->GetDir() = D3DXVECTOR3(-1, 0, -1);
				//270도
				else if (m_StPlayerAtrribute[i].st_fAngle == -D3DX_PI / 2)
					_Chef->GetDir() = D3DXVECTOR3(-1, 0, 0);
				//315도
				else if (m_StPlayerAtrribute[i].st_fAngle == -D3DX_PI / 4)
					_Chef->GetDir() = D3DXVECTOR3(-1, 0, 1);
			}
				
			

			if (m_vecCharacter[i]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_BOOSTER_MOVE)
			{
				m_vecCharacter[i]->GetPos() += _Chef->GetDir() *  (CharacterSpeed + m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed);
				m_vecCharacter[i]->GetToGo() = _Chef->GetDir() *  (CharacterSpeed + m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed);
			}
			else
			{
				m_vecCharacter[i]->GetPos() += m_StPlayerAtrribute[i].st_vDirection *  (CharacterSpeed + m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed);
				m_vecCharacter[i]->GetToGo() = m_StPlayerAtrribute[i].st_vDirection *  (CharacterSpeed + m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed);
			}
			
			D3DXMATRIX matR1P, matT1P;

			if (m_vecCharacter[i]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[i]->GetRoot()->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
			{
				m_StPlayerAtrribute[i].st_fAngle = atan2f(-m_StPlayerAtrribute[i].st_vDirection.z, m_StPlayerAtrribute[i].st_vDirection.x) + D3DX_PI / 2.0f;
			}
			D3DXMatrixRotationY(&matR1P, m_StPlayerAtrribute[i].st_fAngle);

			D3DXMatrixTranslation(&matT1P, m_vecCharacter[i]->GetPos().x, m_vecCharacter[i]->GetPos().y, m_vecCharacter[i]->GetPos().z);
			D3DXVec3TransformNormal(&m_StPlayerAtrribute[i].st_vDirection, &D3DXVECTOR3(0, 0, 1), &matT1P);


			m_StPlayerAtrribute[i].st_matPlayer = matR1P * matT1P;
			m_vecCharacter[i]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[i].st_matPlayer);
		}
	}


}

void cCharacterControl::SetPlaterMod(int num)
{
	if (num == 0 && num > 2) return;
	else
		m_enmPlayerMod = (PLAYERMOD)num;

}

void cCharacterControl::AddcCharacter(IN cChef * Chef)
{
	m_vecCharacter.push_back(Chef);
}
void cCharacterControl::Booster()
{

	for (int i = 0; i < 2; i++)
	{
		if (m_StPlayerAtrribute[i].st_BisBooster)
		{
			m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed -= m_StPlayerAtrribute[i].st_fFrictional;
		}
		if (m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed <= 0.0f)
		{
			if(m_StPlayerAtrribute[i].st_BisBooster)
				m_vecCharacter[i]->GetRoot()->SetChefAnimation(CHEF_STATE_IDLE);
			m_StPlayerAtrribute[i].st_BisBooster = false;
			m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed = 0.0f;
		
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

cChef * cCharacterControl::GetControlPlayer()
{
	return m_vecCharacter[m_Bswitch];
}
