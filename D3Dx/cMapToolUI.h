#pragma once
class cMapToolUI
{
private:
	LPD3DXSPRITE		m_pSprite;
	LPDIRECT3DTEXTURE9	m_pUITexture;
	D3DXIMAGE_INFO		m_stImageInfo;
public:
	cMapToolUI();
	~cMapToolUI();

	void Setup();
	void Update();
	void Render();
};

