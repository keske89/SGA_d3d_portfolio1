#pragma once

#include "IDisplayObject.h"

class cWorldMapObj;

enum TILE_TYPE
{
	TILE_GRASS,
	TILE_WATER,
	TILE_SAND,
	TILE_END
};

class cWorldTile : public IDisplayObject
{
private:
	TILE_TYPE m_Type;
	cWorldMapObj* m_pTile;
	bool m_bAnimation;

	float m_ani;
	int m_nIdx;

public:
	cWorldTile();
	virtual ~cWorldTile();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Animation(int idx);

	void SetType(TILE_TYPE type) { m_Type = type; }
	void SetAnimation(bool ani, int idx = 0) { m_nIdx = idx; m_bAnimation = ani; }
};

