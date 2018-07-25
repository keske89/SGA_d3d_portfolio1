#include "stdafx.h"
#include "cPlateReturnBox.h"
#include "cPlate.h"


cPlateReturnBox::cPlateReturnBox()
{
}


cPlateReturnBox::~cPlateReturnBox()
{
}

void cPlateReturnBox::Setup()
{
}

void cPlateReturnBox::Update()
{
	
	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;


	m_player = NULL;
	Inventory();
}

void cPlateReturnBox::Render()
{
	SetLight();
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matLocal * m_matWorld));
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}

void cPlateReturnBox::Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype)
{
	D3DXMATRIX matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 0.9f, 1.0f, 0.9f);
	m_matLocal = matS;
	m_eState = OBJ_STATIC;
	m_nObjectType = lidtype;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
	m_matWorld = matWorld;

	m_bInteraction = false;
	m_bIsUse = false;
	m_pMesh = ObJMANAGER->GetMesh(L"PlateReturnBox.obj");
	// ¶Ñ°Ï ¾Æ·¡ÂÊ ÀÌ¹ÌÁö
	m_pTexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Plate_Return.png");
}

void cPlateReturnBox::SetWorldMat(D3DXMATRIX matWorld)
{
	m_matWorld = matWorld;
	m_vPos.x = matWorld._41;
	m_vPos.y = matWorld._42;
	m_vPos.z = matWorld._43;
}

void cPlateReturnBox::SetLight()
{
	if (m_player) // ÇÃ·¹ÀÌ¾î ¿¬°áµÆÀ½
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

void cPlateReturnBox::PlateReturn()
{
	
	cPlate* m_plate = new cPlate;
	m_plate->Setup(m_matLocal * m_matWorld, m_vPos, 24);
	m_plate->SetIsUse(false);
	m_Inven = m_plate;
	
}

void cPlateReturnBox::Inventory()
{
	if (m_Inven != NULL)
	{
		D3DXMATRIX matT;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, 0, 0.45f, 0);

		m_Inven->SetWorldMatrix(matT * m_matLocal * m_matWorld);
	}
}
