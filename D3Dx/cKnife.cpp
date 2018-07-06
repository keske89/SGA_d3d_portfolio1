#include "stdafx.h"
#include "cKnife.h"


cKnife::cKnife()
{

}


cKnife::~cKnife()
{
	
}

void cKnife::Setup()
{
	m_pMesh = ObJMANAGER->GetMesh(L"Knife.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Knife.png");
}

void cKnife::Update()
{
	
	
}

void cKnife::Render()
{


}


