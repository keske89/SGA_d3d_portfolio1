#pragma once
#include"cObjLoader.h"
enum CHEF_STATE
{
	CHEF_STATE_IDLE,						//������ �ִ� ����
	CHEF_STATE_MOVE,						//�����̴� ����
	CHEF_STATE_TRANCEPORT_IDLE,				//�����ΰ��� ��� ������ �ִ»���
	CHEF_STATE_TRANCEPORT_MOVE,				//�����ΰ��� ��� �����̴� ����
	CHEF_STATE_CHOP,						//������ ��� �ִ� ����
	CHEF_STATE_DISHWASHING					//�������� �ϴ� ����
};
class cChefRoot
{
protected:
	D3DXMATRIX					m_matWorldTM;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DMATERIAL9				m_stMtl;
	SYNTHESIZE(LPD3DXMESH, m_pMesh, mesh);
	SYNTHESIZE_REF(std::vector<cChefRoot*>, m_vecChild, Child);
	CHEF_STATE				m_eChefstate;
protected:
	SYNTHESIZE(D3DXMATRIX, m_matLocalTM, matLocal);
	SYNTHESIZE(D3DXVECTOR3, m_vLocalPos, Pos);
	float m_fRotX, RotX;
	float m_fRotY, RotY;
	SYNTHESIZE(float, m_fRotDeltaX, RotDeltaX);
	SYNTHESIZE(float, m_fRotDeltaY, RotDeltaY);
	SYNTHESIZE(D3DXMATRIX*, m_pParentWorldTM, ParentWorldTM);


public:
	cChefRoot();
	~cChefRoot();
	void AddChild(cChefRoot* pChild);
	void Destroy();
	virtual void SetUp();
	virtual void Update();
	virtual void Render();
	void SetChefAnimation(int state)
	{
		m_eChefstate = (CHEF_STATE)state;
	}
	CHEF_STATE GetCHEF_STATE() { return m_eChefstate; }
	virtual void ImageChange();

};

