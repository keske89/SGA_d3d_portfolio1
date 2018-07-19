#pragma once
#include "IMoveObject.h"
#include "cWMDefinition.h"

class cWMCarPuff;
class cWMCarBody;

class cWMBorder;

class cWorldMapCar : public IMoveObject
{
private:

	cWMCarBody* m_Carbody;
	cWMCarPuff* m_Puff[10];

	float m_fCarRot;

	BoundingSphere m_Bs;

	cWMBorder* m_Border;

public:
	cWorldMapCar();
	virtual ~cWorldMapCar();


	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	BoundingSphere* GetBS() { return &m_Bs; }

	void setBorder(cWMBorder* border) { m_Border = border; }
};

