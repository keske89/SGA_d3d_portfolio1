#pragma once
#include "cActionObj.h"

class cFoodObj;
class cProgressbar;



class cPot : public cActionObj
{
public:
	
	cProgressbar*			m_pPgbar;
	int						m_RecipeCost;
	int						m_size;
	IDirect3DTexture9*		m_texture[3];
	//bool					m_bIsAction;
	std::vector<cIGObj*>	m_vec;

public:
	cPot();
	~cPot();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	void InvenToVector();
	void SetFood(cFoodObj* foodobject);
	SYNTHESIZE(bool, m_bIsAction, IsAction);

	// cActionObj을(를) 통해 상속됨
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetLight() override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;

};

