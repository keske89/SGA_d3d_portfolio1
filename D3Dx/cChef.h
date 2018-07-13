#pragma once
#include"cChefAnimation.h"
#include"cChefRunPuff.h"
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
	SYNTHESIZE_REF(D3DXVECTOR3, m_vPosition, Pos);
	cIGObj *				m_pObjRoot;
	cStageObjManager*		m_pStageOBJ;
	SYNTHESIZE(float, m_fRadius, radius);

	LPD3DXMESH				m_pMesh;
	BOOL					m_bRender;
private:
	std::list<cChefRunPuff *> m_vecPuff;
public:
	cChef();
	~cChef();
	void SetUp(D3DXVECTOR3 vPos, cCharacterControl * m_pControl = NULL);
	void Relese();
	void Update();
	void Render();
	void SetMaterial();
	cIGObj * GetcIGObject();
	void SetcIGObject(cIGObj * _object);
	void setcStageObjManagerAdressLink(cStageObjManager* _StageObject) { m_pStageOBJ = _StageObject; }

	void runPuffCreate();
};

