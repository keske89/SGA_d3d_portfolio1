#pragma once

#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{
public:
	enum eFontType
	{
		FT_DEFAULT,
		FT_QUEST,
	};

private:
	SINGLETONE(cFontManager);
	std::map<eFontType, LPD3DXFONT>	m_mapFont;

public:
	LPD3DXFONT GetFont(eFontType type);
	void Destroy();
};

