#pragma once
#include "cGameNode.h"
#include "cRay.h"

struct ST_TILE
{
	vector<ST_PNT_VERTEX>	vecVertex;
	D3DXMATRIX				matFinal;
	wstring					wstrTexture;
};

class cCamera;
class cStageGrid;
class cStageMapToolUI;

class cStageMapTool : public cGameNode
{
private:
	cCamera * m_pCamera;
	cStageGrid*							m_pGrid;
	cStageMapToolUI*						m_pUI;
	D3DXVECTOR3						m_vecPos;
	D3DXMATRIX						m_matTileRot;
	D3DXMATRIX						m_matTileTrans;
	ST_TILE							m_stFloorTileTemplate;

	int								m_nTextureNum;
	int								m_nIndexX;
	int								m_nIndexZ;
	float							m_fRotAngle;

	map<pair<int, int>, ST_TILE>	m_mapFloorTiles;
	map<pair<int, int>, ST_TILE>::iterator	m_iterFloorTiles;
	map<pair<int, int>, ST_TILE>	m_mapObjectTiles;

public:
	cStageMapTool();
	~cStageMapTool();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Control();
};

