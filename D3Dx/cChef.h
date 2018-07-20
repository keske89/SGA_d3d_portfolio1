#pragma once
#include"cChefAnimation.h"
#include"cChefRunPuff.h"
#include"cIGObj.h"

class cChefRoot;
class cStageObjManager;
class cCharacterControl;
class cCollision;


enum CHEF_STATE
{
	CHEF_STATE_IDLE,						//가만히 있는 상태
	CHEF_STATE_MOVE,						//움직이는 상태
	CHEF_STATE_BOOSTER_MOVE,				//부스터 상태
	CHEF_STATE_TRANCEPORT_IDLE,				//무엇인가를 들고 가만히 있는상태
	CHEF_STATE_TRANCEPORT_MOVE,				//무엇인가를 들고 움직이는 상태
	CHEF_STATE_CHOP,						//음식을 썰고 있는 상태
	CHEF_STATE_DISHWASHING,					//설거지를 하는 상태
	CHEF_STATE_ACTION						//무엇인가를 들 준비상태
};
class cChef :public cChefAnimation, public cActionDelegate
{
private:
	SYNTHESIZE_REF(cChefRoot *, m_pRoot, Root);
	cCharacterControl*		m_pControl;
	D3DMATERIAL9			m_stMtl;
	SYNTHESIZE_REF(D3DXVECTOR3, m_vPosition, Pos);
	SYNTHESIZE_REF(D3DXVECTOR3, m_vdir, Dir);
	SYNTHESIZE_REF(D3DXVECTOR3, m_vdirX, DirX);
	SYNTHESIZE_REF(D3DXVECTOR3, m_vdirZ, DirZ);
	SYNTHESIZE_REF(D3DXVECTOR3, m_vToGo, ToGo);
	SYNTHESIZE(cIGObj *, m_pInven, Inven);
	cIGObj *				m_pDetect;
	cStageObjManager*		m_pStageOBJ;
	SYNTHESIZE(float, m_fRadius, radius);

	LPD3DXMESH				m_pMesh;
	CHEF_STATE				m_eChefstate;
private:
	std::vector<cChefRunPuff *> m_vecPuff;
	std::vector<cChefRunPuff *>::iterator m_vecItPuff;
public:
	cChef();
	~cChef();
	void SetUp(IN D3DXVECTOR3 vPos,IN cCharacterControl * pControl = NULL);
	//void SetUp(IN D3DXVECTOR3 vPos,IN int ChageImageNum,IN cCharacterControl * pControl = NULL);
	void Relese();
	void Update();
	void Render();
	void SetMaterial();
	void SetDetect(IN cIGObj * _object) { m_pDetect = _object; }
	cIGObj* GetDetect() { return m_pDetect; }
	void setcStageObjManagerAdressLink(cStageObjManager* _StageObject) { m_pStageOBJ = _StageObject; }
	void runPuffCreate();
	void runPuffUpdate();
	void runPuffDelete(int num);
	virtual void OnAction(IN cIGObj* pSender) override;
	void SetChefAnimation(int state)
	{
		m_eChefstate = (CHEF_STATE)state;
	}
	CHEF_STATE GetCHEF_STATE() { return m_eChefstate; }
};

