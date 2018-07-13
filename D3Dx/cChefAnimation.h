#pragma once
class cChefRoot;
class cChefAnimation
{
private:
	float  m_fRotX, m_fRotY, m_fRotZ;
	float m_fRotDeltaX, m_fRotDeltaY, m_fRotDeltaZ;
public:
	cChefAnimation();
	virtual	~cChefAnimation();
	void Animation(cChefRoot * _cChefRoot);
	D3DXMATRIX*  KnifeLocal();
};

