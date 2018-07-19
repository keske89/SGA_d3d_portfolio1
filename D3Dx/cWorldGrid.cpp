#include "stdafx.h"
#include "cWorldGrid.h"

#include "cWMDefinition.h"
#include "cWMBorder.h"

cWorldGrid::cWorldGrid()
{
	m_Texture = NULL;
	m_Border = NULL;
}


cWorldGrid::~cWorldGrid()
{
}

void cWorldGrid::Setup()
{
	//테두리
	m_Border = new cWMBorder; m_Border->Setup();

	//하단 Mesh
	D3DXCreateTextureFromFile(g_pD3DDevice, _T("./map/maptexture.png"), &m_Texture);

	int size = 60;
	m_verticesPlane.push_back(VERTEX_TYPE_PNT(D3DXVECTOR3(-size, 0, -size), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(0, 1)));
	m_verticesPlane.push_back(VERTEX_TYPE_PNT(D3DXVECTOR3(-size, 0, size), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(0, 0)));
	m_verticesPlane.push_back(VERTEX_TYPE_PNT(D3DXVECTOR3(size, 0, -size), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(1, 1)));

	m_verticesPlane.push_back(VERTEX_TYPE_PNT(D3DXVECTOR3(size, 0, size), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(1, 0)));
	m_verticesPlane.push_back(VERTEX_TYPE_PNT(D3DXVECTOR3(size, 0, -size), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(1, 1)));
	m_verticesPlane.push_back(VERTEX_TYPE_PNT(D3DXVECTOR3(-size, 0, size), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(0, 0)));

	//Grid
	float interval = 5.0f;
	int numHalfLine = 12;
	float halfLength = interval * numHalfLine;
	D3DCOLOR c;
	float tmpInterval;
	for (int i = 1; i <= numHalfLine; ++i)
	{
		tmpInterval = interval * i;
		c = (i % 5 == 0) ? D3DCOLOR_XRGB(0, 0, 0) : D3DCOLOR_XRGB(0, 0, 0);
		m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(-halfLength, 0.01f, tmpInterval), c));
		m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(halfLength, 0.01f, tmpInterval), c));
		m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(-halfLength, 0.01f, -tmpInterval), c));
		m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(halfLength, 0.01f, -tmpInterval), c));
		m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(tmpInterval, 0.01f, -halfLength), c));
		m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(tmpInterval, 0.01f, halfLength), c));
		m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(-tmpInterval, 0.01f, -halfLength), c));
		m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(-tmpInterval, 0.01f, halfLength), c));
	}

	//X-Axis
	c = D3DCOLOR_XRGB(0, 0, 0);
	m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(-halfLength, 0.01f, 0.0f), c));
	m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(halfLength, 0.01f, 0.0f), c));

	////Y-Axis
	//c = D3DCOLOR_XRGB(0, 255, 0);
	//m_vertices.push_back(ST_PC_VERTEX(D3DXVECTOR3(0.0f, -halfLength, 0.0f), c));
	//m_vertices.push_back(ST_PC_VERTEX(D3DXVECTOR3(0.0f, halfLength, 0.0f), c));

	//Z-Axis
	c = D3DCOLOR_XRGB(0, 0, 0);
	m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(0.0f, 0.01f, -halfLength), c));
	m_vertices.push_back(VERTEX_TYPE_PC(D3DXVECTOR3(0.0f, 0.01f, halfLength), c));

}

void cWorldGrid::Update()
{
	m_Border->Update();
}

void cWorldGrid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//하단 Mesh 
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetFVF(ST_WM_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_Texture);
	g_pD3DDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, m_verticesPlane.size() / 3,
	&m_verticesPlane[0], sizeof(ST_WM_PNT_VERTEX));

	//Grid 
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetFVF(ST_WM_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vertices.size() / 2,
		&m_vertices[0], sizeof(ST_WM_PC_VERTEX));


	//테두리

	m_Border->Render();
}

void cWorldGrid::Release()
{
	SAFE_RELEASE(m_Texture);
	SAFE_RELEASE(m_Border);
}
