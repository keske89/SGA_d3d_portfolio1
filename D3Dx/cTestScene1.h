#pragma once
#include "cGameNode.h"

class cStage;
class cCamera;
class cStageGrid;
class cStageObjManager;
class cChef;
class cCharacterControl;
class cCollision;

class cTestScene1 : public cGameNode
{
private:
	cStage * m_pStage;
	cCamera*						m_pCamera;
	cStageGrid*						m_pGrid;
	cStageObjManager*				m_pSOM;
	cChef*							m_pChef[2];
	cCharacterControl*				m_pControl;
	cCollision*						m_pCollision;
	LPD3DXFONT						m_pFont;
	D3DXVECTOR3						m_vecPos;				//Ä«¸Þ¶ó ·è¾Ü Æ÷Áö¼Ç
	vector<pair<int, D3DXMATRIX>>	m_vNewObjData;
	vector<pair<int, D3DXMATRIX>>	m_vSetObjData;
	map<pair<int, int>, int>		m_mapIsBlockedData;
	D3DXVECTOR3						m_vecChefPos[2];

public:
	cTestScene1();
	~cTestScene1();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Control();
};

