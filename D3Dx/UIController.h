#pragma once

enum UITEXTURE
{
	UITEX_NORMAL,
	UITEX_OVER,
	UITEX_DOWN,
	UITEX_END
};

class UIObject;

class IUIFunction
{
public:
	virtual void OnClick(UIObject * pSender) = 0;
	virtual void OnOver(UIObject * pSender) = 0;
	virtual void OnExit(UIObject * pSender) = 0;
	virtual void OnEntrance(UIObject * pSender) = 0;
};

class UIObject
{
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);
	SYNTHESIZE(string, m_sName, Name);
	SYNTHESIZE(int, m_nAlpha, Alpha);

protected:
	vector<UIObject*>		m_vecChild;
	LPDIRECT3DTEXTURE9		m_pTex[UITEX_END];
	POINT					m_ptTexWH[UITEX_END];
	UIObject *				m_pParent;
	D3DXMATRIX				m_matWorld;
	IUIFunction *			m_pFunction;
	bool					m_isOver;

public:
	UIObject();
	~UIObject();

	void Update();
	void Render();

	void AddChild(UIObject * pChild);
	void SetTexture(LPDIRECT3DTEXTURE9 normal, LPDIRECT3DTEXTURE9 over = NULL, LPDIRECT3DTEXTURE9 down = NULL);
	void SetFunction(IUIFunction * function);
	UIObject * Find(string name);
	void Release();
};


