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
				if (m_vecCharacter[m_Bswitch]->GetCHEF_STATE() != CHEF_STATE_CHOP || m_vecCharacter[m_Bswitch]->GetCHEF_STATE() != CHEF_STATE_DISHWASHING)
					m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_IDLE);
			}
			else
			{
				m_Bswitch = true;
				if (m_vecCharacter[m_Bswitch]->GetCHEF_STATE() != CHEF_STATE_CHOP || m_vecCharacter[m_Bswitch]->GetCHEF_STATE() != CHEF_STATE_DISHWASHING)
					m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_IDLE);
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (m_vecCharacter[i]->GetDetect())
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
				{
					if (m_vecCharacter[i]->GetDetect()->GetObjectType() == 30)
						m_vecCharacter[i]->SetChefAnimation(CHEF_STATE_CHOP);
					else if (m_vecCharacter[i]->GetDetect()->GetObjectType() == 27)
						m_vecCharacter[i]->SetChefAnimation(CHEF_STATE_DISHWASHING);
				}
			}
			else
			{
				m_vecCharacter[i]->SetChefAnimation(CHEF_STATE_IDLE);
			}
		}
		if (m_vecCharacter[m_Bswitch]->GetInven())
			m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			if (!m_StPlayerAtrribute[m_Bswitch].st_BisBooster)
			{
				m_StPlayerAtrribute[m_Bswitch].st_fFrictional = 0.05f;
				m_StPlayerAtrribute[m_Bswitch].st_fCharacterBOOSTERSpeed = 0.5f;
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_BOOSTER_MOVE);
				m_StPlayerAtrribute[m_Bswitch].st_vBooster = m_vecCharacter[m_Bswitch]->GetPos() - m_vecCharacter[m_Bswitch]->GetDir();
				m_StPlayerAtrribute[m_Bswitch].st_BisBooster = true;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			//오브젝트
			if (m_vecCharacter[m_Bswitch]->GetDetect())
			{
				if (m_vecCharacter[m_Bswitch]->GetInven() == NULL)
				{
					if (m_vecCharacter[m_Bswitch]->GetDetect()->GetInven())
					{
						m_vecCharacter[m_Bswitch]->SetInven(m_vecCharacter[m_Bswitch]->GetDetect()->GetInven());
						m_vecCharacter[m_Bswitch]->GetDetect()->SetInven(NULL);
					}
					else
					{
						m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_ACTION);
					}
				}
				else
				{
					//오브젝트의 인벤이 비워져있으면!!!
					if (!m_vecCharacter[m_Bswitch]->GetDetect()->GetInven())
					{
						m_vecCharacter[m_Bswitch]->GetDetect()->SetInven(m_vecCharacter[m_Bswitch]->GetInven());
						m_vecCharacter[m_Bswitch]->SetInven(NULL);
						m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_IDLE);
					}
				}
			}
			// 타일
			else
			{
				m_vecCharacter[m_Bswitch]->SetInven(NULL);
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_IDLE);
			}
		}


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_MOVE);
			else
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);
			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

			m_StPlayerAtrribute[m_Bswitch].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			if (!m_vecCharacter[m_Bswitch]->GetInven())
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_IDLE);
			else
				m_vecCharacter[m_Bswitch]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

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
		m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_BOOSTER_MOVE);
		m_StPlayerAtrribute[0].st_BisBooster = true;
	}
	if (m_vecCharacter[0]->GetDetect())
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			if (m_vecCharacter[0]->GetDetect()->GetObjectType() == 30)
				m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_CHOP);
			else if (m_vecCharacter[0]->GetDetect()->GetObjectType() == 27)
				m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_DISHWASHING);
		}
	}
	else
	{
		m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_IDLE);
	}
	if (m_vecCharacter[0]->GetInven())
		m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (m_vecCharacter[0]->GetDetect())
		{
			if (m_vecCharacter[0]->GetInven() == NULL)
				m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_ACTION);
			else
			{
				//오브젝트의 인벤이 비워져있으면!!!
				if (!m_vecCharacter[0]->GetDetect()->GetInven())
				{
					m_vecCharacter[0]->GetDetect()->SetInven(m_vecCharacter[0]->GetInven());
					m_vecCharacter[0]->SetInven(NULL);
					m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_IDLE);
				}
			}
		}
		// 타일
		else
		{
			m_vecCharacter[0]->SetInven(NULL);
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_IDLE);
		}
	}
	if (KEYMANAGER->isStayKeyDown('F'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown('H'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('F'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('H'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[0].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown('T'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
	}
	if (KEYMANAGER->isStayKeyDown('G'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
	}
	if (KEYMANAGER->isOnceKeyUp('T'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp('G'))
	{
		if (!m_vecCharacter[0]->GetInven())
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[0]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[0].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
}
void cCharacterControl::Control2P()
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		m_StPlayerAtrribute[1].st_fFrictional = 0.05f;
		m_StPlayerAtrribute[1].st_fCharacterBOOSTERSpeed = 0.5f;
		m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_BOOSTER_MOVE);
		m_StPlayerAtrribute[1].st_BisBooster = true;
	}
	if (m_vecCharacter[1]->GetDetect())
	{
		if (KEYMANAGER->isOnceKeyDown('O'))
		{
			if (m_vecCharacter[1]->GetDetect()->GetObjectType() == 30)
				m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_CHOP);
			else if (m_vecCharacter[1]->GetDetect()->GetObjectType() == 27)
				m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_DISHWASHING);

		}
	}
	else
	{
		m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_IDLE);
	}
	if (m_vecCharacter[1]->GetInven())
		m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		if (m_vecCharacter[1]->GetDetect())
		{
			if (m_vecCharacter[1]->GetInven() == NULL)
				m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_ACTION);
			else
			{
				//오브젝트의 인벤이 비워져있으면!!!
				if (!m_vecCharacter[1]->GetDetect()->GetInven())
				{
					m_vecCharacter[1]->GetDetect()->SetInven(m_vecCharacter[1]->GetInven());
					m_vecCharacter[1]->SetInven(NULL);
					m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_IDLE);
				}
			}
		}
		// 타일
		else
		{
			m_vecCharacter[1]->SetInven(NULL);
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_IDLE);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(1, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(-1, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD4))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD6))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);
		m_StPlayerAtrribute[1].st_vDirectionX = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, 1);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_MOVE);
		else
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_MOVE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, -1);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD8))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

		m_StPlayerAtrribute[1].st_vDirectionZ = D3DXVECTOR3(0, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD5))
	{
		if (!m_vecCharacter[1]->GetInven())
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_IDLE);
		else
			m_vecCharacter[1]->SetChefAnimation(CHEF_STATE_TRANCEPORT_IDLE);

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
void cCharacterControl::Move()
{

	for (int i = 0; i < 2; i++)
	{
		
			m_vecCharacter[i]->GetDir() = m_StPlayerAtrribute[i].st_vDirectionX + m_StPlayerAtrribute[i].st_vDirectionZ;
			
			D3DXVec3Normalize(&m_StPlayerAtrribute[i].st_vDirection, &(m_StPlayerAtrribute[i].st_vDirectionX + m_StPlayerAtrribute[i].st_vDirectionZ));
			if (m_StPlayerAtrribute[i].st_vDirection == D3DXVECTOR3(0, 0, 0))
			{
				if (m_StPlayerAtrribute[i].st_fAngle == 0.0f)
					m_vecCharacter[i]->GetDir() = D3DXVECTOR3(0, 0, 1);
				//45도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI / 4)
					m_vecCharacter[i]->GetDir() = D3DXVECTOR3(1, 0, 1);
				//90도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI / 2)
					m_vecCharacter[i]->GetDir() = D3DXVECTOR3(1, 0, 0);
				//135도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI / 4 * 3)
					m_vecCharacter[i]->GetDir() = D3DXVECTOR3(1, 0, -1);
				//180도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI)
					m_vecCharacter[i]->GetDir() = D3DXVECTOR3(0, 0, -1);
				//225도
				else if (m_StPlayerAtrribute[i].st_fAngle == D3DX_PI / 4 * 5)
					m_vecCharacter[i]->GetDir() = D3DXVECTOR3(-1, 0, -1);
				//270도
				else if (m_StPlayerAtrribute[i].st_fAngle == -D3DX_PI / 2)
					m_vecCharacter[i]->GetDir() = D3DXVECTOR3(-1, 0, 0);
				//315도
				else if (m_StPlayerAtrribute[i].st_fAngle == -D3DX_PI / 4)
					m_vecCharacter[i]->GetDir() = D3DXVECTOR3(-1, 0, 1);
			}
			
			if (m_vecCharacter[i]->GetCHEF_STATE() == CHEF_STATE_BOOSTER_MOVE)
			{
				m_vecCharacter[i]->GetPos() += m_vecCharacter[i]->GetDir() *  (CharacterSpeed + m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed);
				m_vecCharacter[i]->GetToGo() = m_vecCharacter[i]->GetDir() *  (CharacterSpeed + m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed);
			}
			else
			{
				if (m_vecCharacter[i]->GetCHEF_STATE() == CHEF_STATE_IDLE || m_vecCharacter[i]->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_IDLE)
				{
					m_vecCharacter[i]->GetPos() += m_StPlayerAtrribute[i].st_vDirection *  (0.0f);
				}
				else
				{
					m_vecCharacter[i]->GetPos() += m_StPlayerAtrribute[i].st_vDirection *  (CharacterSpeed + m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed);
					m_vecCharacter[i]->GetToGo() = m_StPlayerAtrribute[i].st_vDirection *  (CharacterSpeed + m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed);
				}
			}
			
			D3DXMATRIX matR, matT;

			if (m_vecCharacter[i]->GetCHEF_STATE() == CHEF_STATE_MOVE || m_vecCharacter[i]->GetCHEF_STATE() == CHEF_STATE_TRANCEPORT_MOVE)
			{
				m_StPlayerAtrribute[i].st_fAngle = atan2f(-m_StPlayerAtrribute[i].st_vDirection.z, m_StPlayerAtrribute[i].st_vDirection.x) + D3DX_PI / 2.0f;
			}
			D3DXMatrixRotationY(&matR, m_StPlayerAtrribute[i].st_fAngle);

			D3DXMatrixTranslation(&matT, m_vecCharacter[i]->GetPos().x, m_vecCharacter[i]->GetPos().y, m_vecCharacter[i]->GetPos().z);
			D3DXVec3TransformNormal(&m_StPlayerAtrribute[i].st_vDirection, &D3DXVECTOR3(0, 0, 1), &matT);


			m_StPlayerAtrribute[i].st_matPlayer = matR * matT;
			m_vecCharacter[i]->GetRoot()->SetParentWorldTM(&m_StPlayerAtrribute[i].st_matPlayer);
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
				m_vecCharacter[i]->SetChefAnimation(CHEF_STATE_IDLE);
			m_StPlayerAtrribute[i].st_BisBooster = false;
			m_StPlayerAtrribute[i].st_fCharacterBOOSTERSpeed = 0.0f;
		
		}
	}
}

cChef * cCharacterControl::GetControlPlayer()
{
	return m_vecCharacter[m_Bswitch];
}
