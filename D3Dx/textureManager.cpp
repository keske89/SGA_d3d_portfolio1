#include "stdafx.h"
#include "textureManager.h"


textureManager::textureManager()
{
}


textureManager::~textureManager()
{
}

void textureManager::release()
{
	this->deleteAll();
}

#ifdef UNICODE
TEXTUREINFO textureManager::addTexture(wstring keyName, const WCHAR* fileName)
{
	TEXTUREINFO info = find(keyName);

	if (info) return info;
	info = new tagTextureInfo;

	if (FAILED(D3DXCreateTextureFromFileEx(
		D3DDEVICE,
		fileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,
		0,
		D3DFMT_FROM_FILE,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		D3DCOLOR_ARGB(255, 255, 0, 255),
		&info->textureInfo,
		0,
		&info->texture)))
	{
		return NULL;
	}

	_textures.insert(make_pair(keyName, info));

	return info;
}

TEXTUREINFO textureManager::addTexture(wstring keyName, LPDIRECT3DDEVICE9 device, const WCHAR* fileName)
{
	TEXTUREINFO info = find(keyName);

	if (info) return info;
	info = new tagTextureInfo;

	if (FAILED(D3DXCreateTextureFromFileEx(
		device,
		fileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,
		0,
		D3DFMT_FROM_FILE,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		D3DCOLOR_ARGB(255, 255, 0, 255),
		&info->textureInfo,
		0,
		&info->texture)))
	{
		return NULL;
	}

	_textures.insert(make_pair(keyName, info));

	return info;
}

TEXTUREINFO textureManager::find(wstring keyName)
{
	map<wstring, TEXTUREINFO>::iterator key = _textures.find(keyName);

	if (key != _textures.end())
	{
		return key->second;
	}

	return NULL;
}

LPDIRECT3DTEXTURE9 textureManager::findTexture(wstring keyName)
{
	map<wstring, TEXTUREINFO>::iterator key = _textures.find(keyName);

	if (key != _textures.end())
	{
		return key->second->texture;
	}

	return NULL;
}

BOOL textureManager::deleteTexture(wstring keyName)
{
	map<wstring, TEXTUREINFO>::iterator key = _textures.find(keyName);

	if (key != _textures.end())
	{
		key->second->texture->Release();
		SAFE_DELETE(key->second);
		_textures.erase(key);
		return TRUE;
	}

	return FALSE;
}

BOOL textureManager::deleteAll()
{
	map<wstring, TEXTUREINFO>::iterator key = _textures.begin();

	for (; key != _textures.end();)
	{
		if (key->second)
		{
			key->second->texture->Release();
			SAFE_DELETE(key->second);
			key = _textures.erase(key);
		}
		else ++key;
	}

	_textures.clear();

	return TRUE;
}

D3DXVECTOR2 textureManager::getUVPoint(wstring keyName, float textureX, float textureY)
{
	D3DXVECTOR2 uvPoint = D3DXVECTOR2(0, 0);

	map<wstring, TEXTUREINFO>::iterator key = _textures.find(keyName);

	if (key != _textures.end())
	{
		uvPoint = D3DXVECTOR2(textureX / key->second->textureInfo.Width, textureY / key->second->textureInfo.Height);
	}

	return uvPoint;
}
#else
TEXTUREINFO textureManager::addTexture(string keyName, const char* fileName)
{
	TEXTUREINFO info = find(keyName);

	if (info) return info;
	info = new tagTextureInfo;

	if (FAILED(D3DXCreateTextureFromFileEx(
		D3DDEVICE,
		fileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,
		0,
		D3DFMT_FROM_FILE,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		0,
		&info->textureInfo,
		0,
		&info->texture)))
	{
		return NULL;
	}


	_textures.insert(make_pair(keyName, info));

	return info;
}

TEXTUREINFO textureManager::addTexture(string keyName, LPDIRECT3DDEVICE9 device, const char* fileName)
{
	TEXTUREINFO info = find(keyName);

	if (info) return info;
	info = new tagTextureInfo;

	if (FAILED(D3DXCreateTextureFromFileEx(
		device,
		fileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,
		0,
		D3DFMT_FROM_FILE,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		0,
		&info->textureInfo,
		0,
		&info->texture)))
	{
		return NULL;
	}

	_textures.insert(make_pair(keyName, info));

	return info;
}

TEXTUREINFO textureManager::find(string keyName)
{
	map<string, TEXTUREINFO>::iterator key = _textures.find(keyName);

	if (key != _textures.end())
	{
		return key->second;
	}

	return NULL;
}

LPDIRECT3DTEXTURE9 textureManager::findTexture(string keyName)
{
	map<string, TEXTUREINFO>::iterator key = _textures.find(keyName);

	if (key != _textures.end())
	{
		return key->second->texture;
	}

	return NULL;
}

BOOL textureManager::deleteTexture(string keyName)
{
	map<string, TEXTUREINFO>::iterator key = _textures.find(keyName);

	if (key != _textures.end())
	{
		key->second->texture->Release();
		SAFE_DELETE(key->second);
		_textures.erase(key);
		return TRUE;
	}

	return FALSE;
}

BOOL textureManager::deleteAll()
{
	map<string, TEXTUREINFO>::iterator key = _textures.begin();

	for (; key != _textures.end();)
	{
		if (key->second)
		{
			key->second->texture->Release();
			SAFE_DELETE(key->second);
			key = _textures.erase(key);
		}
		else ++key;
	}

	_textures.clear();

	return TRUE;
}

D3DXVECTOR2 textureManager::getUVPoint(string keyName, float textureX, float textureY)
{
	D3DXVECTOR2 uvPoint = D3DXVECTOR2(0, 0);

	map<string, TEXTUREINFO>::iterator key = _textures.find(keyName);

	if (key != _textures.end())
	{
		uvPoint = D3DXVECTOR2(textureX / key->second->textureInfo.Width, textureY / key->second->textureInfo.Height);
	}

	return uvPoint;
}
#endif

