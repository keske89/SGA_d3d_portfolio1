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
	STAGE_TYPE m_Type;			//�������� Ÿ��
	cSphere* m_pSphere;			//�������� ��ü
	cWorldTile* m_pTile[20];	//�������� Ÿ��
	cWMStarBoard* m_pStarBoard;		//�������� ����
	cWMStageNum* m_pStageNum[3];	//�������� ��ȣ

	bool m_bAnimation;			//���ϸ��̼� 
	cWorldMapCar* m_pCar;		//�浹����

	vector<cWorldTile*> m_vecTile; //Tile ������ ����

	vector<cPath*> m_vecPath;	//path ������ ����
	D3DXVECTOR3 m_NextPos;		//path ���� ������
	PATH_TYPE m_pathType;

	POINT m_Stage;		//stage number x,y

	int m_nStar;

public:
	cWorldStage();
	virtual ~cWorldStage();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	//Animation
	void AnimationStart(bool ani);
	void SetAnimation(bool ani) { m_bAnimation = ani; }

	void setType(STAGE_TYPE type) { m_Type = type; }
	//PATH�� setter
	void SetPathType(PATH_TYPE type) { m_pathType = type; }
	void SetNextPos(D3DXVECTOR3 pos) { m_NextPos = pos; }

	//�浹�� getter
	cSphere* getSphere() { return m_pSphere; }

	void setCar(cWorldMapCar* pCar) { m_pCar = pCar; }
	void setStageNum(POINT stage) { m_Stage = stage; }

	void setStar(int star) { m_nStar = star; }
};

