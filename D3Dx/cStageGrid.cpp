#include "stdafx.h"
#include "cStageGrid.h"


cStageGrid::cStageGrid()
{
	D3DXMatrixIdentity(&m_matWorld);
}


cStageGrid::~cStageGrid()
{
}

void cStageGrid::Setup()
{
}

void cStageGrid::Update()
{
}

void cStageGrid::Render()
{
	for (int i = 0; i <= GRID_MAX; ++i)
	{
		Draw3DLine(D3DXVECTOR3(i, 0, 0), D3DXVECTOR3(i, 0, GRID_MAX), D3DCOLOR_XRGB(0, 0, 0));
		Draw3DLine(D3DXVECTOR3(0, 0, i), D3DXVECTOR3(GRID_MAX, 0, i), D3DCOLOR_XRGB(0, 0, 0));
	}
}

void cStageGrid::Draw3DLine(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DCOLOR color)
{
	ST_PC_VERTEX lines[2];
	lines[0].p = p1;
	lines[0].c = color;
	lines[1].p = p2;
	lines[1].c = color;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, lines, sizeof(ST_PC_VERTEX));
}
