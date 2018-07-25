#pragma once
#include "cFoodObj.h"

class UIObject;

class cOnion : public cFoodObj
{
public:
	UIObject* m_Icon;

public:
	cOnion();
	~cOnion();

	// cFoodObj을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
	virtual void SetLight() override;
	D3DXVECTOR2 Convert3DTo2D();
};

