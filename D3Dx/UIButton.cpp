#include "stdafx.h"
#include "UIButton.h"
#include "UIText.h"


UIButton::UIButton(IUIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite)
	: iUIObject(pSprite)
	, m_pDelegate(pDelegate)
	, m_buttonState(NORMAL)
	, m_pText(NULL)
	, m_bCheck(false)
	, m_type(MOUSE)
{
}

UIButton::UIButton(IUIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite, int type)
	: iUIObject(pSprite)
	, m_pDelegate(pDelegate)
	, m_buttonState(NORMAL)
	, m_pText(NULL)
	, m_bCheck(false)
	, m_type(type)
{
}

UIButton::~UIButton()
{
}

void UIButton::Update()
{
	iUIObject::Update();

	if (m_type == MOUSE)
	{
		this->MouseControl();
	}
	else if (m_type == KEYBOARD)
	{
		this->KeyBoardControl();
	}
	else if (m_type == BOTH)
	{
		this->KeyBoardControl();
		this->MouseControl();
	}
}

void UIButton::Render()
{
	if (m_aTexture[m_buttonState])
	{
		RECT rect;
		SetRect(&rect, 0, 0, m_size.x, m_size.y);

		m_pSprite->Draw(m_aTexture[m_buttonState], &rect, &m_pivot, &m_combinedPos, m_color);
	}

	iUIObject::Render();
}

void UIButton::Release()
{
	SAFE_RELEASE(m_pDelegate);
	for (auto p : m_aTexture)
	{
		SAFE_RELEASE(p);
	}

	SAFE_RELEASE(m_pText);
}

void UIButton::KeyBoardControl()
{
	if (m_bCheck)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			if (m_buttonState == MOUSEOVER)
			{
				m_buttonState = SELECTED;
			}
		}
		else
		{
			if (m_buttonState == SELECTED)
			{
				if (m_pDelegate)
					m_pDelegate->OnClick(this);
			}
			m_buttonState = MOUSEOVER;
		}
	}
	else
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{

		}
		else
		{
			m_buttonState = NORMAL;
		}
	}
}

void UIButton::MouseControl()
{
	RECT rect;
	GetFinalRect(&rect);

	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	// mouse control
	if (PtInRect(&rect, mousePoint))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_buttonState == MOUSEOVER)
			{
				m_buttonState = SELECTED;
			}
		}
		else
		{
			if (m_buttonState == SELECTED)
			{
				if (m_pDelegate)
					m_pDelegate->OnClick(this);
			}
			m_buttonState = MOUSEOVER;
		}
	}
	else
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{

		}
		else
		{
			m_buttonState = NORMAL;
		}
	}
}

void UIButton::SetTexture(LPCTSTR normal, LPCTSTR mouseOver, LPCTSTR selected)
{
	D3DXIMAGE_INFO imageInfo;
	m_aTexture[NORMAL] = g_pTextureManager->GetTexture(normal, &imageInfo);
	m_aTexture[MOUSEOVER] = g_pTextureManager->GetTexture(mouseOver);
	m_aTexture[SELECTED] = g_pTextureManager->GetTexture(selected);

	m_size.x = imageInfo.Width;
	m_size.y = imageInfo.Height;
}

void UIButton::SetText(LPD3DXFONT pFont, LPCTSTR text)
{
	if (m_pText == NULL)
	{
		m_pText = new UIText(pFont, m_pSprite);
		this->AddChild(m_pText);
		m_pText->m_size = m_size;
	}

	m_pText->m_pFont = pFont;
	m_pText->m_text = text;
}
