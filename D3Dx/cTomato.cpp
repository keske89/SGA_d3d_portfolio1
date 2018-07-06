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
	m_pMesh = ObJMANAGER->GetMesh(L"Tomato_Sliced.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Tomato.png");

}

void cTomato::Update()
{
	
}

void cTomato::Render()
{
}
