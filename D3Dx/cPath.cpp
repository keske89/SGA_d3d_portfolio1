#include "stdafx.h"
#include "cPath.h"


#include "cWorldMapObj.h"

#include "cWorldStage.h"

cPath::cPath()
	:m_Type(PATH_CURVED)
	, m_pPath(NULL)
	, m_bAnimation(false)
	, m_ani(1.0f)
{
}


cPath::~cPath()
{
}

void cPath::Setup()
{
	if (m_Type == PATH_CURVED)
	{
		D3DXMATRIX matS, matT, matStraightR, matStraight;
		D3DXMatrixScaling(&matS, 5.0f, 4.0f, 5.0f);
		D3DXMatrixTranslation(&matT, 0.3f, 0, -1.4f);
		D3DXMatrixRotationY(&matStraightR, (190) * D3DX_PI / 180);
		matStraight = matS * matStraightR * matT;
		m_pPath = new cWorldMapObj; ((cWorldMapObj*)m_pPath)->SetFilename(_T("./map/"), _T("Path_120-13.obj"), _T("./map/Path_Texture.png"));  m_pPath->SetLocalMatrix(&matStraight); m_pPath->Setup();
	}
	else if (m_Type == PATH_STRAIGHT)
	{
		D3DXMATRIX matS, matStraightR, matStraight;
		D3DXMatrixScaling(&matS, 5.0f, 4.0f, 5.0f);
		D3DXMatrixRotationY(&matStraightR, 120 * D3DX_PI / 180);
		matStraight = matS * matStraightR;
		m_pPath = new cWorldMapObj; ((cWorldMapObj*)m_pPath)->SetFilename(_T("./map/"), _T("Path_Straight.obj"), _T("./map/Path_Texture.png"));  m_pPath->SetLocalMatrix(&matStraight); m_pPath->Setup();
	}
}

void cPath::Update()
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixScaling(&matS, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y - m_ani, m_vPosition.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_rot.y, m_rot.x, m_rot.z);

	m_matWorld = m_matLocal * matS * matR * matT;

	if (m_bAnimation)
	{
		this->Animation();
	}
}

void cPath::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pPath->Render();
}

void cPath::Release()
{
	SAFE_RELEASE(m_pPath);
}

void cPath::Animation()
{
	if (m_ani > 0.0f)
	{
		m_ani -= 0.01f;
	}
}

void cPath::setTrack(D3DXVECTOR3 From, D3DXVECTOR3 To)
{
	if (m_Type == PATH_STRAIGHT)
	{
		float y = 0.0f;
		float x = 0.0f;
		float length = 0.0f;
		D3DXVECTOR3 v = (To - From);
		D3DXVECTOR3 vT = ((To + From)) / 2;
		y = v.z;
		x = v.x;
		float angleY = atan2f(v.x, v.z);
		length = D3DXVec3Length(&v);

		this->setScale(&D3DXVECTOR3(1.0f, 1.0f, length / 10.0f));
		this->setRotation(&D3DXVECTOR3(0.0f, angleY, 0.0f));
		this->setPosition(&vT);
	}
	else if (m_Type == PATH_CURVED)
	{
		/*float y = 0.0f;
		float x = 0.0f;
		float length=0.0f;
		D3DXVECTOR3 v = (To - From);
		D3DXVECTOR3 vT = ((To + From)) / 2;

		length = D3DXVec3Length(&v);*/

		float y = 0.0f;
		float x = 0.0f;
		float length = 0.0f;
		D3DXVECTOR3 v = (To - From);
		y = v.z;
		x = v.x;

		float angleY = 0;

		if (y >0 && x>0)
		{
			angleY = (0) * D3DX_PI / 180;
			this->setScale(&D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			this->setRotation(&D3DXVECTOR3(0.0f, angleY, 0.0f));

		}
		else
		{
			angleY = (180) * D3DX_PI / 180;
			this->setScale(&D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			this->setRotation(&D3DXVECTOR3(0.0f, angleY, 0.0f));
		}
		//this->setScale(&D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		//this->setRotation(&D3DXVECTOR3(0.0f, angleY, 0.0f));

		D3DXVECTOR3 vT(To.x, 0, From.z);
		this->setPosition(&vT);
	}
}
