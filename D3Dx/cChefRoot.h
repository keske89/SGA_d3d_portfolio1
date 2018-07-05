#pragma once
#include"cObjLoader.h"
enum PARTANIMATION
{
	PARTANIMATION_IDLE,
	PARTANIMATION_MOVE,
	PARTANIMATION_CHOP,
	PARTANIMATION_TRANCEPORT,
	PARTANIMATION_DISHWASHING
};
class cChefRoot
{
protected:
	D3DXMATRIX					m_matLocalTM;
	D3DXMATRIX					m_matWorldTM;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DMATERIAL9				m_stMtl;
	LPD3DXMESH					m_pMesh;
	SYNTHESIZE_REF(std::vector<cChefRoot*>, m_vecChild, Child);
	PARTANIMATION				m_ePartAnimation;
protected:
	SYNTHESIZE(D3DXVECTOR3, m_vLocalPos, Pos);
	float m_fRotX, RotX;
	float m_fRotY, RotY;
	SYNTHESIZE(float, m_fRotDeltaX, RotDeltaX);
	SYNTHESIZE(float, m_fRotDeltaY, RotDeltaY);
	SYNTHESIZE(D3DXMATRIX*, m_pParentWorldTM, ParentWorldTM);


public:
	cChefRoot();
	~cChefRoot();
	void AddChild(cChefRoot* pChild);
	void Destroy();
	virtual void SetUp();
	virtual void Update();
	virtual void Render();
	virtual void AniMation();
	virtual void SetPart_AniMation(int state)
	{
		m_ePartAnimation = (PARTANIMATION)state;
	}
	virtual PARTANIMATION GetCHEF_STATE() { return m_ePartAnimation; }
	virtual void ImageChange();

};

