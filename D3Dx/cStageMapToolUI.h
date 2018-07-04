#pragma once
class cStageMapToolUI
{
private:
	LPD3DXSPRITE		m_pSprite;
	LPDIRECT3DTEXTURE9	m_pUITexture;
	D3DXIMAGE_INFO		m_stImageInfo;
public:
	cStageMapToolUI();
	~cStageMapToolUI();

	void Setup();
	void Update();
	void Render();
};

