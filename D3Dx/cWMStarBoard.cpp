#include "stdafx.h"
#include "cWMStarBoard.h"

#include "cSphere.h"
#include "UIController.h"

cWMStarBoard::cWMStarBoard()
	: m_nScore(3)
	, m_pStarBoard(NULL)
	, m_pSphere(NULL)
{
	TEXTUREMANAGER->addTexture(_T("파티클2"), _T("./Resources/ui/CookingTick.png"));
	PARTICLE->AddParticle("Selection",
		TEXTUREMANAGER->findTexture(_T("파티클2")),
		"./Particle/attack.ptc");
}

cWMStarBoard::~cWMStarBoard()
{
}

void cWMStarBoard::Release()
{
	SAFE_RELEASE(m_pStarBoard);
	SAFE_RELEASE(m_pSphere);

	for (auto e : m_vecEffect)
	{
		SAFE_DELETE(e);
	}

	SAFE_DELETE(m_pParticle);

}

void cWMStarBoard::EffectSetup()
{
	D3DXVECTOR3 front;
	D3DXMATRIX matY;
	D3DXMatrixRotationY(&matY, m_rot.y);
	D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, 1), &matY);

	D3DXVECTOR3 pos = m_vPosition;
	D3DXVECTOR3 Dest = m_vPosition + front * 1.0f;
	ST_EFFECT tempEffect;
	ZeroMemory(&tempEffect, sizeof(tempEffect));

	tempEffect.time = DXUtil::FRand(0.1, 0.4) + 1.0f;
	//tempEffect.isRY = true;
	//tempEffect.isRX = true;
	tempEffect.height = 3.0f;

	//TODO : 알파값도 랜덤으로, 스케일도 랜덤으로 RND써서 수정

	tempEffect.SetAlpha(DXUtil::FRand(255, 255), 0, DXUtil::FRand(255, 255));
	tempEffect.SetScale(DXUtil::FRand(1.0, 1.0), DXUtil::FRand(0.0, 0.0), DXUtil::FRand(1.0, 1.0));
	//tempEffect.SetMotorSpeed(DXUtil::FRand(1.4, 3.0), DXUtil::FRand(1.4, 3.0), DXUtil::FRand(1.4, 3.0));
	TEXTUREMANAGER->addTexture(_T("testSkill"), _T("./Resources/ui/CookingTick.png"));
	tempEffect.tex = TEXTUREMANAGER->findTexture(_T("testSkill"));
	cEffectObject* tempEFOBJ;
	tempEFOBJ = new cEffectObject;

	D3DXVECTOR3 TempDir;
	TempDir = pos - Dest;
	D3DXVec3Normalize(&TempDir, &TempDir);

	float Length = D3DXVec3Length(&(Dest - pos));

	D3DXVECTOR3 Destpos = Dest;
	Destpos.y += 0.0f;
	Destpos.x += DXUtil::FRand(0.5, 0.5);
	Destpos.z += DXUtil::FRand(0.3, 0.3);
	Destpos += TempDir * (Length * 0.3f);
	tempEFOBJ->Setup(tempEffect, Destpos);

	m_vecEffect.push_back(tempEFOBJ);
}

void cWMStarBoard::Effect()
{
	if (m_vecEffect.size() <= 0) return;

	for (int i = 0; i < m_vecEffect.size();)
	{
		if (!m_vecEffect[i]->IsFinish())
		{
			m_vecEffect[i]->Update();
			i++;
		}
		else
		{
			SAFE_DELETE(m_vecEffect[i]);
			m_vecEffect.erase(m_vecEffect.begin() + i);
		}
	}
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
	m_pParticle = PARTICLE->GetParticle("Selection");
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

	Effect();
	m_pParticle->World();
	m_pParticle->Update();
}

void cWMStarBoard::Render()
{
	m_pStarBoard->Render();


	for (int i = 0; i < m_vecEffect.size(); i++)
	{
		m_vecEffect[i]->Render();
	}

	m_pParticle->Render();
}


void cWMStarBoard::Animation(int score)
{
	if (m_pSphere->getBS().isPicked) //스페어 충돌시
	{
		EffectSetup();
		m_pParticle->SetPos(m_vPosition);
		m_pParticle->TimeReset();
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

