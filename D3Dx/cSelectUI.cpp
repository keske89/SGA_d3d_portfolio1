#include "stdafx.h"
#include "cSelectUI.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UIText.h"

cSelectUI::cSelectUI()
	: m_pSprite(NULL)
	, m_pRootUI(NULL)
	, _isMod(false)
{
	for (int i = 0; i < 2; i++)
	{
		m_buttonSelect[i] = 0;
	}
	D3DXMatrixIdentity(&m_matWorld);
}


cSelectUI::~cSelectUI()
{
}

void cSelectUI::SelectControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (!_isMod)
		{
			if (m_buttonSelect[0] <= 0)
				m_buttonSelect[0] = 6;
			else
				m_buttonSelect[0]--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (!_isMod)
		{
			if (m_buttonSelect[0] >= 6)
				m_buttonSelect[0] = 0;
			else
				m_buttonSelect[0]++;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		if (_isMod)
		{
			if (m_buttonSelect[0] <= 0)
				m_buttonSelect[0] = 6;
			else
				m_buttonSelect[0]--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		if (_isMod)
		{
			if (m_buttonSelect[0] >= 6)
				m_buttonSelect[0] = 0;
			else
				m_buttonSelect[0]++;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		if (_isMod)
		{
			if (m_buttonSelect[1] <= 0)
				m_buttonSelect[1] = 6;
			else
				m_buttonSelect[1]--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		if (_isMod)
		{
			if (m_buttonSelect[1] >= 6)
				m_buttonSelect[1] = 0;
			else			   
				m_buttonSelect[1]++;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_nextScene = "StageScene";
		_isChange = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!_isMod)
		{
			_isMod = true;
		}
		else
		{
			_isMod = false;
		}
	}
}

void cSelectUI::ChangeCharater()
{
	for (int i = 0; i < 2; i++)
	{
		switch (m_buttonSelect[i])
		{
		case 0:
		{
			m_pSelectCharater[i]->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/Texture2D/Level_Character_icon_Bear.png")));
			m_pSelectCharater[i]->SetName("Level_Character_icon_Bear");

		}
		break;
		case 1:
		{
			m_pSelectCharater[i]->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/Texture2D/Level_Character_Icon_Beard.png")));
			m_pSelectCharater[i]->SetName("Level_Character_Icon_Beard");
		}
		break;
		case 2:
		{
			m_pSelectCharater[i]->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/Texture2D/Level_Character_Icon_BlackCat.png")));
			m_pSelectCharater[i]->SetName("Level_Character_Icon_BlackCat");
		}
		break;
		case 3:
		{
			m_pSelectCharater[i]->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/Texture2D/Level_Character_Icon_Boof.png")));
			m_pSelectCharater[i]->SetName("Level_Character_Icon_Boof");
		}
		break;
		case 4:
		{
			m_pSelectCharater[i]->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/Texture2D/Level_Character_Icon_Box.png")));
			m_pSelectCharater[i]->SetName("Level_Character_Icon_Box");
		}
		break;
		case 5:
		{
			m_pSelectCharater[i]->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/Texture2D/Level_Character_Icon_Buck.png")));
			m_pSelectCharater[i]->SetName("Level_Character_Icon_Box");
		}
		break;
		case 6:
		{
			m_pSelectCharater[i]->SetTexture(g_pTextureManager->GetTexture(_T("./Resources/Texture2D/Level_Character_Icon_Dino.png")));
			m_pSelectCharater[i]->SetName("Level_Character_Icon_Box");
		}
		break;
		default:
			break;
		}
	}
}

void cSelectUI::Setup()
{
	SOUNDMANAGER->addSound("셀렉씬bgm", "./Sound/아케이드 2016 - 로그인 화면.mp3", true, true);
	SOUNDMANAGER->play("셀렉씬bgm", CH_SELECTSENCEBGM, 1.0f);
	_isChange = false;
	_alpha = 0;
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	
	//배경
	UIImage* pImage = new UIImage(m_pSprite);
	m_pRootUI = pImage;
	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->SetTexture(_T("./Resources/Texture2D/Level_Select_Background.png"));
	pImage->SetName(_T("SelectBack"));
	m_pSelectCharater[0] = new UIObject; 
	m_pSelectCharater[0]->SetPosition(D3DXVECTOR3(22, 62, 0));
	m_pSelectCharater[0]->SetScale(D3DXVECTOR3(0.38f, 0.38f, 0.38f));


	m_pSelectCharater[1] = new UIObject;
	m_pSelectCharater[1]->SetPosition(D3DXVECTOR3(855, 62, 0));
	m_pSelectCharater[1]->SetScale(D3DXVECTOR3(0.38f, 0.38f, 0.38f));
	//캐릭터
	

	//비어있는 셀렉벡그라운드
	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->setPosition(&D3DXVECTOR3(-20, 50, 0));
	pImage->m_size = D3DXVECTOR2(100, 100);
	pImage->SetTexture(_T("./Resources/Texture2D/back.png"));
	pImage->SetName(_T("SelectBackBgL"));
	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->setPosition(&D3DXVECTOR3(-25, 50, 0));
	pImage->m_size = D3DXVECTOR2(100, 100);
	pImage->SetTexture(_T("./Resources/Texture2D/Level_Character_Background_Left.png"));
	pImage->SetName(_T("SelectBgL"));
	
	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->setPosition(&D3DXVECTOR3(825, 50, 0));
	pImage->m_size = D3DXVECTOR2(100, 100);
	pImage->SetTexture(_T("./Resources/Texture2D/Level_Character_Background_Left.png"));
	pImage->SetName(_T("SelectBgR"));

	//타이틀
	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->setPosition(&D3DXVECTOR3(250, 0, 0));
	pImage->m_size = D3DXVECTOR2(100, 100);
	pImage->SetTexture(_T("./Resources/Texture2D/Level_Title_Background.png"));
	pImage->SetName(_T("Level_Title"));

	
	UIText* pText0 = new UIText(g_pFontManager->GetFont(eFontType::FT_QUEST), m_pSprite);

	m_pRootUI->AddChild(pText0);
	pText0->m_text = _T("Level 1-2");
	pText0->m_size = D3DXVECTOR2(200, 50);
	pText0->setColor(D3DXCOLOR(1, 1, 1, 1));
	pText0->setPosition(&D3DXVECTOR3(550, 25, 0));
	pText0->SetName(_T("textview0"));
	
	

	//별모양 + 숫자 텍스트
	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->setPosition(&D3DXVECTOR3(450, 300, 0));
	pImage->m_size = D3DXVECTOR2(100, 100);
	pImage->SetTexture(_T("./Resources/Texture2D/Level_Star_Available.png"));
	pImage->SetName(_T("Star_Available1"));


	UIText* pText1 = new UIText(g_pFontManager->GetFont(eFontType::FT_DEFAULT), m_pSprite);

	m_pRootUI->AddChild(pText1);
	pText1->m_text = _T("....    40");
	pText1->m_size = D3DXVECTOR2(300, 50);
	pText1->setColor(D3DXCOLOR(0, 0, 0, 1));
	pText1->setPosition(&D3DXVECTOR3(550, 330, 0));
	pText1->SetName(_T("textview1"));

	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->setPosition(&D3DXVECTOR3(450, 400, 0));
	pImage->m_size = D3DXVECTOR2(100, 100);
	pImage->SetTexture(_T("./Resources/Texture2D/Level_Star_Available.png"));
	pImage->SetName(_T("Star_Available2"));

	UIText* pText2 = new UIText(g_pFontManager->GetFont(eFontType::FT_DEFAULT), m_pSprite);
	m_pRootUI->AddChild(pText2);
	pText2->m_text = _T("....    80");
	pText2->m_size = D3DXVECTOR2(300, 50);
	pText2->setColor(D3DXCOLOR(0, 0, 0, 1));
	pText2->setPosition(&D3DXVECTOR3(550, 430, 0));
	pText2->SetName(_T("textview2"));

	pImage = new UIImage(m_pSprite);
	m_pRootUI->AddChild(pImage);
	pImage->setPosition(&D3DXVECTOR3(450, 500, 0));
	pImage->m_size = D3DXVECTOR2(100, 100);
	pImage->SetTexture(_T("./Resources/Texture2D/Level_Star_Available.png"));
	pImage->SetName(_T("Star_Available3"));

	UIText* pText3 = new UIText(g_pFontManager->GetFont(eFontType::FT_DEFAULT), m_pSprite);
	m_pRootUI->AddChild(pText3);
	pText3->m_text = _T("....  160");
	pText3->m_size = D3DXVECTOR2(300, 50);
	pText3->setColor(D3DXCOLOR(0, 0, 0, 1));
	pText3->setPosition(&D3DXVECTOR3(550, 530, 0));
	pText3->SetName(_T("textview3"));

	/////단추
	UIButton* pButtonL = new UIButton(this, m_pSprite, 1);
	m_pRootUI->AddChild(pButtonL);
	pButtonL->setPosition(&D3DXVECTOR3(12, 265, 0));
	pButtonL->SetTexture(_T("./Resources/ui/arrow-btn-l-up.png.png"), _T("./Resources/ui/arrow-btn-l-over.png.png"), _T("./Resources/ui/arrow-btn-l-down.png.png"));
	pButtonL->SetName(_T("ArrowsL"));

	UIButton* pButtonR = new UIButton(this, m_pSprite, 2);
	m_pRootUI->AddChild(pButtonR);
	pButtonR->setPosition(&D3DXVECTOR3(336, 265, 0));
	pButtonR->SetTexture(_T("./Resources/ui/arrow-btn-r-up.png.png"), _T("./Resources/ui/arrow-btn-r-over.png.png"), _T("./Resources/ui/arrow-btn-r-down.png.png"));
	pButtonR->SetName(_T("ArrowsR"));


	UIButton* pButtonL2 = new UIButton(this, m_pSprite, 3);
	m_pRootUI->AddChild(pButtonL2);
	pButtonL2->setPosition(&D3DXVECTOR3(860, 265, 0));
	pButtonL2->SetTexture(_T("./Resources/ui/arrow-btn-l-up.png.png"), _T("./Resources/ui/arrow-btn-l-over.png.png"), _T("./Resources/ui/arrow-btn-l-down.png.png"));
	pButtonL2->SetName(_T("ArrowsL1"));

	UIButton* pButtonR2 = new UIButton(this, m_pSprite, 4);
	m_pRootUI->AddChild(pButtonR2);
	pButtonR2->setPosition(&D3DXVECTOR3(1184, 265, 0));
	pButtonR2->SetTexture(_T("./Resources/ui/arrow-btn-r-up.png.png"), _T("./Resources/ui/arrow-btn-r-over.png.png"), _T("./Resources/ui/arrow-btn-r-down.png.png"));
	pButtonR2->SetName(_T("ArrowsR1"));
	
}

void cSelectUI::Update()
{
	if (_isChange)
	{
		_alpha++;
		if (_alpha >= 255)
		{
			if (_nextScene == "StageScene")
			{
				SCENEMANAGER->ChangeScene("StageScene");
				SOUNDMANAGER->stop(CH_SELECTSENCEBGM);
			}
		}
	}
	else
	{
		m_pRootUI->Update();
		if (!_isMod)
		{
			m_pSelectCharater[0]->Update();
			DATABASE->SetchageChefNum1P(m_buttonSelect[0]);
			DATABASE->SetchageChefNum2P(-1);
			m_pRootUI->GetVecChild()[m_pRootUI->GetVecChild().size() - 4]->setPosition(&D3DXVECTOR3(12, 265, 0));
			m_pRootUI->GetVecChild()[m_pRootUI->GetVecChild().size() - 3]->setPosition(&D3DXVECTOR3(336, 265, 0));
		}
		else
		{
			m_pSelectCharater[0]->Update();
			DATABASE->SetchageChefNum1P(m_buttonSelect[0]);
			m_pSelectCharater[1]->Update();
			DATABASE->SetchageChefNum2P(m_buttonSelect[1]);
			m_pRootUI->GetVecChild()[m_pRootUI->GetVecChild().size() - 2]->setPosition(&D3DXVECTOR3(860, 265, 0));
			m_pRootUI->GetVecChild()[m_pRootUI->GetVecChild().size() - 1]->setPosition(&D3DXVECTOR3(1184, 265, 0));
		}
		SelectControl();
		ChangeCharater();
		
	}
}

void cSelectUI::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);

	for (int i = 0; i < m_pRootUI->GetVecChild().size(); i++)
	{
		
		if (!_isMod)
		{
			if (i<m_pRootUI->GetVecChild().size()-2)
				m_pRootUI->GetVecChild()[i]->Render();
		}
		else
			m_pRootUI->GetVecChild()[i]->Render();
	}
	m_pSprite->End();
	
	if (!_isMod)
		m_pSelectCharater[0]->Render();
	else
	{
		m_pSelectCharater[0]->Render();
		m_pSelectCharater[1]->Render();
	}
	if (_isChange)
		IMAGEMANAGER->alphaRender(_T("blackMask"), _alpha);
}

void cSelectUI::Release()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pRootUI);
}

void cSelectUI::OnClick(UIButton * pSender)
{

}
