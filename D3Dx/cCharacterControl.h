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

	PLAYERMOD					m_enmPlayerMod;				//임시 모드
	BOOL						m_Bswitch;					//싱글모드일시 사용
	ST_PLAYER_ATTRIBUTE			m_StPlayerAtrribute[2];		//각각의 캐릭터 움직임에 필요한 변수들의 모임
	std::map<pair<int, int>, bool> m_mapSatgeIndex;			//맵 인데스 정보
public:
	cCharacterControl();
	~cCharacterControl();
	void AddcCharacter(IN cChef * _Chef);
	void SetPlaterMod(int num);
	void SetUp(IN std::map<pair<int, int>, bool> StageIndex);
	void SetUp();
	void Update();
	void Render();
	void Control();
	void ControlAction();
	void Control1P();
	void Control2P();
	void SetPos1P(D3DXVECTOR3 _pos);
	void SetPos2P(D3DXVECTOR3 _pos);
	void Move();
	void Booster();
	BOOL CheckChefIntersect();
	void ChefIntersectMove();
	ST_PLAYER_ATTRIBUTE* GetAtribute(IN cChef * _Chef)
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

