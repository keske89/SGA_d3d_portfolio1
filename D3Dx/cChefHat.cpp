#include "stdafx.h"
#include "cChefHat.h"


cChefHat::cChefHat()
{
}


cChefHat::~cChefHat()
{
}

void cChefHat::SetUp()
{
	m_pMesh = ObJMANAGER->GetMesh(L"Hat_Fancy #000039.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/Level_Title_Background.png");

}
