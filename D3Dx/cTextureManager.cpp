#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const char * szFullPath)
{
	//std::string sFullPath = std::string(szFullPath);
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		//wchar_t wtext[1024];
		//size_t outSize;
		//mbstowcs_s(&outSize, wtext, strlen(szFullPath) + 1, szFullPath, strlen(szFullPath));
		D3DXCreateTextureFromFile(g_pD3DDevice, szFullPath, &m_mapTexture[szFullPath]);
	}

	return m_mapTexture[szFullPath];
}

void cTextureManager::Destroy()
{
	for (auto p : m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapTexture.clear();
}
