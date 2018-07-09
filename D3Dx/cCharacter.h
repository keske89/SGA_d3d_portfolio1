#pragma once
class cChefRoot;
class cIGObj;
class cCharacterControl;
enum CHEF_STATE
{
	CHEF_STATE_IDLE,						//������ �ִ� ����
	CHEF_STATE_MOVE,						//�����̴� ����
	CHEF_STATE_TRANCEPORT_IDLE,				//�����ΰ��� ��� ������ �ִ»���
	CHEF_STATE_TRANCEPORT_MOVE,				//�����ΰ��� ��� �����̴� ����
	CHEF_STATE_CHOP,						//������ ��� �ִ� ����
	CHEF_STATE_DISHWASHING					//�������� �ϴ� ����
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
	//void SetUp(cCharacterControl * m_pControl); ��Ŀ� ���� ��ȯ
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

