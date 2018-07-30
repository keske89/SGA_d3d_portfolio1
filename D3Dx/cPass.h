#pragma once
#include "cActionObj.h"
class cPassScroll;
class cStageObjManager;
class cOrder;
class cPot;

class cPass : public cActionObj
{
public:

	cPassScroll*		m_PassScroll;
	cStageObjManager*	m_SOM;
	cPot*				m_Pot;
	std::vector<cOrder*> m_vec;

public:
	cPass();
	~cPass();

	// cActionObj을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
	virtual void SetLight() override;

	void SetSOM(cStageObjManager* som) { m_SOM = som; }
	void Inventory();
	void Present();
};

