#pragma once
#include "cActionObj.h"

class cCrateLid;

class cCrate : public cActionObj
{
public:
	cCrate();
	~cCrate();

	// cActionObj��(��) ���� ��ӵ�
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int objectType);
	virtual void SetWorldMat(D3DXMATRIX matWorld);
	virtual void SetLight() override;


};




