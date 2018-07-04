#pragma once
#include"cObjLoader.h"
class cChefRoot
{
protected:
	D3DXMATRIX					m_matLocalTM;
	float						m_fRotX;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DMATERIAL9				m_stMtl;
	LPD3DXMESH					m_pMesh;
	std::vector<cChefRoot*>		m_vecChild;
protected:
	SYNTHESIZE(D3DXVECTOR3, m_vLocalPos, Pos);
	SYNTHESIZE(float, m_fRotDeltaX, RotDeltaX);
	SYNTHESIZE(D3DXMATRIX, m_matWorldTM, world);
	SYNTHESIZE(D3DXMATRIX*, m_pParentWorldTM, ParentWorldTM);

	
public:
	cChefRoot();
	~cChefRoot();
	void AddChild(cChefRoot* pChild);
	void Destroy();
	virtual void SetUp();
	virtual void Update();
	virtual void Render();



};

