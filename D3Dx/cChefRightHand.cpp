#include "stdafx.h"
#include "cChefRightHand.h"


cChefRightHand::cChefRightHand()
{
}


cChefRightHand::~cChefRightHand()
{
}

void cChefRightHand::SetUp()
{
	m_pMesh = ObJMANAGER->GetMesh(L"Hand_Open_R #000539.obj");
	m_pTexture=g_pTextureManager->GetTexture(L"./Resources/Texture2D/DLC_Chef_Bear.png");
}
	