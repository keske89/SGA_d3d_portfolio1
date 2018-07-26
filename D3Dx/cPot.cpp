#include "stdafx.h"
#include "cPot.h"
#include "cFoodObj.h"
#include "cProgressbar.h"
#include "cStageObjManager.h"
#include "cRecipe.h"


cPot::cPot()
	: m_pPgbar(NULL)
	, m_size(1)
	, m_RecipeCost(0)
	, m_nPotStatus(0)
	, m_nEffectCount(0)
{
	m_vec.clear();
	
}


cPot::~cPot()
{
	SAFE_DELETE(m_pPgbar);

	for (auto p : m_pIcon)
	{
		SAFE_DELETE(p);
	}


	for (auto e : m_vecEffect)
	{
		SAFE_DELETE(e);
	}
}

void cPot::Setup()
{
	
}

void cPot::Update()
{
	if (m_recipe)
		m_recipe->Update();

	D3DXVECTOR3 temp = m_vPos;
	temp.y = m_vPos.y - 0.05f;
	temp.z = m_vPos.z - 0.05f;

	if (m_InvenCount == 0)
	{
		m_pPgbar->Setup(m_matWorld, m_vPos, 2);
	}

	if (m_InvenCount != 0 && m_bIsAction)	// 냄비에 재료가 들어왔고 가스렌지에 올라갔고 
	{
		m_pPgbar->Update(temp, m_InvenCount);	// 프로그레스 바 업데이트를 돌린다.
		

		if (m_pPgbar->Complete() && m_InvenCount == 3)
		{
			m_recipe = new cRecipe;
			m_recipe->Setup(m_matWorld, m_RecipeCost);
			m_Inven = m_recipe;
			m_InvenCount = 0;
			m_RecipeCost = 0;
			m_nPotStatus = 2;
		}
		else
		{	
			m_nPotStatus = 0;
		}
		
	}
	
	if (m_RecipeCost !=0 && m_InvenCount == 3)
	{
		m_isFull = true;
		
	}
	else
	{
		m_isFull = false;
	
	}
	
	
	InvenToVector();

	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;
	m_player = NULL;
	m_bIsAction = false;

	//====================================================Effect용 

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		m_nPotStatus = 2;
	}
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		m_nPotStatus = 0;
		m_nEffectCount = 0;
	}

	if (m_nPotStatus == 2)
	{
		EffectSetup();
	}

	this->Effect();
	this->setIconTexture();
	this->setIconPosition();

}

void cPot::Render()
{
	//====================================================Effect용 
	DWORD prevRS;
	g_pD3DDevice->GetRenderState(D3DRS_FILLMODE, &prevRS);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXVECTOR3 dir(-1, -1, -1);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	for (int i = 0; i < m_vecEffect.size(); i++)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecEffect[i]->GetWorld());
		m_vecEffect[i]->Render();
	}
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, prevRS);
	////====================================================UIObject용
	for (auto p : m_pIcon)
	{
		p->Render();
	}

	//====================================================Effect용 
	SetLight();
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);

	if (m_pPgbar&& m_bIsAction && m_InvenCount != 0 )
	{
		m_pPgbar->Render();
	}
	
	if (m_recipe)
		m_recipe->Render();
}

void cPot::InvenToVector()
{
	if (m_Inven)
	{
		if (m_Inven->GetObjectType() == OBJECTTYPE::FOBJ_ONION ||
			m_Inven->GetObjectType() == OBJECTTYPE::FOBJ_TOMATO)
		{
			m_RecipeCost += m_Inven->GetCost();
			m_InvenCount += 1;
		}
	
		m_Inven->SetWorldMatrix(m_matLocal * m_matWorld);
	}


}


