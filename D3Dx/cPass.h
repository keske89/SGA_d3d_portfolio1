#pragma once
#include "cActionObj.h"
class cPassScroll;

class cPass : public cActionObj
{
	cPassScroll*		m_PassScroll;
public:
	cPass();
	~cPass();

	// cActionObj��(��) ���� ��ӵ�
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
};

