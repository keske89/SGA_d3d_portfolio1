#include "stdafx.h"
#include "cChefHead.h"

cChefHead::cChefHead()
{
}


cChefHead::~cChefHead()
{
}

void cChefHead::SetUp()
{
	m_pMesh = ObJMANAGER->GetMesh(L"Chef_Bear.obj");
	m_pTexture=g_pTextureManager->GetTexture( L"./Resources/Texture2D/DLC_Chef_Bear.png");
}
