#pragma once
class cStageUI
{
private:
	LPD3DXSPRITE		m_pSprite;
	int					m_nTimer;
	LPDIRECT3DTEXTURE9	m_pTimerTexture;
	LPDIRECT3DTEXTURE9	m_pCoinTexture;
	LPDIRECT3DTEXTURE9	m_pNumberTexture;
	D3DXIMAGE_INFO		m_STTimerImageInfo;
	D3DXIMAGE_INFO		m_STCoinImageInfo;
	D3DXIMAGE_INFO		m_STNumberImageInfo;
	D3DXMATRIX			m_matTimer;
	D3DXMATRIX			m_matCoin;
	D3DXMATRIX			m_matNumberSecond0;
	D3DXMATRIX			m_matNumberSecond1;
	D3DXMATRIX			m_matNumberSecond2;
	D3DXMATRIX			m_matCoinNumber0;
	D3DXMATRIX			m_matCoinNumber1;
	D3DXMATRIX			m_matCoinNumber2;
public:
	cStageUI();
	~cStageUI();

	void Setup();
	void Update();
	void Render();

	inline bool getTimer() { 
		if (m_nTimer <= 0) return false; 
		else return true;
	}
};

