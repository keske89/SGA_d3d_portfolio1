#pragma once
#include "cGameNode.h"
#include "iUIObject.h"

class cWorldGrid;
class cWorldMapCar;
class cSphere;
class cPath;
class cWorldTile;

class cWMCloud;

class cWorldStage;

class cWMapMenu;

class cCamera;

class cWorldMapScene : public cGameNode
{
private:
	LPD3DXFONT				m_pFont;

	cWorldGrid*	m_pWorldGrid; //Grid

	cWorldMapCar* m_pCar; //Car

	cWorldStage* m_pStage[10]; //Stage Sphere + Path
	bool m_bIsStageclear[10]; //CLAER 
	int m_nStar[10]; //star

	cWMapMenu* m_UI; // UI

	cCamera* m_pCamera; //CAMERA

	cWMCloud* m_pCloud[10]; //CLOUD

	D3DXMATRIX m_matWorld;

	//INTRO TO WM
	BYTE _alpha;
	bool _isChangeDone;

	//WM TO STAGE
	BYTE _alpha1;
	bool _isChange;
	string _nextScene;

public:
	cWorldMapScene();
	~cWorldMapScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	void setCamera(cCamera* camera) { m_pCamera = camera; }
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Control();
};
