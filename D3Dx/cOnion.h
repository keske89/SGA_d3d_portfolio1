#pragma once
#include "cFoodObj.h"
class cOnion : public cFoodObj

{
public:
	cOnion();
	~cOnion();

	// cFoodObj��(��) ���� ��ӵ�
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
	virtual void SetLight() override;
};

