#include "stdafx.h"
#include "cWMBorder.h"

#include "cWorldMapObj.h"

cWMBorder::cWMBorder()
{
}


cWMBorder::~cWMBorder()
{
}

void cWMBorder::Setup()
{
	D3DXMATRIX matS;
	m_scale = D3DXVECTOR3(2.0f, 1.f, 2.4f);
	D3DXMatrixScaling(&matS, m_scale.x, m_scale.y, m_scale.z);

	m_Border = new cWorldMapObj;  ((cWorldMapObj*)m_Border)->SetFilename(_T("./map/"), _T("Map_Border_mesh.obj"), _T("./map/Map_Border.png"));
	m_Border->SetLocalMatrix(&matS);
	m_Border->Setup();



}

void cWMBorder::Update()
{
}

void cWMBorder::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_Border->Render();
}

void cWMBorder::Release()
{
	SAFE_RELEASE(m_Border);
}
