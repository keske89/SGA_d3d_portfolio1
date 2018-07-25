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
#include "cChefRoot.h"
#include "cWMDefinition.h"



//delegate
#include "cCrateLid.h"

cStageObjManager::cStageObjManager()
	: m_buttonSelect(BUTTON_2)
	, m_player1(NULL)
	, m_player2(NULL)
{
}


cStageObjManager::~cStageObjManager()
{
	list<cIGObj*>::iterator iter;
	for (iter = m_listObj.begin(); iter != m_listObj.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	for (iter = m_listFoodObj.begin(); iter != m_listFoodObj.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	
}

void cStageObjManager::Setup()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR3 mPos(0, 0, 0);

}

void cStageObjManager::Update()
{
	

	for (auto p : m_listObj)
	{
		p->GetInven()->SetIsSet(false);

		if (p->GetInven())
		{
			p->GetInven()->SetIsSet(true);
		}
		
		p->Update();

		///////// �������� ////////

		if (p->GetObjectType() == AOBJ_COOKER)
		{
			if (p->GetInven())
			{
				if (p->GetInven()->GetObjectType() == AOBJ_POT)
				{
					p->GetInven()->SetIsAction(true);
				}
			}
		}

		if ((p->GetObjectType() == AOBJ_CHOPPIGNBOARD))
		{

		}

		//////// �������� ó�� ////////////
		if (p->GetObjectType() == AOBJ_BIN)
		{
			if (p->GetInven())
			{
				DeleteFood(p->GetInven());
				p->SetInven(NULL);
			}
		}
	}
	

	for (auto p : m_listFoodObj)
	{
		
		p->Update();

				
		///////// ���� ó�� ////////
		if (p->GetObjectType() == AOBJ_POT)
		{
			if (p->GetInven())
			{
				if (p->GetInven()->GetObjectType() == (int)FOBJ_TOMATO ||
					p->GetInven()->GetObjectType() == (int)FOBJ_ONION)
				{
					DeleteFood(p->GetInven());
					p->SetInven(NULL);
				}
			}
		}
	}
}

void cStageObjManager::Render()
{
	D3DXVECTOR3 dir(-1, -1, -1);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &D3DXCOLOR(2.0f, 2.0f, 2.0f, 2.0f));
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	for (auto p : m_listObj)
	{
		p->Render();
	}

	for (auto p : m_listFoodObj)
	{
		p->Render();
	}

}


void cStageObjManager::DeleteObject(std::list<cIGObj*>::iterator objectIter)
{
	SAFE_DELETE(*objectIter);
	m_listObj.erase(objectIter);

}

void cStageObjManager::DeleteFood(cIGObj * foodPointer)
{
	list<cIGObj*>::iterator iter = m_listFoodObj.begin();
	for (; iter != m_listFoodObj.end(); ++iter)
	{
		if ((*iter) == foodPointer)
		{
			m_listFoodObj.erase(iter);
			SAFE_DELETE(foodPointer);
			break;
		}
	}
}


