#pragma once
#include "IDisplayObject.h"

class cWorldMapObj;

enum STAGENUM_TYPE
{
	STAGENUM_0,
	STAGENUM_1,
	STAGENUM_2,
	STAGENUM_3,
	STAGENUM_4,
	STAGENUM_5,
	STAGENUM_6,
	STAGENUM_DASH

};

class cWMStageNum : public IDisplayObject
{
private:
	STAGENUM_TYPE m_Type;
	cWorldMapObj * m_pNum;

public:
	cWMStageNum();
	virtual ~cWMStageNum();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetType(int type) { m_Type = (STAGENUM_TYPE)type; }
};

