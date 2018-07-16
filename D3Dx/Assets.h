#pragma once

class Assets
{
public:
	enum FontType
	{
		FontType_MAIN,
		FontType_NORMAL,
		FontType_QUEST
	};

	static void	Delete();

	/////Texture/////
private:
	static map<CString, LPDIRECT3DTEXTURE9>	m_pTextureList;
	static map<CString, D3DXIMAGE_INFO>	m_imageInfoList;
public:
	static LPDIRECT3DTEXTURE9 GetTexture(LPCTSTR filePath, D3DXIMAGE_INFO* info = NULL);
	/////Texture/////

	/////Font/////
private:
	static map<FontType, LPD3DXFONT> m_pFontList;
public:
	static LPD3DXFONT GetFont(FontType e);
	/////Font/////
};

