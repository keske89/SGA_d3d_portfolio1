#pragma once
class cChefRoot;
class cIGObj;
class cCharacterControl;
enum CHEF_STATE
{
	CHEF_STATE_IDLE,						//가만히 있는 상태
	CHEF_STATE_MOVE,						//움직이는 상태
	CHEF_STATE_TRANCEPORT_IDLE,				//무엇인가를 들고 가만히 있는상태
	CHEF_STATE_TRANCEPORT_MOVE,				//무엇인가를 들고 움직이는 상태
	CHEF_STATE_CHOP,						//음식을 썰고 있는 상태
	CHEF_STATE_DISHWASHING					//설거지를 하는 상태
};
class cCharacter
{
private:
	SYNTHESIZE_REF(cChefRoot *, m_pRoot, Root);
	cCharacterControl*		m_pControl;
	D3DMATERIAL9			m_stMtl;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Pos);
	CHEF_STATE				m_eChefState;
	cIGObj * m_pObjRoot;
public:
	cCharacter();
	~cCharacter();
	void SetUp(D3DXVECTOR3 vPos, cCharacterControl * m_pControl);
	//void SetUp(cCharacterControl * m_pControl); 방식에 따라 전환
	void Update();
	void Render();
	void SetMaterial();
	void SetCHEF_STATE(int state)
	{
		m_eChefState = (CHEF_STATE)state;
	}
	CHEF_STATE GetCHEF_STATE() { return m_eChefState; }
	cIGObj * GetcIGObject();
	void SetcIGObject(cIGObj * _object);
	void setcIGObjectAdressLink(cIGObj* _object) { m_pObjRoot = _object; }
};

