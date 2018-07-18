#include "stdafx.h"
#include "cCrateLid.h"
#include "cIGObj.h"
#include "cCrate.h"


cCrateLid::cCrateLid()
	: m_fAnimationRot(0.0f)
	, m_bAni(false)
	, m_pTexture2(NULL)
{
}


cCrateLid::~cCrateLid()
{
	delete m_crate;
	m_pChild->~cIGObj();
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
	m_eState = OBJ_STATIC;
	m_nObjectType = objectType;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;

	m_matWorld = matWorld;

	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"CrateLid_mesh.obj");
	// �Ѱ� �Ʒ��� �̹���
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/LidBottom_Texture.png");
	m_nObjectType = objectType;

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


void cCrateLid::Update()
{	
	this->Action();
	
	if (m_bAni)
	{
		this->Animation();
	}
	
	Inventory();

}


void cCrateLid::Render()
{
	
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal* m_matWorld));
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

		g_pD3DDevice->SetTexture(0, m_pTexture);
		m_pMesh->DrawSubset(0);
		g_pD3DDevice->SetTexture(0, m_pTexture2);
		m_pMesh->DrawSubset(1);

		m_pChild->Render();
}

void cCrateLid::Action()
{
	if (m_bInteraction)
	{
	
			
			

		
	}
	else
	{
		
			// �������� ����Ҷ� lid ��ǥ�� �����Ǿ������ ����߻����� �ذ� ��� ã�ƺ����ҵ�

			/*D3DXMATRIX matT;
			D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y-0.5f, m_vPos.z);
			m_matWorld = m_matLocal;
			m_fAnimationRot = 0.0f;
			m_bAni = false;*/
		
	}
}

void cCrateLid::Animation()
{
	int n = 60;								//���ڿ����� ����
	float f1 = 1.0f;						//animation �ӵ� ����
	float f2 = 1.0f - m_fAnimationRot / n;  //animation interpolation�� t�� 
	if (m_fAnimationRot <= n)
	{
		m_fAnimationRot += f1;
	}

	D3DXMATRIX matR, matT;
	D3DXMatrixRotationX(&matR, m_fAnimationRot * D3DX_PI / 180);
	D3DXMatrixTranslation(&matT, 0, 0.2f - (0.2f * f2), -0.6f - (-0.6f * f2)); //interpolation 
	m_matWorld = m_matLocal * matT * matR;

	if (m_fAnimationRot > n)
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
