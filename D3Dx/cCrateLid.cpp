#include "stdafx.h"
#include "cCrateLid.h"
#include "cIGObj.h"
#include "cCrate.h"


cCrateLid::cCrateLid()
	: m_CrateState(NORMAL)
	, m_bCheck(false)
	, m_fAnimationRot(0.0f)
	, m_bAni(false)
	, m_pTexture2(NULL)
{
}


cCrateLid::~cCrateLid()
{
	delete m_crate;
	//m_pChild->~cIGObj();
}

void cCrateLid::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int objectType)
{
	// CRATE = 10~ 

	//	CRATE_TOMATO = 11,
	//	CRATE_POTATO = 12,
	//	CRATE_MUSHROOM = 13,
	//	CRATE_ONION = 14,
	D3DXVECTOR3 trans(0, -0.5f, 0);
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	m_matLocal = matT;

	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;

	m_matWorld = matWorld;

	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"CrateLid_mesh.obj");
	// 뚜겅 아래쪽 이미지
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/LidBottom_Texture.png");

	switch (objectType)
	{
	case 14:
		m_pTexture2 = g_pTextureManager->GetTexture(L"Resources/Texture2D/Onion_Texture.png");
		break;

	case 11:
		m_pTexture2 = g_pTextureManager->GetTexture(L"Resources/Texture2D/Tomato_Texture.png");
		break;

	case 13:
		m_pTexture2 = g_pTextureManager->GetTexture(L"Resources/Texture2D/Mushroom_Texture.png");
		break;

	case 12:
		m_pTexture2 = g_pTextureManager->GetTexture(L"Resources/Texture2D/Potato_Texture.png");
		break;

	default:
		break;
	}

	m_nObjectType = objectType;


	m_crate = new cCrate;
	m_crate->Setup(matWorld, pos, 11);
	this->AddChild(m_crate);
	

}

void cCrateLid::Setup()
{
}

void cCrateLid::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}

cIGObj* cCrateLid::GetInven()
{
	cIGObj* temp;

	if (m_Inven != NULL)
	{
		temp = m_Inven;
		m_Inven = NULL;
		return temp;
	}
	else
	{

	}
}



void cCrateLid::SetTexture()
{
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/LidBottom_Texture.png");
	m_aTexture[NORMAL] = g_pTextureManager->GetTexture(L"Resources/Texture2D/Mushroom_Texture.png");
	m_aTexture[COLLISIONWITHPLAYER] = g_pTextureManager->GetTexture(L"Resources/Texture2D/Tomato_Texture.png");
	m_aTexture[SELECTED] = g_pTextureManager->GetTexture(L"Resources/Texture2D/Onion_Texture.png");
}



void cCrateLid::Update()
{

	//SetTexture();
	//this->Action();
	//
	//if (m_bAni)
	//{
	//	this->Animation();
	//}
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	Inventory();

}


void cCrateLid::Render()
{
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetTexture(0, m_pTexture2);
	m_pMesh->DrawSubset(1);

	m_pChild->Render();


}

void cCrateLid::Action()
{
	if (m_bCheck)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			if (m_CrateState == COLLISIONWITHPLAYER)
			{
				m_CrateState = SELECTED;

			}
		}
		else
		{
			if (m_CrateState == SELECTED) //
			{
				//Animation용
				m_bAni = true;

				if (m_pDelegate)
					m_pDelegate->OnAction(this); //Delegate의 OnAction함수 호출 : LidType에 맞는 FoodObj를 new해준다.
			}
			m_CrateState = COLLISIONWITHPLAYER;

		}
	}
	else
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{

		}
		else
		{
			m_CrateState = NORMAL;
			m_matWorld = m_matLocal;
			m_fAnimationRot = 0.0f;
			m_bAni = false;
		}
	}
}

void cCrateLid::Animation()
{
	float f = 0.6f;
	float f2 = 1.0f - m_fAnimationRot / 45;
	if (m_fAnimationRot <= 45)
	{
		m_fAnimationRot += f;
	}
	D3DXMATRIX matR, matT;
	D3DXMatrixRotationX(&matR, m_fAnimationRot * D3DX_PI / 180);
	D3DXMatrixTranslation(&matT, 0, 0.1f - (0.1f * f2), -0.8f - (-0.8f*f2));
	m_matWorld = m_matLocal * matT* matR;

	if (m_fAnimationRot > 45)
	{
		m_matWorld = m_matLocal;
	}

}

void cCrateLid::Inventory()
{
	if (m_Inven != NULL)
	{
		D3DXMATRIX matT;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, 0, 1.0f, 0);

		m_Inven->SetWorldMatrix(matT * m_matLocal * m_matWorld);
	}

}
