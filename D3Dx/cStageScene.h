#pragma once
#include "cGameNode.h"

class cStage;
class cStageUI;
class cBackground;
class cCamera;
class cStageGrid;
class cStageObjManager;
class cChef;
class cCharacterControl;
class cCollision;

class cStageScene : public cGameNode
{
private:
	cStage*							m_pStage;
	cStageUI*						m_pStageUI;
	cBackground*					m_pBG;
	cCamera*						m_pCamera;
	cStageGrid*						m_pGrid;
	cStageObjManager*				m_pSOM;
	cChef*							m_pChef[2];
	cCharacterControl*				m_pControl;
	cCollision*						m_pCollision;

	D3DXVECTOR3						m_vecPos;				//ī�޶� ��� ������
	vector<pair<int, D3DXMATRIX>>	m_vNewObjData;
	vector<pair<int, D3DXMATRIX>>	m_vSetObjData;
	map<pair<int, int>, int>		m_mapIsBlockedData;
	D3DXVECTOR3						m_vecChefPos[2];

	bool							m_bCameraSetting;
	float							m_fCameraAngle;
	int								m_nTimer;
	bool							m_bPause;
public:
	cStageScene();
	~cStageScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Control();
};

