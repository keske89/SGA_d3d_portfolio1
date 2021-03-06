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

	map<pair<int, int>, int>						m_mapIsBlockedData;
	map<pair<int, int>, int>::iterator				m_IterBlockedData;
public:
	cCollision();
	~cCollision();

	void Setup();
	void Update();

	void ListUpdate();
	bool PlayerPlayerCollision(D3DXVECTOR3& pos1, D3DXVECTOR3& pos2, D3DXVECTOR3& dir1, D3DXVECTOR3& dir2);
	bool PlayerObjectCollision(list<cIGObj*>::iterator iter, D3DXVECTOR3& pos1, D3DXVECTOR3& pos2, D3DXVECTOR3& dir1, D3DXVECTOR3& dir2);
	bool ObjectObjectCollision(list<cIGObj*>::iterator iter1, list<cIGObj*>::iterator iter2);
	bool WallCollisionX(float moveX, D3DXVECTOR3& pos, D3DXVECTOR3& dir);
	bool WallCollisionZ(float moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir);
	bool WallVertexCollision(float moveX, float moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir);
	cIGObj* DetectObject(int playerNum);
	bool DetectMovement(int& moveX, int& moveZ, D3DXVECTOR3 dir);
	float GetDistance(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);

	inline void setPlayerMemoryAddressLink(int playerNum, cChef* address) { m_pPlayer[playerNum] = address; }
	inline void setStageObjManagerMemoryAddressLink(cStageObjManager* address) { m_pSOM = address; }
	inline void setMapIsBlockedData(map<pair<int, int>, int> data) { m_mapIsBlockedData = data; }
};

