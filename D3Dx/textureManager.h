#pragma once

#include <map>
#include <string>
using namespace std;

#ifndef D3DDEVICE
#define D3DDEVICE		deviceManager::GetInstance()->getDevice()
#endif

#ifndef SAFE_DELETE(p)
#define SAFE_DELETE(p)	{if (p) delete p; p = NULL;}
#endif

#define TEXTUREMANAGER	textureManager::GetInstance()

#ifndef g_pTextureManager
#define g_pTextureManager TEXTUREMANAGER
#endif

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9	texture;
	D3DXIMAGE_INFO		textureInfo;
} *TEXTUREINFO;

class textureManager
{
	SINGLETONE(textureManager)

#ifdef UNICODE
private:
	map<wstring, TEXTUREINFO>		_textures;

public:
	void release();

	TEXTUREINFO addTexture(wstring keyName, const WCHAR* fileName);
	TEXTUREINFO addTexture(wstring keyName, LPDIRECT3DDEVICE9 device, const WCHAR* fileName);

	TEXTUREINFO find(wstring keyName);
	LPDIRECT3DTEXTURE9 findTexture(wstring keyName);

	BOOL deleteTexture(wstring keyName);
	BOOL deleteAll();

	D3DXVECTOR2 getUVPoint(wstring keyName, float textureX, float textureY);
#else
private:
	map<string, TEXTUREINFO>		_textures;

public:
	void release();

	TEXTUREINFO addTexture(string keyName, const char* fileName);
	TEXTUREINFO addTexture(string keyName, LPDIRECT3DDEVICE9 device, const char* fileName);

	TEXTUREINFO find(string keyName);
	LPDIRECT3DTEXTURE9 findTexture(string keyName);

	BOOL deleteTexture(string keyName);
	BOOL deleteAll();

	D3DXVECTOR2 getUVPoint(string keyName, float textureX, float textureY);
#endif
};



