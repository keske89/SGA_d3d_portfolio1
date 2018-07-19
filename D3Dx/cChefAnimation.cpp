#include "stdafx.h"
#include "cChefAnimation.h"
#include "cChefRoot.h"

cChefAnimation::cChefAnimation()
	: m_fRotX(0.0f)
	, m_fRotY(0.0f)
	, m_fRotZ(0.0f)
	, m_fRotDeltaX(0.05f)
	, m_fRotDeltaY(0.05f)
	, m_fRotDeltaZ(0.05f)
{
}


cChefAnimation::~cChefAnimation()
{
}

void cChefAnimation::Animation(cChefRoot * _cChefRoot)
{
	D3DXMATRIX matS, matT, matT2, matRX, matRY, matRZ, matR, matOld, matAni;

	switch (_cChefRoot->GetCHEF_STATE())
	{
	case CHEF_STATE_IDLE:
	{
		D3DXMatrixIdentity(&matOld);
		D3DXMatrixTranslation(&matT2, 3.43f, 0, 0);
		D3DXMatrixTranslation(&matT, 0, -100, 0);
		_cChefRoot->GetChild()[0]->SetmatLocal(matT2);
		_cChefRoot->GetChild()[1]->SetmatLocal(matOld);
		_cChefRoot->GetChild()[3]->SetmatLocal(matT);
		_cChefRoot->GetChild()[2]->Setmesh(ObJMANAGER->GetMesh(L"Hand_Open_R #000539.obj"));
	}
	break;
	case CHEF_STATE_MOVE:
	{
		D3DXMatrixTranslation(&matT2, 3.43f, 0, 0);
		D3DXMatrixTranslation(&matT, 0, -100, 0);
		_cChefRoot->GetChild()[0]->SetmatLocal(matT2);
		_cChefRoot->GetChild()[2]->Setmesh(ObJMANAGER->GetMesh(L"Hand_Open_R #000539.obj"));
		_cChefRoot->GetChild()[3]->SetmatLocal(matT);
		for (int i = 0; i < _cChefRoot->GetChild().size() - 1; i++)
		{
			//赣府
			if (0 == i)
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

			}
			//哭率 // 坷弗率
			else if (i == 1 || i == 2)
			{
				m_fRotX += m_fRotDeltaX;

				if (m_fRotX > D3DX_PI / 8.0f)
				{
					m_fRotX = D3DX_PI / 8.0f;
				}

				if (m_fRotX < -D3DX_PI / 8.0f)
				{
					m_fRotX = -D3DX_PI / 8.0f;
				}
				m_fRotDeltaX *= -1.0;

			}
			D3DXMatrixIdentity(&matRX);
			D3DXMatrixIdentity(&matT);
			D3DXVECTOR3 temp = _cChefRoot->GetChild()[i]->GetPos();

			D3DXMatrixRotationY(&matRY, m_fRotY);
			D3DXMatrixTranslation(&matT, temp.x, temp.y, temp.z);
			if(i == 0)
				matAni = matT2  * matRY * matT;
			else
				matAni = matRX * matRY * matT;
			_cChefRoot->GetChild()[i]->SetmatLocal(matAni);

		}
	}
	break;
	case CHEF_STATE_TRANCEPORT_IDLE:
	{
		D3DXMatrixTranslation(&matT2, 3.43f, 0, 0);
		D3DXMatrixTranslation(&matT, 0, -100, 0);
		_cChefRoot->GetChild()[0]->SetmatLocal(matT2);
		_cChefRoot->GetChild()[2]->Setmesh(ObJMANAGER->GetMesh(L"Hand_Open_R #000539.obj"));
		_cChefRoot->GetChild()[3]->SetmatLocal(matT);
		float f_tempAngle = 0;
		for (int i = 1; i < _cChefRoot->GetChild().size() - 1; i++)
		{
			//哭率
			if (1 == i)
			{
				if (m_fRotZ > 0.4f)
					m_fRotZ += 0;
				else
					m_fRotZ += m_fRotDeltaZ;
				f_tempAngle = -D3DX_PI / 2;
			}
			//坷弗率
			else if (2 == i)
			{
				if (m_fRotZ > 0.4f)
					m_fRotZ += 0;
				else
					m_fRotZ += m_fRotDeltaZ;

				f_tempAngle = D3DX_PI / 2;
			}

			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixIdentity(&matT);
			D3DXVECTOR3 temp = _cChefRoot->GetChild()[i]->GetPos();
			D3DXMatrixRotationZ(&matRZ, f_tempAngle);
			D3DXMatrixTranslation(&matT, temp.x, temp.y + 1.0f, m_fRotZ);
			if (i == 0)
				matAni = matT2;
			else
			matAni = matRZ * matT;
			_cChefRoot->GetChild()[i]->SetmatLocal(matAni);
		}
	}
	break;
	case CHEF_STATE_TRANCEPORT_MOVE:
	{
		D3DXMatrixTranslation(&matT2, 3.43f, 0, 0);
		D3DXMatrixTranslation(&matT, 0, -100, 0);
		_cChefRoot->GetChild()[0]->SetmatLocal(matT2);
		_cChefRoot->GetChild()[2]->Setmesh(ObJMANAGER->GetMesh(L"Hand_Open_R #000539.obj"));
		_cChefRoot->GetChild()[3]->SetmatLocal(matT);
		float f_tempAngle = 0;
		for (int i = 0; i < _cChefRoot->GetChild().size() - 1; i++)
		{
			if (0 == i)
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

			}
			//哭率
			else if (1 == i)
				f_tempAngle = -D3DX_PI / 2;
			//坷弗率
			else if (2 == i)
				f_tempAngle = D3DX_PI / 2;


			D3DXVECTOR3 temp = _cChefRoot->GetChild()[i]->GetPos();

			D3DXMatrixIdentity(&matRX);
			D3DXMatrixIdentity(&matRY);
			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixIdentity(&matT);
			
			D3DXMatrixRotationY(&matRY, m_fRotY);
			D3DXMatrixRotationZ(&matRZ, f_tempAngle);
			if (i == 0)
			{
				D3DXMatrixTranslation(&matT, temp.x, temp.y, temp.z);
				matAni = matT2 * matRX * matRY * matT;
			}
			else
			{
				D3DXMatrixTranslation(&matT, temp.x, temp.y+1.0f, 0.4f);
				matAni = matRZ * matT;
			}
			_cChefRoot->GetChild()[i]->SetmatLocal(matAni);
		}
	}
	break;
	case CHEF_STATE_CHOP:
	{

		m_fRotX += (m_fRotDeltaX*2.0f);
		if (m_fRotX > D3DX_PI / 2.0f)
		{
			m_fRotX = D3DX_PI / 2.0f;
			m_fRotDeltaX *= -1.0;
		}

		if (m_fRotX < -D3DX_PI / 8.0f)
		{
			m_fRotX = -D3DX_PI / 8.0f;
			m_fRotDeltaX *= -1.0;
		}

		D3DXVECTOR3 temp = _cChefRoot->GetChild()[2]->GetPos();

		D3DXMatrixRotationX(&matRX, m_fRotX);
		D3DXMatrixTranslation(&matT, temp.x+0.2f, temp.y+0.6f, temp.z);
		matAni = matRX * matT;
		_cChefRoot->GetChild()[2]->SetmatLocal(matAni);
		_cChefRoot->GetChild()[3]->SetmatLocal(matAni);
		_cChefRoot->GetChild()[2]->Setmesh(ObJMANAGER->GetMesh(L"Hand_Grip_R #010449.obj"));
	}
	break;
	case CHEF_STATE_DISHWASHING:
	{
		for (int i = 1; i <_cChefRoot->GetChild().size() - 1; i++)
		{
			//哭率
			if (1 == i)
			{
				if (m_fRotZ > 0.4f)
					m_fRotZ += 0;
				else
					m_fRotZ += m_fRotDeltaZ;


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
			}
			//坷弗率
			else if (2 == i)
			{
				if (m_fRotZ > 0.4f)
					m_fRotZ += 0;
				else
					m_fRotZ += m_fRotDeltaZ;
			}

			D3DXMatrixIdentity(&matRY);
			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixIdentity(&matT);
			D3DXVECTOR3 temp = _cChefRoot->GetChild()[i]->GetPos();
			D3DXMatrixRotationZ(&matRZ, D3DX_PI / 4);
			if (i == 1)
			{
				D3DXMatrixTranslation(&matT, temp.x, temp.y - 0.2f, m_fRotZ);
				D3DXMatrixRotationY(&matRY, m_fRotY);
			}
			else
				D3DXMatrixTranslation(&matT, temp.x + 0.5f, temp.y + 0.5f, m_fRotZ);

			matAni = matRZ * matT *matRY;
			_cChefRoot->GetChild()[i]->SetmatLocal(matAni);
		}
	}
	default:
		break;
	}
}

D3DXMATRIX * cChefAnimation::KnifeLocal()
{
	D3DXMATRIX matT;
	D3DXVECTOR3 temp = D3DXVECTOR3(0, -1000, 0);
	D3DXMatrixTranslation(&matT, temp.x, temp.y, temp.z);
	return &matT;
}
