#include "stdafx.h"
#include "imageManager.h"

#ifdef UNICODE
imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

void imageManager::release()
{
	this->deleteAll();
}

image* imageManager::addImage(wstring keyName, float width, float height)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::addImage(wstring keyName, const WCHAR* fileName)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->init(fileName)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::addImage(wstring keyName, const WCHAR* fileName, float x, float y)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->init(fileName, x, y)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::addFrameImage(wstring keyName, const WCHAR* fileName, float x, float y, int frameX, int frameY)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->initFrame(fileName, x, y, frameX, frameY)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::addFrameImage(wstring keyName, const WCHAR* fileName, int frameX, int frameY)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->initFrame(fileName, frameX, frameY)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::findImage(wstring keyName)
{
	map<wstring, image*>::iterator key = _mImageList.find(keyName);

	if (key != _mImageList.end())
		return key->second;

	return NULL;
}

BOOL imageManager::deleteImage(wstring keyName)
{
	map<wstring, image*>::iterator key = _mImageList.find(keyName);

	if (key != _mImageList.end())
	{
		SAFE_OBJRELEASE(key->second);
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

BOOL imageManager::deleteAll()
{
	map<wstring, image*>::iterator iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second)
		{
			SAFE_OBJRELEASE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return TRUE;
}

void imageManager::render(wstring keyName)
{
	image* img = this->findImage(keyName);

	if (img) img->render();
}

void imageManager::render(wstring keyName, float destX, float destY)
{
	image* img = this->findImage(keyName);

	if (img) img->render(destX, destY);
}

void imageManager::render(wstring keyName, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	image* img = this->findImage(keyName);

	if (img) img->render(destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(wstring keyName, float destX, float destY)
{
	image* img = this->findImage(keyName);

	if (img) img->frameRender(destX, destY);
}

void imageManager::frameRender(wstring keyName, float destX, float destY, int currentFrameX, int currentFrameY)
{
	image* img = this->findImage(keyName);

	if (img) img->frameRender(destX, destY, currentFrameX, currentFrameY);
}

void imageManager::alphaRender(wstring keyName, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaRender(alpha);
}

void imageManager::alphaRender(wstring keyName, float destX, float destY, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaRender(destX, destY, alpha);
}

void imageManager::alphaRender(wstring keyName, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaRender(destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::alphaFrameRender(wstring keyName, float destX, float destY, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaFrameRender(destX, destY, alpha);
}

void imageManager::alphaFrameRender(wstring keyName, float destX, float destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaFrameRender(destX, destY, currentFrameX, currentFrameY, alpha);
}
#else
imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

void imageManager::release()
{
	this->deleteAll();
}

image* imageManager::addImage(string keyName, float width, float height)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::addImage(string keyName, const WCHAR* fileName)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->init(fileName)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::addImage(string keyName, const WCHAR* fileName, float x, float y)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->init(fileName, x, y)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::addFrameImage(string keyName, const WCHAR* fileName, float x, float y, int frameX, int frameY)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->initFrame(fileName, x, y, frameX, frameY)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::addFrameImage(string keyName, const WCHAR* fileName, int frameX, int frameY)
{
	image* img = this->findImage(keyName);

	if (img) return img;
	img = new image;

	if (FAILED(img->initFrame(fileName, frameX, frameY)))
	{
		SAFE_OBJRELEASE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(keyName, img));

	return img;
}

image* imageManager::findImage(string keyName)
{
	map<wstring, image*>::iterator key = _mImageList.find(keyName);

	if (key != _mImageList.end())
		return key->second;

	return NULL;
}

BOOL imageManager::deleteImage(string keyName)
{
	map<wstring, image*>::iterator key = _mImageList.find(keyName);

	if (key != _mImageList.end())
	{
		SAFE_OBJRELEASE(key->second);
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

BOOL imageManager::deleteAll()
{
	map<wstring, image*>::iterator iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second)
		{
			SAFE_OBJRELEASE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return TRUE;
}

void imageManager::render(string keyName)
{
	image* img = this->findImage(keyName);

	if (img) img->render();
}

void imageManager::render(string keyName, float destX, float destY)
{
	image* img = this->findImage(keyName);

	if (img) img->render(destX, destY);
}

void imageManager::render(string keyName, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	image* img = this->findImage(keyName);

	if (img) img->render(destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string keyName, float destX, float destY)
{
	image* img = this->findImage(keyName);

	if (img) img->frameRender(destX, destY);
}

void imageManager::frameRender(string keyName, float destX, float destY, int currentFrameX, int currentFrameY)
{
	image* img = this->findImage(keyName);

	if (img) img->frameRender(destX, destY, currentFrameX, currentFrameY);
}

void imageManager::alphaRender(string keyName, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaRender(alpha);
}

void imageManager::alphaRender(string keyName, float destX, float destY, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaRender(destX, destY, alpha);
}

void imageManager::alphaRender(string keyName, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaRender(destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::alphaFrameRender(string keyName, float destX, float destY, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaFrameRender(destX, destY, alpha);
}

void imageManager::alphaFrameRender(string keyName, float destX, float destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = this->findImage(keyName);

	if (img) img->alphaFrameRender(destX, destY, currentFrameX, currentFrameY, alpha);
}
#endif