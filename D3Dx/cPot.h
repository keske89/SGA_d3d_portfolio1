#pragma once
#include "cActionObj.h"

class cFoodObj;
class cProgressbar;

class cPot : public cActionObj
{
public:
	
	cProgressbar*			m_pPgbar;
	std::vector<cFoodObj*>	m_vecFood;
	int						m_size;

public:
	cPot();
	~cPot();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void SetFood(cFoodObj* foodobject);


	// cActionObj��(��) ���� ��ӵ�
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;

	virtual void SetWorldMat(D3DXMATRIX matWorld) override;

};

