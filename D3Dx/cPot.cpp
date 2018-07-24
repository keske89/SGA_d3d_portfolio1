#include "stdafx.h"
#include "cPot.h"
#include "cFoodObj.h"
#include "cProgressbar.h"
#include "cStageObjManager.h"



cPot::cPot()
	: m_pPgbar(NULL)
	, m_size(1)
	, m_RecipeCost(0)
{
	m_vec.clear();
}


cPot::~cPot()
{
	SAFE_DELETE(m_pPgbar);
}

void cPot::Setup()
{
	
}

void cPot::Update()
{
	

	D3DXVECTOR3 temp = m_vPos;
	temp.y = m_vPos.y - 0.05f;
	temp.z = m_vPos.z - 0.05f;


	if (m_vec.size() != 0 && m_bIsAction)	// 냄비에 재료가 들어왔고 가스렌지에 올라갔고 
	{
		if (!m_pPgbar)				// 프로그레스 바가 아직 없다면 만들고 
		{
			m_pPgbar = new cProgressbar;
			m_pPgbar->Setup(m_matWorld,m_vPos,2);
		}

		if (m_pPgbar)				// 프로그레스 바 있으면
		{
			if (m_bIsAction)			// Cooker에 올라가 있는 상태면
			{
				m_pPgbar->Update(temp, m_vec.size());	// 프로그레스 바 업데이트를 돌린다.
			}

			if (m_pPgbar->Complete() && m_vec.size() == 3)
			{
				//TODO : Create Food  //   food class 생성해서 이곳에서 new 를 해준다.
				for (auto p : m_vec)
				{
					
				}
				m_pPgbar->SetIsStart(false);
				m_pPgbar->Setup(m_matWorld, m_vPos,2);
			}
		}
	}

	
	
	InvenToVector();

	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;
	m_player = NULL;
	
}

void cPot::Render()
{
	SetLight();
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);

	if (m_pPgbar)
	{
		m_pPgbar->Render();
	}
	
}

void cPot::InvenToVector()
{
	if (m_Inven)
	{
		m_vec.push_back(m_Inven);
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
