#include "stdafx.h"
#include "cWorldMapObj.h"
#include "cWMDefinition.h"

#include "cObjLoader.h"

cWorldMapObj::cWorldMapObj()
{
	m_pMesh = NULL;
	m_Texture = NULL;
}

cWorldMapObj::~cWorldMapObj()
{
}

void cWorldMapObj::Release()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_Texture);
}

void cWorldMapObj::Setup()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, m_TextureName, &m_Texture);

	cObjLoader loader;
	if (m_fileName.IsEmpty() == false)
	{
		m_pMesh = loader.LoadMesh(m_filePath, m_fileName, &m_matLocal);
	}

	m_vPosition = D3DXVECTOR3(0, 0, 0);
}

void cWorldMapObj::Update()
{
}

void cWorldMapObj::Render()
{
	g_pD3DDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTexture(0, m_Texture);
	g_pD3DDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pMesh->DrawSubset(0);
}


