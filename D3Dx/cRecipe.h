#pragma once
#include "cIGObj.h"

class cRecipe : public cIGObj
{
public:
	int	m_Type;

public:

	void Setup(int type);
	void Update();
	void Render();
	void Destroy();
	void OrderSystem();


	cRecipe();
	virtual ~cRecipe();

	// cIGObj��(��) ���� ��ӵ�
	virtual void Setup() override;
};

