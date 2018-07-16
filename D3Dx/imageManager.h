#pragma once

#include <map>
using namespace std;

#include "image.h"

#define IMAGEMANAGER imageManager::GetInstance()

class imageManager
{
	SINGLETONE(imageManager);

#ifdef UNICODE
private:
	map<wstring, image*>	_mImageList;

public:
	void release();

	image* addImage(wstring keyName, float width, float height);
	image* addImage(wstring keyName, const WCHAR* fileName);
	image* addImage(wstring keyName, const WCHAR* fileName, float x, float y);

	image* addFrameImage(wstring keyName, const WCHAR* fileName, float x, float y, int frameX, int frameY);
	image* addFrameImage(wstring keyName, const WCHAR* fileName, int frameX, int frameY);

	image* findImage(wstring keyName);

	BOOL deleteImage(wstring keyName);
	BOOL deleteAll();

	void render(wstring keyName);
	void render(wstring keyName, float destX, float destY);
	void render(wstring keyName, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);

	void frameRender(wstring keyName, float destX, float destY);
	void frameRender(wstring keyName, float destX, float destY, int currentFrameX, int currentFrameY);

	void alphaRender(wstring keyName, BYTE alpha);
	void alphaRender(wstring keyName, float destX, float destY, BYTE alpha);
	void alphaRender(wstring keyName, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, BYTE alpha);

	void alphaFrameRender(wstring keyName, float destX, float destY, BYTE alpha);
	void alphaFrameRender(wstring keyName, float destX, float destY, int currentFrameX, int currentFrameY, BYTE alpha);
#else
private:
	map<string, image*>	_mImageList;

public:
	imageManager();
	~imageManager();

	void release();

	HRESULT addImage(string keyName, float width, float height, BOOL isAlpha = FALSE);
	HRESULT addImage(string keyName, const WCHAR* fileName, BOOL isAlpha = FALSE);
	HRESULT addImage(string keyName, const WCHAR* fileName, float x, float y, BOOL isAlpha = FALSE);

	HRESULT addFrameImage(string keyName, const WCHAR* fileName, float x, float y, int frameX, int frameY, BOOL isAlpha = FALSE);
	HRESULT addFrameImage(string keyName, const WCHAR* fileName, int frameX, int frameY, BOOL isAlpha = FALSE);

	image* findImage(string keyName);

	BOOL deleteImage(string keyName);
	BOOL deleteAll();

	void render(string keyName);
	void render(string keyName, float destX, float destY);
	void render(string keyName, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);

	void frameRender(string keyName, float destX, float destY);
	void frameRender(string keyName, float destX, float destY, int currentFrameX, int currentFrameY);

	void alphaRender(string keyName, BYTE alpha);
	void alphaRender(string keyName, float destX, float destY, BYTE alpha);
	void alphaRender(string keyName, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, BYTE alpha);

	void alphaFrameRender(string keyName, float destX, float destY, BYTE alpha);
	void alphaFrameRender(string keyName, float destX, float destY, int currentFrameX, int currentFrameY, BYTE alpha);
#endif
};


