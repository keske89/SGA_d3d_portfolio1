#pragma once
class cChefRoot;
class cIGObj;
class cCharacterControl;
enum CHEF_STATE
{
	CHEF_STATE_IDLE,			//가만히 있는 상태
	CHEF_STATE_MOVE,			//움직이는 상태
	CHEF_STATE_BOOSTER,			//부스터 상태
	CHEF_STATE_CHOP,			//음식을 썰고 있는 상태
	CHEF_STATE_DISHWASHING,		//설거지를 하는 상태
	CHEF_STATE_TRANCEPORTMOVE	//무엇인가를 들고 운반하는 상태
};
class cCharacter
{
private:
	SYNTHESIZE_REF(cChefRoot *,m_pRoot,Root);
	cCharacterControl*		m_pControl;
	D3DMATERIAL9			m_stMtl;
	D3DXVECTOR3				m_vPosition;
	SYNTHESIZE(D3DXMATRIX,m_world,world);
public:
	cCharacter();
	~cCharacter();
	void SetUp(D3DXVECTOR3 vPos,cCharacterControl * m_pControl);
	//void SetUp(cCharacterControl * m_pControl); 방식에 따라 전환
	void Update();
	void Render();
	void SetMaterial();
};

