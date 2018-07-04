#pragma once
class cChefRoot;
class cIGObj;
class cCharacterControl;
enum CHEF_STATE
{
	CHEF_STATE_IDLE,			//������ �ִ� ����
	CHEF_STATE_MOVE,			//�����̴� ����
	CHEF_STATE_BOOSTER,			//�ν��� ����
	CHEF_STATE_CHOP,			//������ ��� �ִ� ����
	CHEF_STATE_DISHWASHING,		//�������� �ϴ� ����
	CHEF_STATE_TRANCEPORTMOVE	//�����ΰ��� ��� ����ϴ� ����
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
	//void SetUp(cCharacterControl * m_pControl); ��Ŀ� ���� ��ȯ
	void Update();
	void Render();
	void SetMaterial();
};

