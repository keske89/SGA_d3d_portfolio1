#pragma once
#include "cActionObj.h"

class cFoodObj;
class cProgressbar;
class cRecipe;

enum POT_STATUS
{
	STAT_START,
	STAT_BOILING,
	STAT_FINISHED,
	STAT_END,
};

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

	//Effect
	int		m_nPotStatus;
	int		m_nEffectCount;
	vector<cEffectObject*> m_vecEffect;
	UIObject * m_pIcon[3];

public:
	cPot();
	~cPot();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	void InvenToVector();

	

	// cActionObj을(를) 통해 상속됨
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype) override;
	virtual void SetLight() override;
	virtual void SetWorldMat(D3DXMATRIX matWorld) override;
	
	//Status
	int	 getPotStat() { return m_nPotStatus; }
	void setPotStat(int stat) { m_nPotStatus = stat; }

	//Effect
	void EffectSetup();
	void Effect();
	void setIconPosition();
	void setIconTexture();
	void DestroyRecipe();

	D3DXVECTOR2 Convert3DTo2D(D3DXVECTOR3 v);

};

