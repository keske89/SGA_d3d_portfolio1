#include "stdafx.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
#include "cCrate.h"
#include "cKnife.h"
#include "cPot.h"
#include "cSink.h"
#include "cCooker.h"
#include "cBin.h"
#include "cPass.h"
#include "cPlate.h"
#include "cPlateReturnBox.h"
#include "cChoppingBoard.h"

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
	m_listObj.push_back(m_crate);

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

	for (auto p : m_listObj)
	{
		p->Update();
	}

	ActionControl();
}

void cStageObjManager::Render()
{
	for (auto p : m_listObj)
	{
		p->Render();
	}
}


void cStageObjManager::DeleteObject(std::list<cIGObj*>::iterator objectIter)
{
	SAFE_DELETE(*objectIter);
	m_listObj.erase(objectIter);

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


std::list<cIGObj*>::iterator cStageObjManager:: SetIngameObject(OBJECTTYPE objtype, D3DXMATRIX matWorld)
{

	//	CRATE_TOMATO = 11,
	//	CRATE_POTATO = 12,
	//	CRATE_MUSHROOM = 13,
	//	CRATE_ONION = 14,
	list<cIGObj*>::iterator iter;

	switch (objtype)
	{
	case CRATE_TOMATO:
		m_crate = new cCrate;
		m_crate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_TOMATO);
		iter = m_listObj.insert(m_listObj.end(), m_crate);
		return iter;
		//return 
		break;
	case CRATE_POTATO:
		m_crate = new cCrate;
		m_crate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_POTATO);
		iter = m_listObj.insert(m_listObj.end(), m_crate);
		return iter;
		break;
	case CRATE_MUSHROOM:
		m_crate = new cCrate;
		m_crate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_MUSHROOM);
		iter = m_listObj.insert(m_listObj.end(), m_crate);
		return iter;
		break;
	case CRATE_ONION:
		m_crate = new cCrate;
		m_crate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_ONION);
		iter = m_listObj.insert(m_listObj.end(), m_crate);
		return iter;
		break;
	case AOBJ_BIN:
		m_Bin = new cBin;
		m_Bin->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		iter = m_listObj.insert(m_listObj.end(), m_Bin);
		return iter;
		break;
	case AOBJ_CHOPPIGNBOARD:
		m_ChoppingBoard = new cChoppingBoard;
		m_ChoppingBoard->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		iter = m_listObj.insert(m_listObj.end(), m_ChoppingBoard);
		return iter;
		break;
	case AOBJ_COOKER:
		m_Cooker = new cCooker;
		m_Cooker->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		iter = m_listObj.insert(m_listObj.end(), m_Cooker);
		return iter;
		break;
	case AOBJ_PASS:
		m_Pass = new cPass;
		m_Pass->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		iter = m_listObj.insert(m_listObj.end(), m_Pass);
		return iter;
		break;
	case AOBJ_PLATE:
		m_Plate = new cPlate;
		m_Plate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		iter = m_listObj.insert(m_listObj.end(), m_Plate);
		return iter;
		break;
	case AOBJ_PLATERETURNBOX:
		m_PlateReturnBox = new cPlateReturnBox;
		m_PlateReturnBox->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		iter = m_listObj.insert(m_listObj.end(), m_PlateReturnBox);
		return iter;
		break;
	case AOBJ_POT:
		m_Pot = new cPot;
		m_Pot->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		iter = m_listObj.insert(m_listObj.end(), m_Pot);
		return iter;
		break;
	case AOBJ_SINK:
		m_Sink = new cSink;
		m_Sink->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		iter = m_listObj.insert(m_listObj.end(), m_Sink);
		return iter;
		break;
	case FOBJ_POTATO:
		break;
	case FOBJ_TOMATO:
		break;
	case FOBJ_MUSHROOM:
		break;
	case FOBJ_ONION:
		break;
	default:
		break;
	}
}


