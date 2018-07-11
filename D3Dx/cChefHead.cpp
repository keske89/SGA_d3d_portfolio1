#include "stdafx.h"
#include "cChefHead.h"


cChefHead::cChefHead()
{
}


cChefHead::~cChefHead()
{
	m_pTexture->Release();
	m_pMesh->Release();
}

void cChefHead::SetUp()
{

	D3DXMATRIX matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 3.45f, 0.0f, 0.0f);
	mat = matT;
	cObjLoader loader;
	m_pMesh = loader.LoadMesh(_T("./Resources/Mesh"), _T("/Chef_Bear.obj"), &mat);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/DLC_Chef_Bear.png", &m_pTexture);
}
