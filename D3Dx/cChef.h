#pragma once
#include"cChefAnimation.h"
class cChefRoot;
class cStageObjManager;
class cIGObj;
class cCharacterControl;

class cChef :public cChefAnimation
{
private:
	SYNTHESIZE_REF(cChefRoot *, m_pRoot, Root);
	cCharacterControl*		m_pControl;
	D3DMATERIAL9			m_stMtl;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Pos);
	cIGObj *				m_pObjRoot;
	cStageObjManager*		m_pStageOBJ;
public:
	cChef();
	~cChef();
	void SetUp(D3DXVECTOR3 vPos, cCharacterControl * m_pControl);
	//void SetUp(cCharacterControl * m_pControl); 방식에 따라 전환
	void Update();
	void Render();
	void SetMaterial();
	cIGObj * GetcIGObject();
	void SetcIGObject(cIGObj * _object);
	void setcStageObjManagerAdressLink(cStageObjManager* _StageObject) { m_pStageOBJ = _StageObject; }
};

