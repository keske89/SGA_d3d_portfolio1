#pragma once

class cChefRunPuff
{
private:
	LPD3DXMESH					m_pMesh;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXMATRIX					m_matLocal;
	D3DXMATRIX					m_matWorld;
	D3DMATERIAL9				m_stMtl;
	float						m_fangle;
	SYNTHESIZE_REF(float, m_fScale, scale);
public:
	cChefRunPuff();
	~cChefRunPuff();
	void SetUp(D3DXVECTOR3 vPos);
	void Update();
	void Render();
	void BoomMod(D3DXVECTOR3 dir);
	void SetMaterial();
};

