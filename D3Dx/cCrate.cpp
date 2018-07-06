#include "stdafx.h"
#include "cCrate.h"


cCrate::cCrate()
{
}


cCrate::~cCrate()
{
}

void cCrate::Setup()
{
	m_pMesh = ObJMANAGER->GetMesh(L"Crate_mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Crate.png");
}

void cCrate::Update()
{
}

void cCrate::Render()
{
}
