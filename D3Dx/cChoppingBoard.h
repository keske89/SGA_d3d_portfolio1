#pragma once
#include "cActionObj.h"

class cProgressbar;
class cFoodObj;

class cChoppingBoard : public cActionObj
{
public:
	cProgressbar* m_pPgbar;
	int				m_size;

public:
	cChoppingBoard();
	~cChoppingBoard();

	// cActionObj을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
	virtual void SetLight() override;
	void Inventory();
};

