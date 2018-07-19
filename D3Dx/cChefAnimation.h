#pragma once
class cChefRoot;
class cChef;
class cChefAnimation
{
private:
	float	m_fRotX;
	float	m_fRotY; 
	float	m_fRotZ;
	float	m_fRotDeltaX; 
	float	m_fRotDeltaY; 
	float	m_fRotDeltaZ;
public:
	cChefAnimation();
	~cChefAnimation();
	void Animation(cChefRoot * _cChefRoot, int _CHEF_STATE);
	D3DXMATRIX*  KnifeLocal();
};

