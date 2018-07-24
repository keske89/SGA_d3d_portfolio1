#pragma once

class cChef;
class cStageObjManager;

class cCollision
{
private:
	cChef*											m_pPlayer[2];
	cStageObjManager*								m_pSOM;

	int												m_nListSize;
	int												m_nNewObjSize;

	list<cIGObj*>									m_objList;
	list<cIGObj*>									m_foodList;
	list<cIGObj*>::iterator							m_iterList;
	list<cIGObj*>::reverse_iterator					m_riterList;

	map<pair<int, int>, vector<cIGObj*>>			m_mapStaticObject;
	map<pair<int, int>, vector<cIGObj*>>::iterator	m_iterStaticObject;

	map<cIGObj*, bool>								m_mapDynamicObject;
	map<cIGObj*, bool>::iterator					m_iterDynamicObject;

	map<pair<int, int>, int>						m_mapIsBlockedData;
	map<pair<int, int>, int>::iterator				m_IterBlockedData;
public:
	cCollision();
	~cCollision();

	void Setup();
	void Update();

	void ListUpdate();
	bool PlayerPlayerCollision(D3DXVECTOR3& pos1, D3DXVECTOR3& pos2, D3DXVECTOR3& dir1, D3DXVECTOR3& dir2);
	bool PlayerWallCollisionX(int moveX, D3DXVECTOR3& pos, D3DXVECTOR3& dir);
	bool PlayerWallCollisionZ(int moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir);
	bool PlayerWallVertexCollision(int moveX, int moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir);
	cIGObj* PlayerDetectObject(int playerNum);
	cIGObj* DetectObject(int playerNum);
	void StaticLineXCollision(int playerNum, int keyFirst, int keySecond, int moveX, D3DXVECTOR3& pos);
	void StaticLineZCollision(int playerNum, int keyFirst, int keySecond, int moveZ, D3DXVECTOR3& pos);
	void StaticVertexCollision(int playerNum, int keyFirst, int keySecond);
	void DinamicCollision(int playerNum, int keyFirst, int keySecond);
	bool DetectMovement(int& moveX, int& moveZ, D3DXVECTOR3 dir);
	float GetDistance(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);

	inline void setPlayerMemoryAddressLink(int playerNum, cChef* address) { m_pPlayer[playerNum] = address; }
	inline void setStageObjManagerMemoryAddressLink(cStageObjManager* address) { m_pSOM = address; }
	inline void setMapIsBlockedData(map<pair<int, int>, int> data) { m_mapIsBlockedData = data; }
};

