#pragma once

class IDisplayObject
{
protected:
	CString			m_name;
	WORD			m_tag;
	D3DXVECTOR3		m_vPosition;
	D3DXVECTOR3		m_rot;
	D3DXVECTOR3		m_scale;

	D3DXMATRIX		m_matLocal;
	D3DXMATRIX		m_matWorld;

	IDisplayObject*		m_pParent;
	vector<IDisplayObject*>	m_vecChild;


public:
	IDisplayObject();
	virtual ~IDisplayObject();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release();

	virtual void AddChild(IDisplayObject* pChild);
	
	CString GetName() { return m_name; }
	void SetName(LPCTSTR name) { m_name = name; }
	IDisplayObject* FindChildByName(LPCTSTR name);
	D3DXMATRIX& GetLocalMatrix() { return m_matLocal; }
	void		SetLocalMatrix(D3DXMATRIX* pMat) { m_matLocal = *pMat; }
	const D3DXVECTOR3& GetPosition() { return m_vPosition; }
	void				setPosition(D3DXVECTOR3* pos) { m_vPosition = *pos; }
	const D3DXVECTOR3& GetRotation() { return m_rot; }
	void				setRotation(D3DXVECTOR3* rot) { m_rot = *rot; }
	const D3DXVECTOR3& GetScale() { return m_scale; }
	void				setScale(D3DXVECTOR3* scale) { m_scale = *scale; }
	const D3DXMATRIX& GetWorldMatrix() { return m_matWorld; }
	void				setWorldMatrix(D3DXMATRIX* pMat) { m_matWorld = *pMat; }
	const vector<IDisplayObject*> GetVecChild() { return m_vecChild; }

};

