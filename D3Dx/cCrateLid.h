#pragma once
#include "cActionObj.h"

class cCrateLid	: public cActionObj
{

public:
	cCrateLid();
	~cCrateLid();

	

	// cActionObj을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos);
};

