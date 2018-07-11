#include "stdafx.h"
#include "cChefRightHand.h"


cChefRightHand::cChefRightHand()
{
}


cChefRightHand::~cChefRightHand()
{
	m_pTexture->Release();
	m_pMesh->Release();
}

void cChefRightHand::SetUp()
{
	D3DXMATRIX matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0.07f, 0.1f, -0.05f);
	mat = matT;
	cObjLoader loader;
	m_pMesh = loader.LoadMesh(_T("./Resources/Mesh"), _T("/Hand_Open_R #000539.obj"), &mat);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"./Resources/Texture2D/DLC_Chef_Bear.png", &m_pTexture);

}
