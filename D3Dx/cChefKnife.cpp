#include "stdafx.h"
#include "cChefKnife.h"


cChefKnife::cChefKnife()
{
}


cChefKnife::~cChefKnife()
{
}

void cChefKnife::SetUp()
{
	cObjLoader loader;
	m_pMesh = ObJMANAGER->GetMesh(L"Knife.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/knife.png");
	D3DXMATRIX  matT;
	D3DXMatrixTranslation(&matT, 0, -100, 0);
	m_matLocalTM = matT;
}
