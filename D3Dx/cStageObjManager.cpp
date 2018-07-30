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
#include "cPassScroll.h"
#include "cOrder.h"
#include "cOrderImage.h"



//delegate
#include "cCrateLid.h"

cStageObjManager::cStageObjManager()
	: m_buttonSelect(BUTTON_2)
	, m_player1(NULL)
	, m_player2(NULL)
{
	m_vecOrder.clear();
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
	
	SAFE_RELEASE(m_pSprite);
}

void cStageObjManager::Setup()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR3 mPos(0, 0, 0);

	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	count = 0;
	//m_pUITexture = g_pTextureManager->GetTexture(L"Resources/Texture2D/Order_Onion.png", &m_stImageInfo);

}

void cStageObjManager::Update()
{
	count++;

	//if (m_OrderRoot)
	//	m_OrderRoot->Update();

	OrderSystem();

	if (m_vecOrder.size() != NULL)
	{
		for (auto p : m_vecOrder)
		{
			p->Update();
		}
	}

	for (auto p : m_listFoodObj)
	{
		p->SetIsSet(false);

		p->Update();


		///////// 냄비 처리 ////////
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


	for (auto p : m_listObj)
	{
		
		if (p->GetInven())
		{
			p->GetInven()->SetIsSet(true);
		}
		
		p->Update();

		///////// 가스렌지 ////////

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

		//////// 쓰레기통 처리 ////////////
		if (p->GetObjectType() == AOBJ_BIN)
		{
			if (p->GetInven())
			{
				DeleteFood(p->GetInven());
				p->SetInven(NULL);
			}
		}

		if (p->GetObjectType() == AOBJ_PASS)
		{
			if (p->GetInven())
			{
				p->Destroy(p->GetInven()->GetInven());
				OnAction(p);
				OnAction(p);
				p->SetInven(NULL);
			}
		}

	}
	

	
}

void cStageObjManager::Render()
{

	if (m_vecOrder.size() != NULL)
	{
		for (auto p : m_vecOrder)
		{
			p->Render(m_pSprite);
		}
	}
		//m_OrderRoot->Render(m_pSprite);


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

void cStageObjManager::EraseOrder(int index)
{
	m_vecOrder.erase(m_vecOrder.begin() + index);

}

void cStageObjManager::OrderSystem()
{
	if (count % 500 == 0 && m_vecOrder.size() < 5)
	{
		cOrderImage* pOrderImage = new cOrderImage;
		pOrderImage->SetPosition(D3DXVECTOR3(10 + (250 * m_vecOrder.size()), 10, 0));
		
		int temp = TIMEMANAGER->getWorldTime();
		if (temp % 2 == 0)
		{
			pOrderImage->SetTexture(L"Resources/Texture2D/Order_Onion.png");
			m_vecOrder.push_back(pOrderImage);
		}
		else if (temp % 2 == 1)
		{
			pOrderImage->SetTexture(L"Resources/Texture2D/Order_Tomato.png");
			m_vecOrder.push_back(pOrderImage);
		}
		
	}

	for (int i = 0; i <m_vecOrder.size(); i++)
	{
		m_vecOrder[i]->SetPosition(D3DXVECTOR3(10 + (250 * i), 10, 0));
	}

}


void cStageObjManager::OnAction(cIGObj* pSender) //신호를 주는 객체에서 신호가 들어왔다.
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
		m_PlateReturnBox->SetInven(pSender->GetInven());
		//m_Pot->DestroyRecipe();
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

void cStageObjManager::ObjAction(cChef* pSender)
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
		///// 접시를 들고왔을때
		if (pSender->GetInven()->GetObjectType() == AOBJ_PLATE)
		{
			if (pSender->GetInven()->GetInven() == NULL)
			{
				pSender->GetInven()->SetInven(pSender->GetDetect()->GetInven()->GetInven());
				pSender->GetDetect()->GetInven()->SetInven(NULL);
			}
			
		}
		
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
		///// 접시를 들고왔을때

		if (pSender->GetDetect()->GetInven()->GetObjectType() == AOBJ_POT)
		{
			if (pSender->GetInven()->GetObjectType() == AOBJ_PLATE)
			{
				if (pSender->GetInven()->GetInven() == NULL)
				{
					pSender->GetInven()->SetInven(pSender->GetDetect()->GetInven()->GetInven());
					pSender->GetDetect()->GetInven()->SetInven(NULL);

				}

			}
		}

		// 냄비를 들고 왔을때
		else if (pSender->GetDetect()->GetInven()->GetObjectType() == AOBJ_PLATE)
		{
			if (pSender->GetInven()->GetObjectType() == AOBJ_POT)
			{
				if (pSender->GetInven()->GetInven() != NULL)
				{
					pSender->GetDetect()->GetInven()->SetInven(pSender->GetInven()->GetInven());
					pSender->GetInven()->SetInven(NULL);
				}

			}
		}
		

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
		m_Pass->SetSOM(this);
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
	case AOBJ_TABLE: // 기본
		m_Counter = new cCounterTop;
		m_Counter->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_TABLE);
		iter = m_listObj.insert(m_listObj.end(), m_Counter);
		return iter;
		break;
	case AOBJ_TABLE2: // 접시
		m_Counter = new cCounterTop;
		m_Counter->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_TABLE);
		m_Plate = new cPlate;
		m_Plate->Setup(matWorld, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43), AOBJ_PLATE);
		m_Counter->SetInven(m_Plate);
		m_listFoodObj.push_back(m_Plate);
		iter = m_listObj.insert(m_listObj.end(), m_Counter);
		return iter;
		break;
	case AOBJ_TABLE3: //도마
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


