#include "stdafx.h"
#include "cChefBody.h"


cChefBody::cChefBody()
{
}


cChefBody::~cChefBody()
{
	m_pTexture->Release();
}

void cChefBody::SetUp()
{
	cObjLoader loader;
	m_pMesh = loader.LoadMesh(_T("./Resources/Mesh"), _T("/Body.obj"),NULL);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/Chef_Clothes_red.png", &m_pTexture);
}
