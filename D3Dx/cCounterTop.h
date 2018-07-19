#pragma once
#include "cActionObj.h"

class cCounterTop : public cActionObj
{
public:

public:
	cCounterTop();
	~cCounterTop();

	// cActionObj을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetLight() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int objectType) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
	void Inventory();
};

