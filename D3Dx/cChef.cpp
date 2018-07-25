#include "stdafx.h"
#include "cChef.h"
#include "cChefRoot.h"
#include "cCharacterControl.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
#include "cCollision.h"
// parts
#include "cChefBody.h"
#include "cChefHead.h"
#include "cChefHat.h"
#include "cChefLeftHand.h"
#include "cChefRightHand.h"
#include "cChefKnife.h"

cChef::cChef()
	: m_pRoot(NULL)
	, m_vPosition(0, 0, 0)
	, m_vdir(0, 0, 0)
	, m_vToGo(0, 0, 0)
	, m_pInven(NULL)
	, m_pDetect(NULL)
	, m_fRadius(0.5f)
	, m_eChefstate(CHEF_STATE_IDLE)
{
}


cChef::~cChef()
{
}

void cChef::SetUp(IN D3DXVECTOR3 vPos,IN cCharacterControl * _pControl)
{
	m_pControl = _pControl;
	m_vPosition = vPos;
	SetMaterial();
	cChefBody* pBody = new cChefBody;
	pBody->SetUp();
	m_pRoot = pBody;
	cChefHead* pHead = new cChefHead;
	if(m_pControl->GetPlayerMod() == PLAYERMOD::PLAYERMOD_PLAY1P)
		pHead->SetChageNum(DATABASE->GetchageChefNum1P());
	else
	{
		if (0 == (m_pControl->GetVecterCharacter(this)))
		{
			pHead->SetChageNum(DATABASE->GetchageChefNum1P());
		}
		else
		{
			pHead->SetChageNum(DATABASE->GetchageChefNum2P());
		}
	}
	pHead->SetUp();
	m_pRoot->AddChild(pHead);
	cChefHat * pHat = new cChefHat;
	pHat->SetUp();
	m_pRoot->AddChild(pHat);
	cChefLeftHand * pLHand = new cChefLeftHand;
	pLHand->SetUp();
	m_pRoot->AddChild(pLHand);
	cChefRightHand* pRHand = new cChefRightHand;
	pRHand->SetUp();
	m_pRoot->AddChild(pRHand);
	cChefKnife * pKnife = new cChefKnife;
	pKnife->SetUp();
	m_pRoot->AddChild(pKnife);
	
	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y, vPos.z);
	m_pRoot->SetParentWorldTM(&matT);

}

void cChef::Relese()
{
}

void cChef::Update()
{
	runPuffCreate();
	if (m_pInven)
	{
		D3DXVECTOR3 vtemp = m_vPosition + (m_vdir*0.7f);
		D3DXMATRIX matT, mat;
		mat = m_pRoot->GetmatLocal();
		D3DXMatrixTranslation(&matT, vtemp.x, vtemp.y+0.5f, vtemp.z);
		mat *= matT;
		m_pInven->SetWorldMatrix(mat);
		m_pInven->SetIsSet(true);
	}

	Animation(m_pRoot,m_eChefstate);

	if (m_pRoot)
		m_pRoot->Update();
	if (m_pDetect)
	{
		if (m_eChefstate == CHEF_STATE::CHEF_STATE_ACTION)
		{
			m_pStageOBJ->ObjAction(this);
		}

	}
	for (int i = 0; i < m_vecPuff.size();i++)
	{
		if (m_eChefstate == CHEF_STATE_BOOSTER_MOVE)
		{
			if(i<20)
				m_vecPuff[i]->BoomMod(m_vdir);
			else
				m_vecPuff[i]->Update();
		}
		else
			m_vecPuff[i]->Update();
	}
	for (int i = 0; i < m_vecPuff.size(); )
	{
		if (m_vecPuff[i]->Getscale() <= 0)
			runPuffDelete(i);
		else
			i++;
	}

}

void cChef::Render()
{

	g_pD3DDevice->SetMaterial(&m_stMtl);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	if (m_pRoot)
		m_pRoot->Render();
	for (int i = 0; i < m_vecPuff.size(); i++)
	{
		m_vecPuff[i]->Render();
	}
}

void cChef::SetMaterial()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
}


void cChef::runPuffCreate()
{
	if (m_eChefstate == CHEF_STATE_MOVE || m_eChefstate == CHEF_STATE_TRANCEPORT_MOVE)
	{
		cChefRunPuff * _runPuff = new cChefRunPuff;
		D3DXVECTOR3 vP = (m_vPosition - (m_vdir*0.5f));
		_runPuff->SetUp(D3DXVECTOR3(vP.x, vP.y + 0.3f, vP.z));
		m_vecPuff.push_back(_runPuff);
		if (m_vecPuff.size() > 0)
		{
			cChefRunPuff * temp ;
			for (int i = 0; i < m_vecPuff.size()-1; i++)
			{
				temp = m_vecPuff[i];
				m_vecPuff[i] = m_vecPuff[i + 1];
				m_vecPuff[i + 1] = temp;
			}

		}
	}
	else if (m_eChefstate == CHEF_STATE_BOOSTER_MOVE)
	{
		for (int i = 0; i < 20; i++)
		{
			cChefRunPuff * _runPuff = new cChefRunPuff;
			_runPuff->SetUp(m_pControl->GetAtribute(this)->st_vBooster);
			m_vecPuff.push_back(_runPuff);
		}
	}
}



void cChef::runPuffDelete(IN int num)
{
	m_vecPuff.at(num)->~cChefRunPuff();
	m_vecPuff.erase(m_vecPuff.begin() + num);
}

void cChef::OnAction(cIGObj * pSender)
{

}
