#include "stdafx.h"
#include "cTomato.h"

cTomato::cTomato()
{
}


cTomato::~cTomato()
{
}

void cTomato::Setup()
{
}

void cTomato::Update()
{
}

void cTomato::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}
