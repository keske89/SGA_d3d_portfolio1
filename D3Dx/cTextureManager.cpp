#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const WCHAR* szFullPath)
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

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const WCHAR * szFullPath, D3DXIMAGE_INFO * pImageInfo)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end() ||
		m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			szFullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[szFullPath],
			0,
			&m_mapTexture[szFullPath]);
	}

	*pImageInfo = m_mapImageInfo[szFullPath];

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
