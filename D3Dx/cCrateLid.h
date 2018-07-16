#pragma once
#include "cActionObj.h"

class cCrate;

class cCrateLid : public cActionObj
{
private:
	enum CrateState
	{
		NORMAL,
		COLLISIONWITHPLAYER,
		SELECTED,
		COUNT
	};
	CrateState m_CrateState;


	LPDIRECT3DTEXTURE9			m_pTexture2;
	bool m_bCheck;
	bool m_bAni;
	cCrate*						m_crate;
	float m_fAnimationRot;


	//m_LidType;
public:
	cCrateLid();
	~cCrateLid();


	LPDIRECT3DTEXTURE9 m_aTexture[COUNT];
	void SetCheck(bool check) { m_bCheck = check; }
	bool GetCheck() { return m_bCheck; }
	// cActionObj을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int objectType) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld);


	cIGObj* GetInven();
	void SetInven(cIGObj* object) { m_Inven = object; }

	void Action();
	void Animation();
	void Inventory();
};



