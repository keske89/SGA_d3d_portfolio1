// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <atlstr.h>
#include <time.h>

using namespace std;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define SAFE_DELETE(p)			{ if (p) delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(p)	{ if (p) delete [] p; p = NULL; }
#define SAFE_RELEASE(p)			{ if (p) p->Release(); p = NULL; }
#define KEYMANAGER cKeyManager::getSingleton()
#define SOUNDMANAGER cSoundManager::getSingleton()
#define WINSIZEX 1280
#define WINSIZEY 760

//WM
#define SAFE_OBJRELEASE(p)		{ if (p) p->release(); SAFE_DELETE(p);}

extern HWND g_hWnd;

#define SINGLETONE(class_name) \
private: \
	class_name(); \
	~class_name(); \
public: \
	static class_name* GetInstance() \
	{ \
		static class_name instance; \
		return &instance; \
	}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: varType Get##funName(void) { return varName; }\
public: void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_REF(varType, varName, funName)\
protected: varType varName;\
public: varType& Get##funName(void) { return varName; }\
public: void Set##funName(varType& var) { varName = var; }


struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_TEX1
	};
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};
};

//WM
struct ST_WM_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	ST_WM_PC_VERTEX() {}
	ST_WM_PC_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c) : p(_p), c(_c) {}

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct ST_WM_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR3 t;

	ST_WM_PNT_VERTEX() {}
	ST_WM_PNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t) : p(_p), n(_n), t(_t) {}

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};

};

struct ST_RHWC_VERTEX
{
	ST_RHWC_VERTEX() {}
	ST_RHWC_VERTEX(D3DXVECTOR4 _p, D3DCOLOR _c) : p(_p), c(_c) {}

	D3DXVECTOR4 p;
	D3DCOLOR	c;

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE, };
};
//

struct ST_POS_SAMPLE
{
	int nFrame;
	D3DXVECTOR3	v;

	ST_POS_SAMPLE() : nFrame(0), v(0, 0, 0) {}
};

struct ST_ROT_SAMPLE
{
	int nFrame;
	D3DXQUATERNION	q;

	ST_ROT_SAMPLE() : nFrame(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};


struct ST_PARTICLE
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct ST_PARTICLE_ATTRIBUTE
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3 vAcceleration;
	D3DXVECTOR3	vGravity;
	D3DXVECTOR3 vGravityPos;
	float		fGravityForce;
	float		fGravityRadius;
	float		fStartRadius;
	float		fEndRadius;
	float		fRadiusSpeed;
	float		fCurrentRadiusSpeed;
	float		fLifeTime;
	float		fAge;
	D3DXCOLOR	color;
	D3DXCOLOR	colorFade;
	int			nLoop;
	int			nMaxLoop;
	bool		isAlive;
};

struct ST_PARTICLE_ATTRIBUTE_VARIABLE
{
	D3DXVECTOR3 vPosVar;
	D3DXVECTOR3 vVelocityVar;
	D3DXVECTOR3 vAccelerationVar;
	float		fStartRadiusVar;
	float		fEndRadiusVar;
	float		fRadiusSpeedVar;
	float		fLifeTimeVar;
};

struct ST_PARTICLE_INFO
{
	LPDIRECT3DTEXTURE9				pTexture;
	ST_PARTICLE_ATTRIBUTE			origAttribute;
	ST_PARTICLE_ATTRIBUTE_VARIABLE	varAttribute;
	float		fParticleSize;
	int			nParticleCount;
};

struct ST_PCT_VERTEX
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1
	};
};

struct ST_EFFECT
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXVECTOR3 dir;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 mot;
	bool isRX;
	bool isRY;
	bool isRZ;
	bool isSphere;
	float height;
	float time;
	float sc0, sc1, sc2;
	float sp0, sp1, sp2;
	float ms0, ms1, ms2;
	int a0, a1, a2;

	void SetScale(float f0, float f1, float f2)
	{
		sc0 = f0; sc1 = f1; sc2 = f2;
	}

	void SetSpeed(float f0, float f1, float f2)
	{
		sp0 = f0; sp1 = f1; sp2 = f2;
	}

	void SetMotorSpeed(float f0, float f1, float f2)
	{
		ms0 = f0; ms1 = f1; ms2 = f2;
	}

	void SetAlpha(int n0, int n1, int n2)
	{
		a0 = n0; a1 = n1; a2 = n2;
	}

	void SetRandomRot(bool x, bool y, bool z)
	{
		isRX = x; isRY = y; isRZ = z;
	}
};

enum eFontType
{
	FT_DEFAULT,
	FT_TIME,
	FT_QUEST,
};

#include "cDeviceManager.h"
#include "cKeyManager.h"
#include "cTextureManager.h"
#include "cFontManager.h"
#include "cTimeManager.h"
#include "cSceneManager.h"
#include "cTextManager.h"
#include "cObjManager.h"
#include "cSoundManager.h"
//
#include "cIGObj.h"
#include "CommonMacroFunction.h"
//WM
#include "Assets.h"
#include "UIController.h"
#include "imageManager.h"
#include "textureManager.h"
#include "database.h"
#include "cParticleManager.h"
#include "cEffectObject.h"
//

extern POINT _ptMouse;

//WM
extern LPD3DXSPRITE g_sprite;
#define SPRITE g_sprite
extern POINT g_ptMouse;
#define MOUSE_POS g_ptMouse
//

//WM
inline RECT RectMake(float x, float y, float width, float height)
{
	RECT temp = { x, y, x + width, y + height };
	return temp;
}

inline RECT RectMakeCenter(float x, float y, float width, float height)
{
	return RectMake(x - width / 2, y - height / 2, width, height);
}
//

struct ST_UI_SIZE
{
	int nWidth;
	int nHeight;
	ST_UI_SIZE() : nWidth(0), nHeight(0) {}
	ST_UI_SIZE(int _nWidth, int _nHeight)
		: nWidth(_nWidth), nHeight(_nHeight) {}
};