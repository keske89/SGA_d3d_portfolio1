#pragma once
#include "cActionObj.h"



class cCrateLid	: public cActionObj
{
					//m_LidType;
public:
	cCrateLid();
	~cCrateLid();

	

	// cActionObj��(��) ���� ��ӵ�
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld);
};

