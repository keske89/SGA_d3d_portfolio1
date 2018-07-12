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
	D3DXVECTOR3 st_vDirection;
	D3DXVECTOR3	st_vDirectionX;
	D3DXVECTOR3	st_vDirectionZ;
	D3DXVECTOR3	st_vPosition;
	D3DXVECTOR3 st_vBooster;
	D3DXMATRIX	st_matPlayer;
	float		st_fAngle;
	float		st_fCharacterBOOSTERSpeed;
	float		st_fFrictional;
	BOOL		st_BisBooster;
	ST_PLAYER_ATTRIBUTE()
		: st_vDirection(0, 0, 0)
		, st_vDirectionX(0, 0, 0)
		, st_vDirectionZ(0, 0, 0)
		, st_vBooster(0, 0, 0)
		, st_fAngle(0.0f)
		, st_fCharacterBOOSTERSpeed(0)
		, st_fFrictional(0)
		, st_BisBooster(false)
	{
		D3DXMatrixIdentity(&st_matPlayer);
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
	std::map<pair<int, int>, bool> m_mapSatgeIndex;
public:
	cCharacterControl();
	~cCharacterControl();
	void AddcCharacter(cChef * _Chef);
	void SetPlaterMod(int num);
	void SetUp(std::map<pair<int, int>, bool> StageIndex);
	void SetUp();
	void Update();
	void Render();
	void Control();
	void ControlAction();
	void Control1P();
	void Control2P();
	void Move();
	void Booster();
	ST_PLAYER_ATTRIBUTE* GetAtribute(cChef * _Chef)
	{
		if (m_vecCharacter[0] == _Chef)
		{
			return &m_StPlayerAtrribute[0];
		}
		else if (m_vecCharacter[1] == _Chef)
		{
			return &m_StPlayerAtrribute[1];
		}
	}
};

