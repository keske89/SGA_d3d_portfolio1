#pragma once

class cChef;
class cIGObj;

class cActionDelegate //Action¿ë delegate class
{
public:
	virtual void OnAction(cIGObj* pSender) = 0;
	void Release() { delete this; }
};

enum OBJECTTYPE
{
	OBJ_STATIC,
	OBJ_DYNAMIC,

}; 

class cIGObj
{
public:

	//bool				m_bInteraction;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXMESH			m_pMesh;
	D3DXMATRIX			m_matWorld;
	D3DXMATRIX			m_matLocal;
	cIGObj*				m_Inven;
	cIGObj*				m_pChild;
	int					m_nObjectType;
	OBJECTTYPE			m_eState;
	
	SYNTHESIZE(bool, m_bInteraction, Interaction);
	SYNTHESIZE(D3DXVECTOR3, m_vDir, Dir);
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Pos);
	SYNTHESIZE(cActionDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(cChef*, m_player1, player1);
	SYNTHESIZE(cChef*, m_player2, player2);
	

public:
	cIGObj();
	virtual ~cIGObj();

	virtual void Setup()= 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void SetInven(cIGObj* object) { m_Inven = object; }
	void AddChild(cIGObj* childNode);
	void SetWorldMatrix(D3DXMATRIX matWorld);
	inline int GetObjectType() { return m_nObjectType; }
};

