#pragma once
#include "cActionObj.h"

class cCooker : public cActionObj
{
public:
	cCooker();
	~cCooker();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype);
	virtual void SetWorldMat(D3DXMATRIX matWorld);
	virtual void SetLight() override;
	void Inventory();
};