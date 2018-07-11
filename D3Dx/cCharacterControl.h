#pragma once
class cChef;
class cChefRoot;
class cChefAnimation;
#define CharacterSpeed 0.1f
enum PLAYERMOD
{
	PLAYERMOD_DEFLAT,
	PLAYERMOD_PLAY1P,
	PLAYERMOD_PLAY2P
};

struct ST_PLAYER_ATTRIBUTE
{
	D3DXVECTOR3 St_vDirection;
	D3DXVECTOR3	St_vDirectionX;
	D3DXVECTOR3	St_vDirectionZ;
	D3DXVECTOR3	St_vPosition;
	D3DXMATRIX	ST_matPlayer;
	float		St_fAngle;
	BOOL		ST_BisBooster;
	ST_PLAYER_ATTRIBUTE()
		: St_vDirection(0, 0, 0)
		, St_vDirectionX(0, 0, 0)
		, St_vDirectionZ(0, 0, 0)
		, St_vPosition(0, 0, 0)
		, St_fAngle(0.0f)
		, ST_BisBooster(false)
	{
		D3DXMatrixIdentity(&ST_matPlayer);
	}
};
class cCharacterControl
{
private:
	std::vector<cChef *>	m_vecCharacter;

	PLAYERMOD					m_enmPlayerMod;
	BOOL						m_Bswitch;
	ST_PLAYER_ATTRIBUTE			m_StPlayerAtrribute[2];
	D3DXVECTOR3					m_vbooster;
	float						m_fCharacterBOOSTERSpeed;
	float						m_fFrictional;
	cChefAnimation *			m_pAnimation;
public:
	cCharacterControl();
	~cCharacterControl();
	void AddcCharacter(cChef * _Chef);
	void SetPlaterMod(int num);
	void SetUp();
	void Update();
	void Render();
	void Control();
	void ControlAction();
	void Move();
	void Booster(D3DXVECTOR3 pos);
};

