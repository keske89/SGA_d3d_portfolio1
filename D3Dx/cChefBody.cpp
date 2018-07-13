#include "stdafx.h"
#include "cChefBody.h"


cChefBody::cChefBody()
{
}


cChefBody::~cChefBody()
{
}

void cChefBody::SetUp()
{
	m_pMesh = ObJMANAGER->GetMesh(L"Body.obj");
	m_pTexture=g_pTextureManager->GetTexture(L"./Resources/Texture2D/Chef_Clothes_red.png");

}
