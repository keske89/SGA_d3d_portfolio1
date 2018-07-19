#pragma once
#include "IDisplayObject.h"

class cWorldMapObj;

enum PATH_TYPE
{
	PATH_STRAIGHT,
	PATH_CURVED,
	PATH_END
};

class cPath : public IDisplayObject
{
private:
	cWorldMapObj * m_pPath;
	PATH_TYPE m_Type;

	bool m_bAnimation;
	float m_ani;

public:
	cPath();
	virtual ~cPath();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Animation();

	void setTrack(D3DXVECTOR3 From, D3DXVECTOR3 To);

	void SetType(PATH_TYPE type) { m_Type = type; }
	void SetAnimation(bool ani) { m_bAnimation = ani; }
};

