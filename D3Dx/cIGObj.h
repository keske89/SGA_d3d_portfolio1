#pragma once

class cIGObj;

class cActionDelegate //Action¿ë delegate class
{
public:
	virtual void OnAction(cIGObj* pSender) = 0;
	void Release() { delete this; }
};


class cIGObj
{
public:

	//bool				m_bInteraction;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXMESH			m_pMesh;
	//D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vDir;
	D3DXMATRIX			m_matWorld;
	D3DXMATRIX			m_matLocal;
	cIGObj*				m_Inven;
	cIGObj*				m_pChild;
	int					m_nObjectType;
	
	SYNTHESIZE(bool, m_bInteraction, Interaction);
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Pos);

	SYNTHESIZE(cActionDelegate*, m_pDelegate, Delegate);

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

