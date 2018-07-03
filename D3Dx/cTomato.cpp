#include "stdafx.h"
#include "cTomato.h"


cTomato::cTomato()
{
}


cTomato::~cTomato()
{
}

void cTomato::Setup()
{
	m_pTexture = g_pTextureManager->GetTexture(L"IngameObj/Tomato_Whole.obj");

}
