#pragma once

#include "IDisplayObject.h"
#include "cWMDefinition.h"

class cSphere;
class cWorldTile;
class cPath;
class cWorldMapCar;
class cWMStarBoard;
class cWMStageNum;

class UIObject;

enum PATH_TYPE;

enum STAGE_TYPE
{
	STAGE_GRASS,
	STAGE_WATER,
	STAGE_SAND,
	STAGE_END
};

class cWorldStage : public IDisplayObject
{
private:
	STAGE_TYPE m_Type;			//스테이지 타입
	cSphere* m_pSphere;			//스테이지 구체
	cWorldTile* m_pTile[20];	//스테이지 타일
	cWMStarBoard* m_pStarBoard;		//스테이지 보드
	cWMStageNum* m_pStageNum[3];	//스테이지 번호

	bool m_bAnimation;			//에니메이션 
	cWorldMapCar* m_pCar;		//충돌감지

	vector<cWorldTile*> m_vecTile; //Tile 관리용 벡터

	vector<cPath*> m_vecPath;	//path 관리용 벡터
	D3DXVECTOR3 m_NextPos;		//path 다음 포지션
	PATH_TYPE m_pathType;

	POINT m_Stage;		//stage number x,y

	int m_nStar;

public:
	cWorldStage();
	virtual ~cWorldStage();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	//Animation
	void AnimationStart(bool ani);
	void SetAnimation(bool ani) { m_bAnimation = ani; }

	void setType(STAGE_TYPE type) { m_Type = type; }
	//PATH용 setter
	void SetPathType(PATH_TYPE type) { m_pathType = type; }
	void SetNextPos(D3DXVECTOR3 pos) { m_NextPos = pos; }

	//충돌용 getter
	cSphere* getSphere() { return m_pSphere; }

	void setCar(cWorldMapCar* pCar) { m_pCar = pCar; }
	void setStageNum(POINT stage) { m_Stage = stage; }

	void setStar(int star) { m_nStar = star; }
};

