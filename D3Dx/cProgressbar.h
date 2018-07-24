#pragma once


class cProgressbar
{
private:
	D3DXVECTOR3				m_vPos;
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DXMATRIX				m_matLocal;
	D3DXMATRIX				m_matWorld;
	LPD3DXSPRITE			m_pSprite;
	
	float					m_fTopGauge;
	float					m_fBottomGauge;
	float					m_fProgress;
	float					m_fHeight;
	int						m_type;
	bool					m_isComplete;
	bool					m_isStart;

	LPDIRECT3DTEXTURE9		m_pUITexture;
	D3DXIMAGE_INFO			m_stImageInfo;

	std::vector<ST_PT_VERTEX>	m_vecComplete;
	std::vector<ST_PT_VERTEX>	m_vecVertexTop;
	std::vector<ST_PT_VERTEX>	m_vecVertexBottom;



public:
	cProgressbar();
	~cProgressbar();

	void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int Type);
	void Update(D3DXVECTOR3 pos, int size);
	void Render();

	float SetGauge(int size);
	bool Complete();
	//void SetIsAction(bool action) { m_isAction = action; }
	void SetPos(D3DXVECTOR3 pos) { m_vPos = pos; }
	void SetIsStart(bool start) { m_isStart = start; }
	

};

