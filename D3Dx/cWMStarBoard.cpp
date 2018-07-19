#include "stdafx.h"
#include "cWMStarBoard.h"

#include "cSphere.h"
#include "UIController.h"

cWMStarBoard::cWMStarBoard()
	: m_nScore(3)
	, m_pStarBoard(NULL)
	, m_pSphere(NULL)
{
}

cWMStarBoard::~cWMStarBoard()
{
}

void cWMStarBoard::Release()
{
	SAFE_RELEASE(m_pStarBoard);
	SAFE_RELEASE(m_pSphere);
}

void cWMStarBoard::Setup()
{
	D3DXVECTOR3 UIPos(m_vPosition.x, m_vPosition.y, m_vPosition.z);

	auto temp = Convert3DTo2D(UIPos);
	UIPos.x = temp.x;
	UIPos.y = temp.y;
	UIPos.z = 0;

	m_pStarBoard = new UIObject; m_pStarBoard->SetPosition(UIPos);
	m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_OnionHouse_Background_Small.png")));
}

void cWMStarBoard::Update()
{
	m_pStarBoard->Update();

	D3DXVECTOR3 UIPos(m_vPosition.x, m_vPosition.y, m_vPosition.z);

	UIPos.y += 2.0f;
	UIPos.x -= 1.5f;

	auto temp = Convert3DTo2D(UIPos);
	UIPos.x = temp.x;
	UIPos.y = temp.y;
	UIPos.z = 0.0f;
	m_pStarBoard->SetPosition(UIPos);

	this->Animation(m_nScore);
}

void cWMStarBoard::Render()
{
	m_pStarBoard->Render();
}


void cWMStarBoard::Animation(int score)
{
	if (m_pSphere->getBS().isPicked) //스페어 충돌시
	{
		if (score == 0)
		{
			m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_Unavailable_Background.png")));
		}
		else if (score == 1)
		{
			m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_Availabe_Background_1.png")));
		}
		else if (score == 2)
		{
			m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_Availabe_Background_2.png")));
		}
		else if (score == 3)
		{
			m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_Availabe_Background_3.png")));
		}

	}
	else//스페어 충돌 아닐시
	{
		if (score == 0)
		{
			m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_Unavailable_Background_Small.png")));
		}
		else if (score == 1)
		{
			m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_Availabe_Background_Small_1.png")));
		}
		else if (score == 2)
		{
			m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_Availabe_Background_Small_2.png")));
		}
		else if (score == 3)
		{
			m_pStarBoard->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Map_Level_Availabe_Background_Small_3.png")));
		}

	}
}

D3DXVECTOR2 cWMStarBoard::Convert3DTo2D(D3DXVECTOR3 v)
{
	D3DXMATRIX proj, view, world;
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &proj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);
	g_pD3DDevice->GetViewport(&vp);
	D3DXMatrixIdentity(&world);
	D3DXVec3Project(&v, &v, &vp, &proj, &view, &world);
	return D3DXVECTOR2(v.x, v.y);
}
