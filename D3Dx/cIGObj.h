#pragma once
class cObjLoader;
class cTomato;
class cKnife;

class cIGObj
{
private:
	cObjLoader*	    ObjLoader;
public:

	//bool				m_bInteraction;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXMESH			m_pMesh;
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vDir;
	D3DXMATRIX			m_matWorld;
	
	cIGObj*			m_Tomato;
	cIGObj*			m_Knife;

	std::vector<cIGObj*>	m_VecObj;
	SYNTHESIZE(bool, m_bInteraction, Interaction);

public:
	cIGObj();
	virtual ~cIGObj();

	virtual void Setup() ;  
	virtual void Update();
	virtual void Render();
	

};

