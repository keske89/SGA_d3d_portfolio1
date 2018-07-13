#include "stdafx.h"
#include "cChefLeftHand.h"


cChefLeftHand::cChefLeftHand()
{
}


cChefLeftHand::~cChefLeftHand()
{
	m_pTexture->Release();
	m_pMesh->Release();
}

void cChefLeftHand::SetUp()
{
	D3DXMATRIX matS, matT, mat;
	D3DXMatrixTranslation(&matT, 0.0f, 0.05f, 0.0f);
	mat = matT;
	cObjLoader loader;
	m_pMesh = loader.LoadMesh(_T("./Resources/Mesh/Player"), _T("/Hand_Open_L1.obj"), &mat);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/DLC_Chef_Bear.png", &m_pTexture);

}

