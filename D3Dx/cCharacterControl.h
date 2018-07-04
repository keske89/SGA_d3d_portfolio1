#pragma once
class cCharacter;
class cChefRoot;
enum PLAYERMOD
{
	PLAYERMOD_DEFLAT,
	PLAYERMOD_PLAY1P,
	PLAYERMOD_PLAY2P
};

class cCharacterControl
{
private:
	std::vector<cCharacter *>	m_vecCharacter;

	D3DXMATRIX					m_mat1P;
	D3DXMATRIX					m_mat2P;
	PLAYERMOD					m_enmPlayerMod;
	BOOL						m_Bswitch;
private:
	SYNTHESIZE(float, m_fRotY1P, Angle1P);
	SYNTHESIZE(float, m_fRotY2P, Angle2P);
	D3DXVECTOR3	m_vDirection1P;
	D3DXVECTOR3	m_vDirection2P;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition1P, Position1P);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition2P, Position2P);
public:
	cCharacterControl();
	~cCharacterControl();
	void SetUp();
	void Update();
	void Render();
	void Control();
	void Move();
	void AddcCharacter(cCharacter * Chef);
	D3DXMATRIX * Getworld(D3DXVECTOR3 positon, cCharacter * Chef = NULL);
	void SetPlaterMod(int num);
};

