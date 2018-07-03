#pragma once
class cIGObj
{
public:

	bool				m_bInteraction;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXMESH			m_pMesh;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_mMat;


public:
	cIGObj();
	~cIGObj();

	virtual void Setup() ;  
	virtual void Update();
	virtual void Render();

};

