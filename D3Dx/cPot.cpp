#include "stdafx.h"
#include "cPot.h"
#include "cFoodObj.h"
#include "cProgressbar.h"


cPot::cPot()
	:m_size(1)
{
	m_vecFood.clear();
}


cPot::~cPot()
{
	delete m_pPgbar;
	m_vecFood.clear();
}

void cPot::Setup()
{
	m_pMesh = ObJMANAGER->GetMesh(L"Pot_Mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Pot_Texture.png");
	m_vecFood.resize(3);
	m_pPgbar = new cProgressbar;
	m_pPgbar->Setup();

}

void cPot::Update()
{
	if (KEYMANAGER->isOnceKeyDown ('W'))
	{
		m_size += 1;
	}
	D3DXVECTOR3 temp = m_vPos;
	temp.y = m_vPos.y - 0.05f;
	temp.z = m_vPos.z - 0.05f;

	m_pPgbar->Update(temp, m_size);
	//if(m_vecFood )
}

void cPot::Render()
{
	m_pPgbar->Render();
}

void cPot::SetFood(cFoodObj* foodobject)
{
	if (foodobject->Getchopped())
	{
		
		m_vecFood.push_back(foodobject);
	}
}
