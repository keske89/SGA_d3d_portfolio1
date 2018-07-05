#pragma once
class cCharacter;
class cChefRoot;
#define CharacterSpeed 0.1f
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
	//===============================================================================
	// 캐릭터 조정
	//===============================================================================
	D3DXVECTOR3	m_vDirectionX;
	D3DXVECTOR3	m_vDirectionZ;

	D3DXVECTOR3	m_vDirection1P;
	D3DXVECTOR3	m_vDirection2P;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition1P, Position1P);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition2P, Position2P);
	float							m_fangle1P;
	float							m_fangle2P;
public:
	cCharacterControl();
	~cCharacterControl();
	void SetUp();
	void Update();
	void Render();
	void Control();
	void ControlAction();
	void Move();
	void AddcCharacter(cCharacter * Chef);
	void SetPlaterMod(int num);
};

