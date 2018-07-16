#pragma once

#ifndef D3DDEVICE
#define D3DDEVICE g_pD3DDevice
#endif

class image
{
#ifdef UNICODE
private:
	typedef struct tagImageInfo
	{
		float				x;			//이미지 X좌표 (left)
		float				y;			//이미지 Y좌표 (top)
		int					width;		//가로 크기(이미지)
		int					height;		//세로 크기(이미지)

		int					currentFrameX;	//현재 프레임 X
		int					currentFrameY;	//현재 프레임 Y
		int					maxFrameX;		//최대 프레임 X
		int					maxFrameY;		//최대 프레임 Y
		int					frameWidth;		//프레임 가로크기
		int					frameHeight;	//프레임 세로크기

		tagImageInfo()
		{
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	static LPD3DXSPRITE		_sprite;
	LPIMAGE_INFO			_imageInfo;
	wstring					_fileName;

	D3DXMATRIX				_worldMatrix;

public:
	image();
	~image();

	HRESULT init(float width, float height);
	HRESULT init(const WCHAR* fileName);
	HRESULT init(const WCHAR* fileName, float x, float y);

	HRESULT initFrame(const WCHAR* fileName, float x, float y, int frameX, int frameY);
	HRESULT initFrame(const WCHAR* fileName, int frameX, int frameY);

	void release();

	void render();
	void render(float destX, float destY);
	void render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);

	void frameRender(float destX, float destY);
	void frameRender(float destX, float destY, int currentFrameX, int currentFrameY);

	void alphaRender(BYTE alpha);
	void alphaRender(float destX, float destY, BYTE alpha);
	void alphaRender(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, BYTE alpha);

	void alphaFrameRender(float destX, float destY, BYTE alpha);
	void alphaFrameRender(float destX, float destY, int currentFrameX, int currentFrameY, BYTE alpha);

	inline float getWidth(void) { return _imageInfo->width; }
	inline float getHeight(void) { return _imageInfo->height; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline void setCurrentFrameX(int currentFrameX) { _imageInfo->currentFrameX = currentFrameX; }
	inline void setCurrentFrameY(int currentFrameY) { _imageInfo->currentFrameY = currentFrameY; }

	inline int getCurrentFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getCurrentFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline void setWorldMatrix(D3DXMATRIX world) { _worldMatrix = world; }
	inline D3DXMATRIX getWorldMatrix() { return _worldMatrix; }
#else
private:
	typedef struct tagImageInfo
	{
		LPD3DXSPRITE		sprite;
		float				x;			//이미지 X좌표 (left)
		float				y;			//이미지 Y좌표 (top)
		int					width;		//가로 크기(이미지)
		int					height;		//세로 크기(이미지)

		int					currentFrameX;	//현재 프레임 X
		int					currentFrameY;	//현재 프레임 Y
		int					maxFrameX;		//최대 프레임 X
		int					maxFrameY;		//최대 프레임 Y
		int					frameWidth;		//프레임 가로크기
		int					frameHeight;	//프레임 세로크기

		tagImageInfo()
		{
			sprite = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	string			_fileName;

public:
	image();
	~image();

	HRESULT init(float width, float height, BOOL isAlpha = FALSE);
	HRESULT init(const CHAR* fileName, float width, float height, BOOL isAlpha = FALSE);
	HRESULT init(const CHAR* fileName, float x, float y, float width, float height, BOOL isAlpha = FALSE);

	HRESULT initFrame(const CHAR* fileName, float x, float y, float width, float height, int frameX, int frameY, BOOL isAlpha = FALSE);
	HRESULT initFrame(const CHAR* fileName, float width, float height, int frameX, int frameY, BOOL isAlpha = FALSE);

	void release();

	void render();
	void render(float destX, float destY);
	void render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);

	void frameRender(float destX, float destY);
	void frameRender(float destX, float destY, int currentFrameX, int currentFrameY);

	void alphaRender(BYTE alpha);
	void alphaRender(float destX, float destY, BYTE alpha);
	void alphaRender(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, BYTE alpha);

	void alphaFrameRender(float destX, float destY, BYTE alpha);
	void alphaFrameRender(float destX, float destY, int currentFrameX, int currentFrameY, BYTE alpha);

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }
#endif
};

