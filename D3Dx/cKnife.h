#pragma once
#include "cActionObj.h"

class cFoodObj;


class cKnife : public cActionObj
{
	
	


public:
	cKnife();
	virtual ~cKnife();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	

	// cActionObj을(를) 통해 상속됨
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;

	virtual void SetWorldMat(D3DXMATRIX matWorld) override;

};

