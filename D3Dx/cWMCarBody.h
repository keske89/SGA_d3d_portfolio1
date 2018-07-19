#pragma once
#include "cWMDefinition.h"
#include "IDisplayObject.h"

class cWorldMapObj;

class cWMCarBody : public IDisplayObject
{
private:
	cWorldMapObj * m_CarBody;
	float m_fCarRot;
	float m_fCarDis;
	float m_fCarSize;
	int m_nState;

public:
	cWMCarBody();
	virtual ~cWMCarBody();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	D3DXMATRIX SetCarAnimation();
};

