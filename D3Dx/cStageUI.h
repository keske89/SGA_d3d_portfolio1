#pragma once
class cStageUI
{
private:
	LPD3DXSPRITE		m_pSprite;
	int					m_nTimer;
	LPDIRECT3DTEXTURE9	m_pTimerTexture;
	LPDIRECT3DTEXTURE9	m_pNumberTexture;
	D3DXIMAGE_INFO		m_STTimerImageInfo;
	D3DXIMAGE_INFO		m_STNumberImageInfo;
	D3DXMATRIX			m_matTimer;
	D3DXMATRIX			m_matNumberSecond0;
	D3DXMATRIX			m_matNumberSecond1;
	D3DXMATRIX			m_matNumberSecond2;
public:
	cStageUI();
	~cStageUI();

	void Setup();
	void Update();
	void Render();

	RECT getRect(LONG left, LONG top, LONG right, LONG bottom);

	inline bool getTimer() { 
		if (m_nTimer <= 0) return false; 
		else return true;
	}
};

