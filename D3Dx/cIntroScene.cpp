#include "stdafx.h"
#include "cIntroScene.h"

#include "UIImage.h"
#include "IDisplayObject.h"
#include "cintroUI.h"
#include "cIntroLogo.h"


cIntroScene::cIntroScene()
{
}

cIntroScene::~cIntroScene()
{
	SAFE_RELEASE(m_UI);
	SAFE_RELEASE(m_Logo);

}

void cIntroScene::Setup()
{
	m_UI = new cIntroUI(); m_UI->setPosition(&D3DXVECTOR3(0, 0, 0)); m_UI->Setup();

	m_Logo = new cIntroLogo(); m_Logo->setPosition(&D3DXVECTOR3(0, 0, 0)); m_Logo->Setup();

	IMAGEMANAGER->addImage(_T("blackMask"), _T(".\\Resources\\ui\\blackMask.png"));

}

void cIntroScene::Update()
{
	m_UI->Update();
	m_Logo->Update();
}

void cIntroScene::Render()
{
	m_UI->Render();
	m_Logo->Render();
}

void cIntroScene::Destroy()
{
}
