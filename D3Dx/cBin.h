#pragma once
#include "cActionObj.h"

class cBin : public cActionObj
{
public:
	cBin();
	~cBin();

	// cActionObj을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
	virtual void SetLight() override;
};