void cStageObjManager::OnAction(cIGObj* pSender) //��ȣ�� �ִ� ��ü���� ��ȣ�� ���Դ�.
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	switch (pSender->m_nObjectType)
	{
		// CRATE = 10~ 
		//CRATE_LID = 10,
	case CRATE_TOMATO :
		break;
	case CRATE_POTATO:
		break;
	case CRATE_MUSHROOM:
		break;
	case CRATE_ONION:
		//pSender
		m_Onion = new cOnion;
		m_Onion->Setup(pSender->GetWorldMat(), pSender->Getplayer()->GetPos(), FOBJ_ONION);
		m_listFoodObj.push_back(m_Onion);
		pSender->Getplayer()->SetInven(m_Onion);
		break;
	case AOBJ_BIN:
		break;
	case AOBJ_CHOPPIGNBOARD:
		
		break;
	case AOBJ_COOKER:
		m_Pot = new cPot;
		m_Pot->Setup(pSender->GetWorldMat(), pSender->Getplayer()->GetPos(), AOBJ_COOKER);
		m_listObj.push_back(m_Pot);
		pSender->SetInven(m_Pot);
		break;
	case AOBJ_PASS:
		break;
	case AOBJ_PLATE:
		break;
	case AOBJ_PLATERETURNBOX:
		break;
	case AOBJ_POT:
		break;
	case AOBJ_SINK:
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

void cStageObjManager::ObjAction(cChef * pSender)
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	D3DXVECTOR3	pos(0, 0, 0);

	switch (pSender->GetDetect()->GetObjectType())
	{
		// CRATE = 10~ 
		//CRATE_LID = 10,
	case CRATE_TOMATO:
		m_Tomato = new cTomato;
		m_Tomato->Setup(mat, pos, FOBJ_TOMATO);
		pSender->SetInven(m_Tomato);
		m_listFoodObj.push_back(m_Tomato);
		break;
	case CRATE_POTATO:
		//m_Potato = new cOnion;
		//m_Onion->Setup(mat, pos, FOBJ_ONION);
		//pSender->SetInven(m_Onion);
		//m_listFoodObj.push_back(m_Onion);
		break;
	case CRATE_MUSHROOM:
		break;
	case CRATE_ONION:
		m_Onion = new cOnion;
		m_Onion->Setup(mat, pos, FOBJ_ONION);
		pSender->SetInven(m_Onion);
		m_listFoodObj.push_back(m_Onion);
		break;
	case AOBJ_BIN:
		break;
	case AOBJ_CHOPPIGNBOARD:
		//pSender->GetInven() 
		break;
	case AOBJ_COOKER:
		/*m_Pot = new cPot;
		m_Pot->Setup(pSender->GetWorldMat(), pSender->Getplayer()->GetPos(), AOBJ_COOKER);
		m_listObj.push_back(m_Pot);
		pSender->SetInven(m_Pot);*/
		break;
	case AOBJ_PASS:
		break;
	case AOBJ_PLATE:
		break;
	case AOBJ_PLATERETURNBOX:
		break;
	case AOBJ_POT:

		break;
	case AOBJ_SINK:
		break;
	case AOBJ_TABLE:
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
		//pCrateLid->SetDelegate(this);
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
		m_Knife = new cKnife;
		m_Knife->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		m_ChoppingBoard->AddChild(m_Knife);
	
		return iter;
		break;
	case AOBJ_COOKER:
		m_Cooker = new cCooker;
		m_Cooker->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_COOKER);
		m_Pot = new cPot;
		m_Pot->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_POT);
		m_Cooker->SetInven(m_Pot);
		m_listFoodObj.push_back(m_Pot);
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
		iter = m_listFoodObj.insert(m_listFoodObj.end(), m_Plate);
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
		iter = m_listFoodObj.insert(m_listFoodObj.end(), m_Pot);
		return iter;
		break;
	case AOBJ_SINK:
		m_Sink = new cSink;
		m_Sink->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_SINK);
		iter = m_listObj.insert(m_listObj.end(), m_Sink);
		return iter;
		break;
	case AOBJ_TABLE: // �⺻
		m_Counter = new cCounterTop;
		m_Counter->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_TABLE);
		iter = m_listObj.insert(m_listObj.end(), m_Counter);
		return iter;
		break;
	case AOBJ_TABLE2: // ����
		m_Counter = new cCounterTop;
		m_Counter->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_TABLE);
		m_Plate = new cPlate;
		m_Plate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_PLATE);
		m_Counter->SetInven(m_Plate);
		m_listFoodObj.push_back(m_Plate);
		iter = m_listObj.insert(m_listObj.end(), m_Counter);
		return iter;
		break;
	case AOBJ_TABLE3: //����
		m_Counter = new cCounterTop;
		m_Counter->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_TABLE);
		m_ChoppingBoard = new cChoppingBoard;
		m_ChoppingBoard->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_CHOPPIGNBOARD);
		m_Knife = new cKnife;
		m_Knife->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), 0);
		m_ChoppingBoard->AddChild(m_Knife);
		m_Counter->SetInven(m_ChoppingBoard);
		m_listFoodObj.push_back(m_ChoppingBoard);
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
		//m_Onion = new cOnion;
		//m_Onion->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), FOBJ_ONION);
		//iter = m_listObj.insert(m_listObj.end(), m_Onion);
		//return iter;
		break;
	default:
		break;
	}
}


