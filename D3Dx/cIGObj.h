#pragma once
class cObjLoader;
class cTomato;
class cKnife;
class cPot;
class cCrate;


class cIGObj
{
public:

	//bool				m_bInteraction;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXMESH			m_pMesh;
	//D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vDir;
	//D3DXMATRIX			m_matWorld;
	
	cIGObj*			m_Tomato;
	cIGObj*			m_Knife;
	cIGObj*			m_Pot;
	cIGObj*			m_Crate;

	std::vector<cIGObj*>	m_VecObj;
	SYNTHESIZE(bool, m_bInteraction, Interaction);
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Pos);
	SYNTHESIZE(D3DXMATRIX, m_matWorld, MatWorld);


public:
	cIGObj();
	virtual ~cIGObj();

	virtual void Setup() ;  
	virtual void Update();
	virtual void Render();
	

};

