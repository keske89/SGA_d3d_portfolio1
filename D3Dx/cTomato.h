#pragma once
#include "cFoodObj.h"

class cTomato : public cFoodObj
{

public:
	cTomato();
	virtual ~cTomato();

	virtual void Setup();
	virtual void Update();
	virtual void Render();



	// cFoodObj을(를) 통해 상속됨
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetLight() override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;

};

