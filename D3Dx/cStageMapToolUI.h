#pragma once

#define MAX_FLOOR_TILE 22

enum eTileType
{
	TT_FLOOR,
	TT_OBJECT
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
	ST_UI_BUTTON		m_stSelectButton;
	D3DVIEWPORT9		VP;

	int					m_nSelectTileNum;
	eTileType			m_eTileType;
public:
	cStageMapToolUI();
	~cStageMapToolUI();

	void Setup();
	void Update();
	void Render();

	bool SelectTile(int& num);
	eTileType getTileType() { return m_eTileType; }
	wstring getTileTexture(int num) { return m_stFloorTile[num].wstrTexture; }
};

