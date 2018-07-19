#pragma once
#include "cActionObj.h"

class cCrate;

class cCrateLid : public cActionObj
{
private:

	LPDIRECT3DTEXTURE9			m_pTexture2;
	bool						m_bCheck;
	bool						m_bAni;
	cCrate*						m_crate;
	float						m_fAnimationRot;


	//m_LidType;
public:
	cCrateLid();
	~cCrateLid();


	// cActionObj��(��) ���� ��ӵ�
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int objectType) override;
	virtual void SetWorldMat(D3DXMATRIX matWorld);
	virtual void SetLight() override;
	void Action();
	void Animation();
	void Inventory();
};



