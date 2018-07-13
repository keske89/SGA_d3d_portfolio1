#pragma once
class cChefRunPuff;
class cRunPuffDelegate //Action¿ë delegate class
{
public:
	virtual void OnAction(cChefRunPuff* pSender) = 0;
	void Release() { delete this; }
};

class cChefRunPuff
{
private:
	LPD3DXMESH					m_pMesh;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXMATRIX					m_matLocal;
	D3DXMATRIX					m_matWorld;
	float						m_fangle;
	SYNTHESIZE_REF(float, m_fScale, scale);
	SYNTHESIZE(cRunPuffDelegate*, m_pDelegate, Delegate);
public:
	cChefRunPuff();
	~cChefRunPuff();
	void SetUp(D3DXVECTOR3 vPos);
	void Update();
	void Render();
};

