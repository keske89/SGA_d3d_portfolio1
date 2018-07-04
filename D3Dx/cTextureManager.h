#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	SINGLETONE(cTextureManager);
	map<wstring, LPDIRECT3DTEXTURE9>	m_mapTexture;
	map<wstring, D3DXIMAGE_INFO>		m_mapImageInfo;

public:
	LPDIRECT3DTEXTURE9 GetTexture(const WCHAR* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(const WCHAR* szFullPath, D3DXIMAGE_INFO* pImageInfo);
	void Destroy();
};

