#pragma once


class cProgressbar
{
private:
	D3DXVECTOR3				m_vPos;
	LPDIRECT3DTEXTURE9		m_pTexture;
	
	float					m_fCurrentWidth;
	//float					m_fMaxWidth;
	float					m_fHeight;

	std::vector<ST_PT_VERTEX>	m_vecVertexTop;
	std::vector<ST_PT_VERTEX>	m_vecVertexBottom;

	SYNTHESIZE(float, m_fMaxWidth, MaxWidth);
	//SYNTHESIZE(float, m_fCurrentWidth, progress);


public:
	cProgressbar();
	~cProgressbar();

	void Setup(D3DXVECTOR3 pos);
	void Update(D3DXVECTOR3 pos);
	void Render(D3DXVECTOR3 pos);

	void SetProgress();

};

