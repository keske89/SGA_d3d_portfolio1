#include "stdafx.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
#include "cCrate.h"
#include "cKnife.h"
#include "cPot.h"
#include "cSink.h"
#include "cCooker.h"
//delegate
#include "cCrateLid.h"

cStageObjManager::cStageObjManager()
	:m_buttonSelect(BUTTON_2)
{
}


cStageObjManager::~cStageObjManager()
{
}

void cStageObjManager::Setup()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR3 mPos(0, 0, 0);

	m_crate = new cCrate;
	m_crate->Setup(matWorld, mPos, 1);
	m_crate->GetLid()->SetDelegate(this); //Delegate Link
	m_vecObj.push_back(m_crate);

	/*m_Sink = new cSink;
	m_Sink->Setup();
	m_vecObj.push_back(m_Sink);*/

	//m_Cooker = new cCooker;
	//m_Cooker->Setup();
	//m_vecObj.push_back(m_Cooker);

}

void cStageObjManager::Update()
{
	//for (int i = 0; i < m_vecObj.size(); i++);
	//{
	//	m_vecObj[i].
	//}

	for (auto p : m_vecObj)
	{
		p->Update();
	}

	ActionControl();
}

void cStageObjManager::Render()
{
	for (auto p : m_vecObj)
	{
		p->Render();
	}
}


void cStageObjManager::DeleteObject(cIGObj* object)
{
	for (int i = 0; i < m_vecObj.size(); i++)
	{
		if (m_vecObj[i] == object)
		{
			SAFE_DELETE(m_vecObj[i]);
			m_vecObj.erase(m_vecObj.begin() + i);
			break;
		}
	}
}

void cStageObjManager::ActionControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		m_buttonSelect++;
		if (m_buttonSelect > 1) m_buttonSelect = BUTTON_1;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

		m_buttonSelect--;
		if (m_buttonSelect < 0) m_buttonSelect = BUTTON_2;
	}

	if (m_buttonSelect == BUTTON_1)
	{
		m_crate->GetLid()->SetCheck(true);
	}
	else if (m_buttonSelect == BUTTON_2)
	{
		m_crate->GetLid()->SetCheck(false);
	}
}

void cStageObjManager::OnAction(cIGObj * pSender)
{
	if (pSender == m_crate->GetLid())
	{
		//SCENEMANAGER->ChangeScene("StageMapTool");
	}
}
