#include "stdafx.h"
#include "cCrateLid.h"


cCrateLid::cCrateLid()
	: m_CrateState(NORMAL)
	, m_bCheck(false)
	, m_fAnimationRot(0.0f)
	, m_bAni(false)
{
}


cCrateLid::~cCrateLid()
{
}

void cCrateLid::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	// CRATE = 10~ 
	
	//	CRATE_TOMATO = 11,
	//	CRATE_POTATO = 12,
	//	CRATE_MUSHROOM = 13,
	//	CRATE_ONION = 14,
	m_vPos = pos;
	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
 	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	m_matLocal = matT;
	m_matWorld = m_matLocal * matWorld;

	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"CrateLid_mesh.obj");
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/LidBottom_Texture.png");

	switch (lidtype)
	{
	case 14:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Onion_Texture.png");
		break;

	case 11:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Tomato_Texture.png");
		break;

	case 13:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Mushroom_Texture.png");
		break;

	case 12:
		m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Potato_Texture.png");
		break;

	default:
		break;
	}


}

void cCrateLid::Setup()
{
}

void cCrateLid::SetWorldMat(D3DXMATRIX matWorld)
{
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
	this->Action();

	if (m_bAni)
	{
		this->Animation();
	}


}


void cCrateLid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(1);


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