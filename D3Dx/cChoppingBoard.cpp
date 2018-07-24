#include "stdafx.h"
#include "cChoppingBoard.h"
#include "cProgressbar.h"
#include "cFoodObj.h"

cChoppingBoard::cChoppingBoard()
	:m_pPgbar(NULL)
{
}


cChoppingBoard::~cChoppingBoard()
{
	SAFE_DELETE(m_pPgbar);
}

void cChoppingBoard::Setup()
{
}

void cChoppingBoard::Update()
{
	
	//m_bIsAction = false;
	
	D3DXVECTOR3 temp = m_vPos;
	temp.y = m_vPos.y - 0.05f;
	temp.z = m_vPos.z - 0.05f;

	if (m_player == NULL || m_Inven == NULL) // 플레이어 연결이 없거나 인벤이 비어있으면
	{
		m_bIsAction = false; // 동작상태를 꺼라
	}

	if (m_Inven == NULL)
	{
		if (m_pPgbar)
		{
			m_pPgbar->Setup(m_matWorld, m_vPos);
			m_pPgbar->SetIsStart(false);
		}
	}

	if (m_Inven != NULL)	// 재료가 들어왔고
	{
		if (!m_pPgbar)		// 프로그레스 바가 아직 없다면 만들고 
		{
			m_pPgbar = new cProgressbar;
			m_pPgbar->Setup(m_matWorld, m_vPos);
			
		}
		if (m_pPgbar)				// 프로그레스 바 있으면
		{
			if (m_bIsAction && m_Inven->Getchopped() == false)		// 동작상태가 on 이고 썰리지 않은상태면 
			{
				m_pPgbar->Update(D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43), m_size);	// 프로그레스 바 업데이트를 돌린다.
			}
		}

	}
		
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	Inventory();

}

void cChoppingBoard::Render()
{
	SetLight();
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal *m_matWorld));
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	m_pMesh->DrawSubset(0);

	if (!m_bIsAction)
	{
		m_pChild->Render();
	}

	if (m_pPgbar)
	{
		m_pPgbar->Render();
	}
}
	

void cChoppingBoard::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXMATRIX matR, matT;
	
	D3DXVECTOR3 v(1.0f, 0, 0);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 0.1f, 0);
	D3DXMatrixRotationAxis(&matR, &v, (float)3.14 * 0.5f);
	m_size = 4;
	m_eState = OBJ_STATIC;
	m_nObjectType = lidtype;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matLocal = matR* matT;
	m_matWorld = matWorld;
	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"Chopping_Board.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/ChoppingBoard.png");
}

void cChoppingBoard::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld =  matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}

void cChoppingBoard::SetLight()
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

void cChoppingBoard::Inventory()
{
	if (m_Inven != NULL)
	{
		D3DXMATRIX matT;
		D3DXMatrixIdentity(&matT);
		//D3DXMatrixTranslation(&matT, -1.0f , 1.0f, 0);

		m_Inven->SetWorldMatrix(m_matWorld);

		
		if (m_pPgbar->Complete())
		{
			//cFoodObj* inven = (cFoodObj*)m_Inven;
			//inven->Setchopped(true);
			m_Inven->Setchopped(true);
			
			// m_pPgbar->~cProgressbar();
			//m_pPgbar->Setup(m_matWorld, m_vPos);
		}
	}
}
