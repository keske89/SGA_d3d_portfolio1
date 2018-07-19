#pragma once
#include "cWMDefinition.h"
#include "IDisplayObject.h"

class cWorldMapObj;

class cWMCloud : public IDisplayObject
{
private:
	cWorldMapObj * m_Cloud;
	float m_fPuffsize;
	float m_fPuffDis;
	float m_fPuffRot;

public:
	cWMCloud();
	~cWMCloud();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	D3DXMATRIX SetAnimation();
};