#include "stdafx.h"
#include "cWorldMapCar.h"

#include "cWorldMapObj.h"
#include "cWMCarPuff.h"
#include "cWMCarBody.h"


cWorldMapCar::cWorldMapCar()
	: m_Carbody(NULL)
	, m_fCarRot(0.0f)
{
	m_Bs.isPicked = false;
	m_Bs.center = m_vPosition;
	m_Bs.radius = 2;

	for (auto p : m_Puff)
	{
		p = NULL;
	}
}


cWorldMapCar::~cWorldMapCar()
{
}

void cWorldMapCar::Setup()
{
	// carbody setting
	m_Carbody = new cWMCarBody; m_Carbody->Setup();

	//car puff setting

	m_Puff[0] = new cWMCarPuff; m_Puff[0]->Setup();
	m_Puff[1] = new cWMCarPuff; m_Puff[1]->Setup();
	m_Puff[2] = new cWMCarPuff; m_Puff[2]->Setup();
	m_Puff[3] = new cWMCarPuff; m_Puff[3]->Setup();
	m_Puff[4] = new cWMCarPuff; m_Puff[4]->Setup();
	m_Puff[5] = new cWMCarPuff; m_Puff[5]->Setup();
	m_Puff[6] = new cWMCarPuff; m_Puff[6]->Setup();
	m_Puff[7] = new cWMCarPuff; m_Puff[7]->Setup();
	m_Puff[8] = new cWMCarPuff; m_Puff[8]->Setup();
	m_Puff[9] = new cWMCarPuff; m_Puff[9]->Setup();
}

void cWorldMapCar::Update()
{
	//Moving Controller update
	IMoveObject::UpdateMoving();

	//Bounding Sphere
	m_Bs.center = m_vPosition;

	m_Carbody->Update();
	D3DXMATRIX matLocal = m_Carbody->GetWorldMatrix()* m_matWorld;
	m_Carbody->setWorldMatrix(&(matLocal));

	if (this->m_isMoving)
	{

		//car puff
		for (auto p : m_Puff)
		{
			p->Update();
			D3DXMATRIX mat = p->GetWorldMatrix() * m_matWorld;
			p->setWorldMatrix(&mat);

		}
	}
}

void cWorldMapCar::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	m_Carbody->Render();

	if (this->m_isMoving)
	{
		for (auto p : m_Puff)
		{
			p->Render();
		}
	}
}

void cWorldMapCar::Release()
{
	SAFE_RELEASE(m_Carbody);
	for (auto p : m_Puff)
	{
		SAFE_RELEASE(p);
	}
}
