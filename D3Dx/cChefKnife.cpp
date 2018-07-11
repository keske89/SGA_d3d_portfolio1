#include "stdafx.h"
#include "cChefKnife.h"


cChefKnife::cChefKnife()
{
}


cChefKnife::~cChefKnife()
{
	m_pTexture->Release();
	m_pMesh->Release();
}

void cChefKnife::SetUp()
{
	cObjLoader loader;
	m_pMesh = ObJMANAGER->GetMesh(L"Knife.obj");
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/knife.png", &m_pTexture);
	D3DXMATRIX  matT;
	D3DXMatrixTranslation(&matT, 0, -100, 0);
	m_matLocalTM = matT;
}
