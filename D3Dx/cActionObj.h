#pragma once
#include "cIGObj.h"

class cActionObj : public cIGObj
{
public:
	cActionObj();
	virtual ~cActionObj();

	virtual void Setup() =0;
	virtual void Update()=0;
	virtual void Render()=0;
	virtual void SetLight() = 0;

	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int objectType) = 0;
	virtual void SetWorldMat(D3DXMATRIX matWorld)= 0;
	

	// cIGObj을(를) 통해 상속됨
	
};

