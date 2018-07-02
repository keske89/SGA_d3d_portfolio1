#pragma once
class cIngameObj
{
protected:
	bool				m_bInteraction;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_mMat;
	LPDIRECT3DTEXTURE9	m_pTexture;



public:
	cIngameObj();
	~cIngameObj();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

