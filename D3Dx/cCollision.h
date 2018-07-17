#pragma once

class cChef;
class cStageObjManager;

class cCollision
{
private:
	cChef*											m_pPlayer[2];
	cStageObjManager*								m_pSOM;

	int												m_nListSize;
	list<cIGObj*>									m_objList;
	list<cIGObj*>::iterator							m_iterList;
	map<pair<int, int>, vector<cIGObj*>>			m_mapObject;
	map<pair<int, int>, vector<cIGObj*>>::iterator	m_iterObject;
	map<pair<int, int>, int>						m_mapIsBlockedData;
	map<pair<int, int>, int>::iterator				m_IterBlockedData;
public:
	cCollision();
	~cCollision();

	void Setup();
	void Update();

	bool PlayerWallCollisionX(int playerNum, int moveX, D3DXVECTOR3& pos);
	bool PlayerWallCollisionZ(int playerNum, int moveZ, D3DXVECTOR3& pos);
	void PlayerWallVertexCollision(int playerNum, D3DXVECTOR3& pos);
	cIGObj* PlayerDetectObject(int playerNum);
	void StaticLineXCollision(int playerNum, int keyFirst, int keySecond, int moveX, D3DXVECTOR3& pos);
	void StaticLineZCollision(int playerNum, int keyFirst, int keySecond, int moveZ, D3DXVECTOR3& pos);
	void StaticVertexCollision(int playerNum, int keyFirst, int keySecond);
	void DinamicCollision(int playerNum, int keyFirst, int keySecond);
	bool DetectMovement(int playerNum, int& moveX, int& moveZ);
	float GetDistance(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);

	inline void setPlayerMemoryAddressLink(int playerNum, cChef* address) { m_pPlayer[playerNum] = address; }
	inline void setStageObjManagerMemoryAddressLink(cStageObjManager* address) { m_pSOM = address; }
	inline void setMapIsBlockedData(map<pair<int, int>, int> data) { m_mapIsBlockedData = data; }
};

