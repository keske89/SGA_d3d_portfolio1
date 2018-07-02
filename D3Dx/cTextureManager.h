#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	SINGLETONE(cTextureManager);
	std::map<std::string, LPDIRECT3DTEXTURE9>	m_mapTexture;

public:
	LPDIRECT3DTEXTURE9 GetTexture(const char* szFullPath);
	void Destroy();
};

