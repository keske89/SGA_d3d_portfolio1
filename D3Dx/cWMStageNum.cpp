#include "stdafx.h"
#include "cWMStageNum.h"
#include "cWorldMapObj.h"

cWMStageNum::cWMStageNum()
{
}


cWMStageNum::~cWMStageNum()
{
}

void cWMStageNum::Setup()
{
	D3DXMATRIX matS, matR, matT, matST;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(0));
	D3DXMatrixTranslation(&matT, 0, 0.0f, 0);
	matST = matS * matR* matT;


	if (m_Type == STAGENUM_0)
	{
		m_pNum = new cWorldMapObj; ((cWorldMapObj*)m_pNum)->SetFilename(_T("./map/"), _T("Map_Tile_Top.obj"), NULL);  m_pNum->SetLocalMatrix(&matST); m_pNum->Setup();
	}
	else if (m_Type == STAGENUM_1)
	{
		m_pNum = new cWorldMapObj; ((cWorldMapObj*)m_pNum)->SetFilename(_T("./map/"), _T("Digit_1.obj"), NULL);  m_pNum->SetLocalMatrix(&matST); m_pNum->Setup();
	}
	else if (m_Type == STAGENUM_2)
	{
		m_pNum = new cWorldMapObj; ((cWorldMapObj*)m_pNum)->SetFilename(_T("./map/"), _T("Digit_2.obj"), NULL);  m_pNum->SetLocalMatrix(&matST); m_pNum->Setup();
	}
	else if (m_Type == STAGENUM_3)
	{
		m_pNum = new cWorldMapObj; ((cWorldMapObj*)m_pNum)->SetFilename(_T("./map/"), _T("Digit_3.obj"), NULL);  m_pNum->SetLocalMatrix(&matST); m_pNum->Setup();
	}
	else if (m_Type == STAGENUM_4)
	{
		m_pNum = new cWorldMapObj; ((cWorldMapObj*)m_pNum)->SetFilename(_T("./map/"), _T("Digit_4.obj"), NULL);  m_pNum->SetLocalMatrix(&matST); m_pNum->Setup();
	}
	else if (m_Type == STAGENUM_5)
	{
		m_pNum = new cWorldMapObj; ((cWorldMapObj*)m_pNum)->SetFilename(_T("./map/"), _T("Digit_5.obj"), NULL);  m_pNum->SetLocalMatrix(&matST); m_pNum->Setup();
	}
	else if (m_Type == STAGENUM_6)
	{
		m_pNum = new cWorldMapObj; ((cWorldMapObj*)m_pNum)->SetFilename(_T("./map/"), _T("Digit_6.obj"), NULL);  m_pNum->SetLocalMatrix(&matST); m_pNum->Setup();
	}
	else if (m_Type == STAGENUM_DASH)
	{
		m_pNum = new cWorldMapObj; ((cWorldMapObj*)m_pNum)->SetFilename(_T("./map/"), _T("Digit_Dash.obj"), NULL);  m_pNum->SetLocalMatrix(&matST); m_pNum->Setup();
	}

}

void cWMStageNum::Update()
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_rot.y, m_rot.x, m_rot.z);

	m_matWorld = matR * matT;
}

void cWMStageNum::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pNum->Render();
}

void cWMStageNum::Release()
{
	SAFE_RELEASE(m_pNum);

}
