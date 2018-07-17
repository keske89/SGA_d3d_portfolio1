#include "stdafx.h"
#include "UIImage.h"


UIImage::UIImage(LPD3DXSPRITE pSprite)
	: iUIObject(pSprite)
	, m_pTex(NULL)
{
}

UIImage::~UIImage()
{
}

void UIImage::Render()
{
	if (m_pTex)
	{
		RECT rect;
		SetRect(&rect, 0, 0, m_size.x, m_size.y);
		//	D3DCOLOR 0-255
		//	D3DXCOLOR 0-1.0f
		m_pSprite->Draw(m_pTex, &rect, &m_pivot, &m_combinedPos, m_color);
	}

	iUIObject::Render();
}

void UIImage::RotateImage()
{
	D3DXMATRIX matR;
	D3DXMatrixRotationYawPitchRoll(&matR, m_rot.y, m_rot.x, m_rot.z);
	m_matLocal *= matR;
}

void UIImage::SetTexture(LPCTSTR filename)
{
	D3DXIMAGE_INFO imageInfo;

	m_pTex = g_pTextureManager->GetTexture(filename, &imageInfo);

	m_size.x = imageInfo.Width;
	m_size.y = imageInfo.Height;
}