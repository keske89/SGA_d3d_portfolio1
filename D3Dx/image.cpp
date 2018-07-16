#include "stdafx.h"
#include "image.h"

LPD3DXSPRITE image::_sprite = NULL;

image::image()
	: _imageInfo(NULL)
	, _fileName(_T(""))
{
	D3DXMatrixIdentity(&_worldMatrix);
}


image::~image()
{
}

HRESULT image::init(float width, float height)
{
	if (!_sprite) D3DXCreateSprite(D3DDEVICE, &_sprite);

	if (_imageInfo) this->release();

	_imageInfo = new IMAGE_INFO;
	if (!_sprite)
	{
		this->release();
		return E_FAIL;
	}
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = _T("");

	return S_OK;
}

HRESULT image::init(const WCHAR* fileName)
{
	if (!_sprite) D3DXCreateSprite(D3DDEVICE, &_sprite);

	if (_imageInfo) this->release();

	_imageInfo = new IMAGE_INFO;
	if (!_sprite)
	{
		this->release();
		return E_FAIL;
	}
	TEXTUREMANAGER->addTexture(fileName, fileName);
	_imageInfo->width = TEXTUREMANAGER->find(fileName)->textureInfo.Width;
	_imageInfo->height = TEXTUREMANAGER->find(fileName)->textureInfo.Height;

	_fileName = fileName;

	return S_OK;
}

HRESULT image::init(const WCHAR* fileName, float x, float y)
{
	if (!_sprite) D3DXCreateSprite(D3DDEVICE, &_sprite);

	if (_imageInfo) this->release();

	_imageInfo = new IMAGE_INFO;
	if (!_sprite)
	{
		this->release();
		return E_FAIL;
	}
	TEXTUREMANAGER->addTexture(fileName, fileName);
	_imageInfo->width = TEXTUREMANAGER->find(fileName)->textureInfo.Width;
	_imageInfo->height = TEXTUREMANAGER->find(fileName)->textureInfo.Height;
	_imageInfo->x = x;
	_imageInfo->y = y;

	_fileName = fileName;

	return S_OK;
}

HRESULT image::initFrame(const WCHAR* fileName, float x, float y, int frameX, int frameY)
{
	if (!_sprite) D3DXCreateSprite(D3DDEVICE, &_sprite);

	if (_imageInfo) this->release();

	_imageInfo = new IMAGE_INFO;
	if (!_sprite)
	{
		this->release();
		return E_FAIL;
	}
	TEXTUREMANAGER->addTexture(fileName, fileName);
	_imageInfo->width = TEXTUREMANAGER->find(fileName)->textureInfo.Width;
	_imageInfo->height = TEXTUREMANAGER->find(fileName)->textureInfo.Height;
	_imageInfo->x = x;
	_imageInfo->y = y;

	_imageInfo->frameWidth = _imageInfo->width / frameX;
	_imageInfo->frameHeight = _imageInfo->height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	_fileName = fileName;

	return S_OK;
}

HRESULT image::initFrame(const WCHAR* fileName, int frameX, int frameY)
{
	if (!_sprite) D3DXCreateSprite(D3DDEVICE, &_sprite);

	if (_imageInfo) this->release();

	_imageInfo = new IMAGE_INFO;
	if (!_sprite)
	{
		this->release();
		return E_FAIL;
	}
	TEXTUREMANAGER->addTexture(fileName, fileName);
	_imageInfo->width = TEXTUREMANAGER->find(fileName)->textureInfo.Width;
	_imageInfo->height = TEXTUREMANAGER->find(fileName)->textureInfo.Height;

	_imageInfo->frameWidth = _imageInfo->width / frameX;
	_imageInfo->frameHeight = _imageInfo->height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	_fileName = fileName;

	return S_OK;
}

void image::release()
{
	SAFE_RELEASE(_sprite);

	if (_imageInfo)
	{
		SAFE_DELETE(_imageInfo);
	}
}

void image::render()
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(0, 0, _imageInfo->width, _imageInfo->height);
	D3DXVECTOR3 pos(_imageInfo->x, _imageInfo->y, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::render(float destX, float destY)
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(0, 0, _imageInfo->width, _imageInfo->height);
	D3DXVECTOR3 pos(destX, destY, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(sourX, sourY, sourWidth, sourHeight);
	D3DXVECTOR3 pos(destX, destY, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::frameRender(float destX, float destY)
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(_imageInfo->frameWidth * _imageInfo->currentFrameX,
		_imageInfo->frameHeight * _imageInfo->currentFrameY,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight);
	D3DXVECTOR3 pos(destX, destY, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::frameRender(float destX, float destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(_imageInfo->frameWidth * _imageInfo->currentFrameX,
		_imageInfo->frameHeight * _imageInfo->currentFrameY,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight);
	D3DXVECTOR3 pos(destX, destY, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::alphaRender(BYTE alpha)
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(0, 0, _imageInfo->width, _imageInfo->height);
	D3DXVECTOR3 pos(_imageInfo->x, _imageInfo->y, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha / (float)255);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::alphaRender(float destX, float destY, BYTE alpha)
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(0, 0, _imageInfo->width, _imageInfo->height);
	D3DXVECTOR3 pos(destX, destY, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha / (float)255);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::alphaRender(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, BYTE alpha)
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(sourX, sourY, sourWidth, sourHeight);
	D3DXVECTOR3 pos(destX, destY, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha / (float)255);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::alphaFrameRender(float destX, float destY, BYTE alpha)
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(_imageInfo->frameWidth * _imageInfo->currentFrameX,
		_imageInfo->frameHeight * _imageInfo->currentFrameY,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight);
	D3DXVECTOR3 pos(destX, destY, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha / (float)255);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}

void image::alphaFrameRender(float destX, float destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	_sprite->SetTransform(&_worldMatrix);

	RECT rc = RectMake(_imageInfo->frameWidth * _imageInfo->currentFrameX,
		_imageInfo->frameHeight * _imageInfo->currentFrameY,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight);
	D3DXVECTOR3 pos(destX, destY, 0);
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha / (float)255);
	_sprite->Draw(TEXTUREMANAGER->findTexture(_fileName),
		&rc,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&pos,
		color);

	_sprite->End();
}
