#include "stdafx.h"
#include "cChefHead.h"

cChefHead::cChefHead()
	:chageNum(IMAGENUM_BRAR)
{
}


cChefHead::~cChefHead()
{
}

void cChefHead::SetUp()
{
	switch (chageNum)
	{
		case IMAGENUM_BRAR:
		{
			m_pMesh = ObJMANAGER->GetMesh(L"Chef_Bear.obj");
			m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/DLC_Chef_Bear.png");
		}
		break;
		case IMAGENUM_BRARD:
		{
			m_pMesh = ObJMANAGER->GetMesh(L"Chef_Beard #010486.obj");
			m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/Beard #010254.png");
		}
		break;
		case IMAGENUM_BLACKCAT:
		{
			m_pMesh = ObJMANAGER->GetMesh(L"Chef_BlackCat #010487.obj");
			m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/Chef_Skin_Cat_Black #010303.png");
		}
		break;
		case IMAGENUM_BOOF:
		{
			m_pMesh = ObJMANAGER->GetMesh(L"Chef_Boof #010478.obj");
			m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/Boof  #010224.png");
		}
		break;
		case IMAGENUM_BOX:
		{
			m_pMesh = ObJMANAGER->GetMesh(L"Chef_Box #010481.obj");
			m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/Chef_Skin_Box #010113.png");
		}
		break;
		case IMAGENUM_BUCK:
		{
			m_pMesh = ObJMANAGER->GetMesh(L"Chef_Buck_Head #010488.obj");
			m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/Chef_Skin_Buck #010356.png");
		}
		break;
		case IMAGENUM_DINO:
		{
			m_pMesh = ObJMANAGER->GetMesh(L"Chef_Dino.obj");
			m_pTexture = g_pTextureManager->GetTexture(L"./Resources/Texture2D/DLC_Chef_Dino.png");
		}
		break;
		case IMAGENUM_DOG:
		{

		}
		break;
		default:
		break;
	}
}


