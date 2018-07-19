#include "stdafx.h"
#include "cWMCarBody.h"

#include "cWorldMapObj.h"

cWMCarBody::cWMCarBody()
	:m_CarBody(NULL)
	, m_fCarRot(0.0f)
	, m_fCarDis(0.0f)
	, m_fCarSize(1.0f)
	, m_nState(1)
{
}



cWMCarBody::~cWMCarBody()
{
}

void cWMCarBody::Setup()
{
	D3DXMATRIX matPS, matPT, matMapP;
	D3DXMatrixScaling(&matPS, 50.0f, 50.0f, 50.0f);
	D3DXMatrixTranslation(&matPT, 0, 0, 0);
	matMapP = matPS * matPT;
	m_CarBody = new cWorldMapObj; ((cWorldMapObj*)m_CarBody)->SetFilename(_T("./map/"), _T("Car.obj"), _T("./map/Car_Texture.png")); m_CarBody->Setup();
}

void cWMCarBody::Update()
{
	D3DXMATRIX matLocal = m_matLocal * this->SetCarAnimation();
	m_matWorld = matLocal;
}

void cWMCarBody::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_CarBody->Render();
}

void cWMCarBody::Release()
{
	SAFE_RELEASE(m_CarBody);
}

D3DXMATRIX cWMCarBody::SetCarAnimation()
{
	int n = 2;
	float f1 = 0.1; // speed;
	float f2 = 1.0f - m_fCarRot / n; //t


	m_fCarRot += m_nState * f1;

	if (m_fCarRot >= n)
	{
		m_nState *= -1;
	}
	else if (m_fCarRot <= -n)
	{
		m_nState *= -1;
	}

	D3DXMATRIX matS, matRx, matRz, matT, matReturn;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matRx);
	D3DXMatrixIdentity(&matRz);
	D3DXMatrixIdentity(&matT);
	//D3DXMatrixScaling(&matS, m_fCarSize, m_fCarSize, m_fCarSize);
	D3DXMatrixRotationX(&matRx, D3DXToRadian(m_fCarRot));
	D3DXMatrixRotationZ(&matRz, D3DXToRadian(m_fCarRot));
	//D3DXMatrixTranslation(&matT, 0, 0, -m_fCarDis);

	matReturn = matS * matRx * matRz * matT;

	return matReturn;
}
