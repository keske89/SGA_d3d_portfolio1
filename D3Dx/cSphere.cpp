#include "stdafx.h"
#include "cSphere.h"


#include "cWorldMapCar.h"

cSphere::cSphere()
{
	m_pMesh = NULL;
	m_Bs.isPicked = false;
	m_Bs.center = m_vPosition;
	m_Bs.radius = 1;
}


cSphere::~cSphere()
{
}

void cSphere::Setup()
{
	m_pMesh = this->CreateMesh();
}

void cSphere::Update()
{
	D3DXMATRIX matS, matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_Bs.center = m_vPosition;
	m_matWorld = matT;

	this->collisionCheck();

}

void cSphere::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTexture(0, NULL);

	if (!m_Bs.isPicked)
		g_pD3DDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	else
		g_pD3DDevice->SetMaterial(&DXUtil::GREEN_MTRL);

	m_pMesh->DrawSubset(0);
}

void cSphere::Release()
{
	SAFE_RELEASE(m_pMesh);
}

LPD3DXMESH cSphere::CreateMesh()
{
	LPD3DXMESH mesh;

	if (FAILED(D3DXCreateSphere(g_pD3DDevice, 1, 50, 50, &mesh, NULL)))
		return NULL;

	LPD3DXMESH texMesh;

	if (FAILED(mesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM, ST_PNT_VERTEX::FVF, g_pD3DDevice, &texMesh)));
	mesh->Release();

	return texMesh;
}

void cSphere::collisionCheck()
{
	if (fabs(m_Bs.center.x - m_pCar->GetBS()->center.x) <= 1.0f &&
		fabs(m_Bs.center.z - m_pCar->GetBS()->center.z) <= 1.0f)
	{
		m_Bs.isPicked = true;
	}
	else
	{
		m_Bs.isPicked = false;
	}
}
