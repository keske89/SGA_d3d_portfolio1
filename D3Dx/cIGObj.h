#pragma once

class cIGObj;
class cChef;
class cActionDelegate //Action¿ë delegate class
{
public:
	virtual void OnAction(cIGObj* pSender) = 0;
	void Release() { delete this; }
};

enum COLLISONTYPE
{
	OBJ_STATIC,
	OBJ_DYNAMIC,

}; 


class cIGObj
{
public:

	//bool				m_bInteraction;
	LPD3DXSPRITE		m_pSprite;
	LPDIRECT3DTEXTURE9	m_pIcon;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXMESH			m_pMesh;
	D3DMATERIAL9		m_stMtl;
	D3DXMATRIX			m_matWorld;
	D3DXMATRIX			m_matLocal;
	//cIGObj*				m_Inven;
	cIGObj*				m_pChild;
	int					m_nObjectType;
	int					m_Cost;
	COLLISONTYPE		m_eState;
	
	SYNTHESIZE(bool, m_bInteraction, Interaction);
	SYNTHESIZE(D3DXVECTOR3, m_vDir, Dir);
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Pos);
	SYNTHESIZE(cActionDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(cChef*, m_player, player);
	SYNTHESIZE(bool, m_bIsEquipped, IsEquipped);
	SYNTHESIZE(bool, m_bIsAction, IsAction);
	SYNTHESIZE(bool, m_isChopped, chopped);
	SYNTHESIZE(cIGObj*, m_Inven, Inven);
	SYNTHESIZE(bool, m_IsSet, IsSet);
	SYNTHESIZE(bool, m_isFull, IsFull);
	int GetCost() { return m_Cost; }
public:
	cIGObj();
	virtual ~cIGObj();

	virtual void Setup()= 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	void AddChild(cIGObj* childNode);
	void SetWorldMatrix(D3DXMATRIX matWorld);
	D3DXMATRIX GetWorldMat() {	return (m_matLocal * m_matWorld);}
	inline int GetObjectType() { return m_nObjectType; }
	inline int GetCollisonType() { return m_eState; }
	LPD3DXMESH GetMesh() { return m_pMesh; }
	
};
