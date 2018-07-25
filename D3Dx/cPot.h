#pragma once
#include "cActionObj.h"

class cFoodObj;
class cProgressbar;
class cRecipe;


class cPot : public cActionObj
{
public:
	
	cProgressbar*			m_pPgbar;
	int						m_RecipeCost;
	int						m_InvenCount;
	int						m_size;
	IDirect3DTexture9*		m_texture[3];
	std::vector<cIGObj*>	m_vec;
	cRecipe*				m_recipe;
public:
	cPot();
	~cPot();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	void InvenToVector();

	

	// cActionObj��(��) ���� ��ӵ�
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetLight() override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
	

};

