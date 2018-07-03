#pragma once
class cObjLoader;
class cTomato;
class cKnife;

class cIGObj
{
private:
	cObjLoader*	    ObjLoader;
public:

	bool				m_bInteraction;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXMESH			m_pMesh;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matT;
	std::string			m_Name;
	


	cIGObj*			m_Tomato;
	cIGObj*			m_Knife;

	std::vector<cIGObj*>	m_VecObj;


public:
	cIGObj();
	virtual ~cIGObj();

	virtual void Setup() ;  
	virtual void Update();
	virtual void Render();

};

