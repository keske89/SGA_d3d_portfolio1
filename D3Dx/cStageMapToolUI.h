#pragma once

#define MAX_FLOOR_TILE 22

enum eTileType
{
	TT_FLOOR,
	TT_OBJECT,
	TT_NEWOBJ,
	TT_MAX
};

enum eMenuType
{
	MT_FLOOR,
	MT_OBJECT,
	MT_NEWOBJ,
	MT_BLOCK,
	MT_OPEN,
	MT_SAVE,
	MT_LOAD,
	MT_TEXTURE1,
	MT_TEXTURE2,
	MT_TEXTURE3,
	MT_MAX
};

struct ST_UI_BUTTON
{
	wstring				wstrTexture;
	D3DXIMAGE_INFO		imageInfo;
	D3DXMATRIX			matrix;
};

class cStageMapToolUI
{
private:
	LPD3DXSPRITE		m_pSprite;
	ST_UI_BUTTON		m_stFloorTile[MAX_FLOOR_TILE];
	ST_UI_BUTTON		m_stTileSelectButton;
	ST_UI_BUTTON		m_stMenuButton[MT_MAX];
	ST_UI_BUTTON		m_stMenuSelectButton;
	D3DVIEWPORT9		VP;

	int					m_nSelectTileNum;
	int					m_nTextureNum;
	eTileType			m_eTileType;
public:
	cStageMapToolUI();
	~cStageMapToolUI();

	void Setup();
	void Update();
	void Render();

	bool SelectTile(int& num);
	bool SelectMenu(int& num);
	inline eTileType getTileType() { return m_eTileType; }
	inline wstring getTileTexture(int num) { return m_stFloorTile[num].wstrTexture; }
	inline void setTextureNum(int num) { m_nTextureNum = num; }
};

