#pragma once
#include "cGameNode.h"
//#include "iUIObject.h"

class cWorldGrid;
class cWorldMapCar;
class cSphere;
class cPath;
class cWorldTile;

class cWMCloud;

class cWorldStage;

class SampleUI;

class cCamera;

class cWorldMapScene : public cGameNode
{
private:
	LPD3DXFONT				m_pFont;

	cWorldGrid*	m_pWorldGrid;

	cWorldMapCar* m_pCar;

	cWorldStage* m_pStage[10];

	SampleUI* m_UI;

	cCamera* m_pCamera;

	cWMCloud* m_pCloud[10];

	D3DXMATRIX m_matWorld;

	BYTE _alpha;
	bool _isChangeDone;

public:
	cWorldMapScene();
	~cWorldMapScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	void setCamera(cCamera* camera) { m_pCamera = camera; }
};
