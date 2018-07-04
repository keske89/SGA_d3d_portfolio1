#pragma once
#include "cGameNode.h"

struct ST_TILE
{
	vector<ST_PNT_VERTEX>	vecVertex;
	D3DXMATRIX				finalMatrix;
	LPDIRECT3DTEXTURE9		texture;
};

class cCamera;
class cStageGrid;

class cStageMapTool : public cGameNode
{
private:
	cCamera*		m_pCamera;
	cStageGrid*		m_pGrid;

	map<pair<int, int>, ST_TILE> m_mapFloorTiles;
	map<pair<int, int>, ST_TILE> m_mapObjectTiles;

public:
	cStageMapTool();
	~cStageMapTool();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void AddTile(int xIndex, int yIndex);
};

