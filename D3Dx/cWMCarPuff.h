#pragma once
#include "cWMDefinition.h"
#include "IDisplayObject.h"

class cWorldMapObj;

class cWMCarPuff : public IDisplayObject
{
private:

	cWorldMapObj * m_Puff;
	float m_fPuffsize;
	float m_fPuffDis;
	float m_fPuffRot;

public:
	cWMCarPuff();
	virtual ~cWMCarPuff();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	D3DXMATRIX SetPuffAnimation();
};

