#pragma once
#include "cIGObj.h"

class cRecipe : public cIGObj
{
public:
	int	m_Type;
		

	

public:

	void Setup(D3DXMATRIX matWorld, int type);
	void Update();
	void Render();
	void Destroy();

	cRecipe();
	virtual ~cRecipe();

	// cIGObj��(��) ���� ��ӵ�
	virtual void Setup() override;
};

