#pragma once
class cStageUI
{
private:
	D3DVIEWPORT9		m_VP;
	LPD3DXSPRITE		m_pSprite;
	int					m_nTimer;
	LPDIRECT3DTEXTURE9	m_pTimerTexture;
	LPDIRECT3DTEXTURE9	m_pCoinTexture;
	LPDIRECT3DTEXTURE9	m_pNumberTexture;
	LPDIRECT3DTEXTURE9	m_pMinusTexture;
	LPDIRECT3DTEXTURE9	m_pReadyTexture;
	LPDIRECT3DTEXTURE9	m_pGoTexture;
	LPDIRECT3DTEXTURE9	m_pStarTexture;
	D3DXIMAGE_INFO		m_STTimerImageInfo;
	D3DXIMAGE_INFO		m_STCoinImageInfo;
	D3DXIMAGE_INFO		m_STNumberImageInfo;
	D3DXIMAGE_INFO		m_STMinusImageInfo;
	D3DXIMAGE_INFO		m_STReadyImageInfo;
	D3DXIMAGE_INFO		m_STGoImageInfo;
	D3DXIMAGE_INFO		m_STStarImageInfo;
	D3DXMATRIX			m_matTimer;
	D3DXMATRIX			m_matCoin;
	D3DXMATRIX			m_matNumberSecond0;
	D3DXMATRIX			m_matNumberSecond1;
	D3DXMATRIX			m_matNumberSecond2;
	D3DXMATRIX			m_matCoinNumber0;
	D3DXMATRIX			m_matCoinNumber1;
	D3DXMATRIX			m_matCoinNumber2;
	D3DXMATRIX			m_matMinus;
	D3DXMATRIX			m_matIntro;
	D3DXMATRIX			m_matStar1;
	D3DXMATRIX			m_matStar2;
	D3DXMATRIX			m_matStar3;
public:
	cStageUI();
	~cStageUI();

	void Setup();
	void Update();
	void Render();

	bool StageIntro(int timer);
	bool StageOuttro();

	inline bool getTimer() { 
		if (m_nTimer <= 0) return false; 
		else return true;
	}
};

