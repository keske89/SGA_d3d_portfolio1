#pragma once
#include "cGameNode.h"

class cStage;
class cCamera;
class cStageGrid;

class cStageScene : public cGameNode
{
private:
	cStage*				m_pStage;
	cCamera*			m_pCamera;
	cStageGrid*			m_pGrid;
	D3DXVECTOR3			m_vecPos;				//Ä«¸Þ¶ó ·è¾Ü Æ÷Áö¼Ç
public:
	cStageScene();
	~cStageScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Control();
};

