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

	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;
}

void cPot::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);

	m_pPgbar->Render();
}

void cPot::SetFood(cFoodObj* foodobject)
{
	if (foodobject->Getchopped())
	{
		
		m_vecFood.push_back(foodobject);
	}
}

void cPot::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matWorld;
	m_pMesh = ObJMANAGER->GetMesh(L"Pot_Mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Pot_Texture.png");
	m_vecFood.resize(3);
	m_pPgbar = new cProgressbar;
	m_pPgbar->Setup();

}

void cPot::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}
