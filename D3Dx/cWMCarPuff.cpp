#include "stdafx.h"
#include "cWMCarPuff.h"

#include "cWorldMapObj.h"

cWMCarPuff::cWMCarPuff()
	:m_Puff(NULL)
	, m_fPuffsize(1.0f)
	, m_fPuffDis(3.5f)
	, m_fPuffRot(10.0)
{
}


cWMCarPuff::~cWMCarPuff()
{
}

void cWMCarPuff::Setup()
{
	D3DXMATRIX matPS, matPT, matMapP;
	D3DXMatrixScaling(&matPS, 50.0f, 50.0f, 50.0f);
	D3DXMatrixTranslation(&matPT, 0, 0, 0);
	matMapP = matPS * matPT;
	//D3DXMatrixIdentity(&matMapP);

	m_Puff = new cWorldMapObj; ((cWorldMapObj*)m_Puff)->SetFilename(_T("./map/"), _T("RunPuff.obj"), NULL); m_Puff->SetLocalMatrix(&matMapP); m_Puff->Setup();
}

void cWMCarPuff::Update()
{
	if (m_fPuffsize > 0)
	{
		D3DXMATRIX matLocal = m_matLocal * this->SetPuffAnimation();
		m_matWorld = matLocal;
	}
	else if (m_fPuffsize <= 0)
	{
		/*m_fPuffDis = 2.5f;
		m_fPuffsize = 1.0f;*/

		m_fPuffDis = (rand() % 100 / 25.0f) + 3.5f;
		m_fPuffsize = rand() % 100 / 50.0f;
		m_fPuffRot = rand() % 360 / 15.0f;
	}
}

void cWMCarPuff::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_Puff->Render();
}

void cWMCarPuff::Release()
{
	SAFE_RELEASE(m_Puff);
}

D3DXMATRIX cWMCarPuff::SetPuffAnimation()
{
	if (m_fPuffsize > 0)
	{
		m_fPuffsize -= 0.02f;
	}

	if (m_fPuffDis < 7.0f)
	{
		m_fPuffDis += 0.1f;
	}

	if (m_fPuffRot < 360)
	{
		m_fPuffRot += 1.0;
	}

	D3DXMATRIX matS, matR, matT, matReturn;
	D3DXMatrixScaling(&matS, m_fPuffsize, m_fPuffsize, m_fPuffsize);
	D3DXMatrixTranslation(&matT, 0, 0, -m_fPuffDis);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(m_fPuffRot));
	matReturn = matS * matR*matT;

	return matReturn;
}
