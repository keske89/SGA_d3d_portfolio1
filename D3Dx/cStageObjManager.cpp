#include "stdafx.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
#include "cCrateLid.h"
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
#include "cTomato.h"
#include "cCounterTop.h"
#include "cChef.h"
#include "cOnion.h"




//delegate
#include "cCrateLid.h"

cStageObjManager::cStageObjManager()
	:m_buttonSelect(BUTTON_2)
{
}


cStageObjManager::~cStageObjManager()
{
	list<cIGObj*>::iterator iter;
	for (iter = m_listObj.begin(); iter != m_listObj.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
}

void cStageObjManager::Setup()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR3 mPos(0, 0, 0);

	


	/*m_Counter = new cCounterTop;
	m_Counter->Setup(matWorld, mPos, 0);
	m_listObj.push_back(m_Counter);

	m_Tomato = new cTomato;
	m_Tomato->Setup(matWorld, mPos, 0);
	m_listObj.push_back(m_Tomato);
*/
}

void cStageObjManager::Update()
{
	//for (int i = 0; i < m_vecObj.size(); i++);
	//{
	//	m_vecObj[i].
	//}
	/*if (KEYMANAGER->isOnceKeyDown('P'))
	{

		m_crateLid->SetInven(m_Tomato);
	}*/
	//
	//if (KEYMANAGER->isOnceKeyDown('L'))
	//{
	//	m_crateLid->GetInven();
	//}

	if (m_player1 && m_player2)
	{
		for (auto p : m_listObj)
		{
			m_player1->GetPos();
			m_player2->GetPos();
		}
	}
	
	
	for (auto p : m_listObj)
	{
		p->Update();
	}

	//IsCollison();
	//ActionControl();
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
		//m_crateLid->GetLid()->SetCheck(true);
	}
	else if (m_buttonSelect == BUTTON_2)
	{
		//m_crate->GetLid()->SetCheck(false);
	}
}

void cStageObjManager::IsCollison()
{
	for (auto p : m_listObj)
	{
		if (fabs(p->GetPos().x - m_player1->GetPos().x) <= 1.0f &&
			fabs(p->GetPos().z - m_player1->GetPos().z) <= 1.0f)
		{
			p->SetInteraction(true);
		}

		else if (fabs(p->GetPos().x - m_player2->GetPos().x) <= 1.0f &&
			fabs(p->GetPos().z - m_player2->GetPos().z) <= 1.0f)
		{
			p->SetInteraction(true);
		}
		else
		{
			p->SetInteraction(false);
		}
	}
}

void cStageObjManager::OnAction(cIGObj* pSender) //신호를 주는 객체에서 신호가 들어왔다.
{
	switch (pSender->m_nObjectType)
	{
	default:
		break;
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
	{
		cCrateLid * pCrateLid = new cCrateLid;
		pCrateLid->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_TOMATO);
		cCrate* pCrate = new cCrate;
		pCrate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_TOMATO);
		pCrateLid->AddChild(pCrate);
		iter = m_listObj.insert(m_listObj.end(), pCrateLid);
		return iter;
	}
	break;
	case CRATE_POTATO:
	{
		cCrateLid * pCrateLid = new cCrateLid;
		pCrateLid->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_POTATO);
		cCrate* pCrate = new cCrate;
		pCrate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_POTATO);
		pCrateLid->AddChild(pCrate);
		iter = m_listObj.insert(m_listObj.end(), pCrateLid);
		return iter;
	}
	break;
	case CRATE_MUSHROOM:
	{
		cCrateLid * pCrateLid = new cCrateLid;
		pCrateLid->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_MUSHROOM);
		cCrate* pCrate = new cCrate;
		pCrate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_MUSHROOM);
		pCrateLid->AddChild(pCrate);
		iter = m_listObj.insert(m_listObj.end(), pCrateLid);
		return iter;
	}
	break;
	case CRATE_ONION:
	{
		cCrateLid * pCrateLid = new cCrateLid;
		pCrateLid->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_ONION);
		cCrate* pCrate = new cCrate;
		pCrate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), (int)CRATE_ONION);
		pCrateLid->AddChild(pCrate);
		iter = m_listObj.insert(m_listObj.end(), pCrateLid);
		return iter;
	}
	break;
	case AOBJ_BIN:
		m_Bin = new cBin;
		m_Bin->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_BIN);
		iter = m_listObj.insert(m_listObj.end(), m_Bin);
		return iter;
		break;
	case AOBJ_CHOPPIGNBOARD:
		m_ChoppingBoard = new cChoppingBoard;
		m_ChoppingBoard->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_CHOPPIGNBOARD);
		iter = m_listObj.insert(m_listObj.end(), m_ChoppingBoard);
		return iter;
		break;
	case AOBJ_COOKER:
		m_Cooker = new cCooker;
		m_Cooker->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_COOKER);
		iter = m_listObj.insert(m_listObj.end(), m_Cooker);
		return iter;
		break;
	case AOBJ_PASS:
		m_Pass = new cPass;
		m_Pass->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_PASS);
		iter = m_listObj.insert(m_listObj.end(), m_Pass);
		return iter;
		break;
	case AOBJ_PLATE:
		m_Plate = new cPlate;
		m_Plate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_PLATE);
		iter = m_listObj.insert(m_listObj.end(), m_Plate);
		return iter;
		break;
	case AOBJ_PLATERETURNBOX:
		m_PlateReturnBox = new cPlateReturnBox;
		m_PlateReturnBox->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_PLATERETURNBOX);
		iter = m_listObj.insert(m_listObj.end(), m_PlateReturnBox);
		return iter;
		break;
	case AOBJ_POT:
		m_Pot = new cPot;
		m_Pot->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_POT);
		iter = m_listObj.insert(m_listObj.end(), m_Pot);
		return iter;
		break;
	case AOBJ_SINK:
		m_Sink = new cSink;
		m_Sink->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_SINK);
		iter = m_listObj.insert(m_listObj.end(), m_Sink);
		return iter;
		break;
	case AOBJ_TABLE:
		m_Counter = new cCounterTop;
		m_Counter->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_TABLE);
		iter = m_listObj.insert(m_listObj.end(), m_Counter);
		return iter;
		break;
	case FOBJ_POTATO:
		
		break;
	case FOBJ_TOMATO:
		break;
	case FOBJ_MUSHROOM:
		break;
	case FOBJ_ONION:
		m_Onion = new cOnion;
		m_Onion->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), FOBJ_ONION);
		iter = m_listObj.insert(m_listObj.end(), m_Onion);
		return iter;
		break;
	default:
		break;
	}
}


