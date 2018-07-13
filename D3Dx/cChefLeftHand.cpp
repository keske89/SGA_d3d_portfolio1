#include "stdafx.h"
#include "cChefLeftHand.h"


cChefLeftHand::cChefLeftHand()
{
}


cChefLeftHand::~cChefLeftHand()
{
}

void cChefLeftHand::SetUp()
{
	m_pMesh = ObJMANAGER->GetMesh(L"Hand_Open_L1.obj");
	m_pTexture=g_pTextureManager->GetTexture(L"./Resources/Texture2D/DLC_Chef_Bear.png");
}

