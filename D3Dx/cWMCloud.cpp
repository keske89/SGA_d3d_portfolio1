#include "stdafx.h"
#include "cWMCloud.h"

#include "cWorldMapObj.h"

cWMCloud::cWMCloud()
	: m_Cloud(NULL)
	, m_fPuffsize(1.0f)
	, m_fPuffDis(3.5f)
	, m_fPuffRot(10.0)
{
}


cWMCloud::~cWMCloud()
{
}

void cWMCloud::Setup()
{
	D3DXMATRIX matPS, matPT, matMapP;
	D3DXMatrixScaling(&matPS, 2.0f, 2.0f, 2.0f);
	D3DXMatrixTranslation(&matPT, 0, 0, 0);
	matMapP = matPS * matPT;
	//D3DXMatrixIdentity(&matMapP);

	m_Cloud = new cWorldMapObj; ((cWorldMapObj*)m_Cloud)->SetFilename(_T("./map/"), _T("Cloud.obj"), NULL); m_Cloud->SetLocalMatrix(&matMapP); m_Cloud->Setup();
}

void cWMCloud::Update()
{

	if (m_fPuffsize > 0)
	{
		D3DXMATRIX matLocal = m_matLocal * this->SetAnimation();
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

void cWMCloud::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_Cloud->Render();
}

void cWMCloud::Release()
{
	SAFE_RELEASE(m_Cloud);
}

D3DXMATRIX cWMCloud::SetAnimation()
{
	if (m_fPuffsize > 0)
	{
		m_fPuffsize -= 0.001f;
	}

	if (m_fPuffDis < 25.0f)
	{
		m_fPuffDis += 0.01f;
	}

	if (m_fPuffRot)
	{
		m_fPuffRot += 0.5;
	}

	D3DXMATRIX matS, matR, matT, matReturn;

	D3DXMatrixIdentity(&matS); D3DXMatrixIdentity(&matR); D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, m_fPuffsize, m_fPuffsize, m_fPuffsize);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + 10, m_vPosition.z - m_fPuffDis);
	D3DXMatrixRotationX(&matR, D3DXToRadian(m_fPuffRot));
	matReturn = matS * matR * matT;

	return matReturn;
}