void cPot::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matLocal = matT;
	m_matWorld = matWorld;
	m_eState = OBJ_DYNAMIC;
	m_nObjectType = lidtype;
	m_pMesh = ObJMANAGER->GetMesh(L"Pot_Mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Pot_Texture.png");
	m_InvenCount = 0;

	m_pPgbar = new cProgressbar;
	m_pPgbar->Setup(m_matWorld, m_vPos, 2);

	////===========================================================UIobject
	D3DXVECTOR3 UIPos(m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXVECTOR3 UIPos1(m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXVECTOR3 UIPos2(m_vPos.x, m_vPos.y, m_vPos.z);

	auto temp = Convert3DTo2D(UIPos);
	UIPos.x = temp.x;
	UIPos.y = temp.y;
	UIPos.z = 0;
	m_pIcon[0] = new UIObject;
	m_pIcon[0]->SetPosition(UIPos);
	m_pIcon[0]->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));

	auto temp1 = Convert3DTo2D(UIPos1);
	UIPos1.x = temp1.x;
	UIPos1.y = temp1.y;
	UIPos1.z = 0;
	m_pIcon[1] = new UIObject;
	m_pIcon[1]->SetPosition(UIPos1);
	m_pIcon[1]->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));


	auto temp2 = Convert3DTo2D(UIPos2);
	UIPos2.x = temp2.x;
	UIPos2.y = temp2.y;
	UIPos2.z = 0;
	m_pIcon[2] = new UIObject;
	m_pIcon[2]->SetPosition(UIPos2);
	m_pIcon[2]->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));
	////===========================================================UIobject
}

void cPot::SetLight()
{
	if (m_player) // 플레이어 연결됐음
	{
		ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
		m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stMtl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	}
	else
	{
		ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
		m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		m_stMtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
}

void cPot::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}

void cPot::EffectSetup()
{
	if (m_nEffectCount < 1)
	{
		D3DXVECTOR3 front;
		D3DXMATRIX matY;
		D3DXMatrixRotationY(&matY, m_vDir.y);
		D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);

		D3DXVECTOR3 pos = m_vPos;
		D3DXVECTOR3 Dest = m_vPos + front * 4.0f;
		ST_EFFECT tempEffect;
		ZeroMemory(&tempEffect, sizeof(tempEffect));

		tempEffect.time = DXUtil::FRand(0.1, 0.4) + 1.0f;
		//tempEffect.isRY = true;
		//tempEffect.isRX = true;
		tempEffect.height = 2.0f;

		//TODO : 알파값도 랜덤으로, 스케일도 랜덤으로 RND써서 수정

		tempEffect.SetAlpha(DXUtil::FRand(255, 255), 0, DXUtil::FRand(255, 255));
		tempEffect.SetScale(DXUtil::FRand(0.5, 0.5), DXUtil::FRand(0.0, 0.0), DXUtil::FRand(0.5, 0.5));
		//tempEffect.SetMotorSpeed(DXUtil::FRand(1.4, 3.0), DXUtil::FRand(1.4, 3.0), DXUtil::FRand(1.4, 3.0));
		TEXTUREMANAGER->addTexture(_T("test"), _T("./Resources/ui/CookingTick.png"));
		tempEffect.tex = TEXTUREMANAGER->findTexture(_T("test"));
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
	m_nEffectCount++;
}

void cPot::Effect()
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

void cPot::setIconPosition() //Icon Texture 위치 변경하는 함수
{
	//====================================================UIObject용 
	for (auto p : m_pIcon)
	{
		p->Update();
	}
	
	D3DXVECTOR3 UIPos(m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXVECTOR3 UIPos1(m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXVECTOR3 UIPos2(m_vPos.x, m_vPos.y, m_vPos.z);


	UIPos.y += 0.0f;
	UIPos.x -= 0.5f;
	auto temp = Convert3DTo2D(UIPos);
	UIPos.x = temp.x;
	UIPos.y = temp.y;
	UIPos.z = 0;

	m_pIcon[0]->SetPosition(UIPos);


	UIPos1.y += 0.0f;
	UIPos1.x += 0.0f;
	auto temp1 = Convert3DTo2D(UIPos1);
	UIPos1.x = temp1.x;
	UIPos1.y = temp1.y;
	UIPos1.z = 0;

	m_pIcon[1]->SetPosition(UIPos1);



	UIPos2.y += 0.5f;
	UIPos2.x -= 0.5f;
	auto temp2 = Convert3DTo2D(UIPos2);
	UIPos2.x = temp2.x;
	UIPos2.y = temp2.y;
	UIPos2.z = 0;

	m_pIcon[2]->SetPosition(UIPos2);


	//====================================================UIObject용 
}

void cPot::setIconTexture() //Icon Texture 변경하는 함수
{
	for (auto p : m_pIcon)
	{
		if (m_nPotStatus == 0)
		{
			p->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/MissingIngredient_Icon.png")));
		}
		else if (m_nPotStatus == 2)
		{
			p->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Tomato_Icon.png")));
		}
		else if (m_nPotStatus ==1)
		{
			p->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/ui/Onion_Icon.png")));
		}
	}
	
}

D3DXVECTOR2 cPot::Convert3DTo2D(D3DXVECTOR3 v)
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
