#include "stdafx.h"
#include "cCollision.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
#include "cChef.h"


cCollision::cCollision()
	: m_pSOM(NULL)
	, m_nListSize(0)
{
	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;
}


cCollision::~cCollision()
{
}

void cCollision::Setup()
{
	m_nListSize = m_pSOM->GetListObj().size();
	m_objList = m_pSOM->GetListObj();
	for (m_iterList = m_objList.begin(); m_iterList != m_objList.end(); ++m_iterList)
	{
		vector<cIGObj*> tempVec;
		pair<int, int> tempPair;
		tempPair.first = (*m_iterList)->GetPos().x;
		tempPair.second = (*m_iterList)->GetPos().z;
		if (m_mapObject.find(tempPair) == m_mapObject.end())
		{
			tempVec.push_back((*m_iterList));
			m_mapObject.insert(make_pair(tempPair, tempVec));
		}
		else
		{
			m_mapObject.find(tempPair)->second.push_back((*m_iterList));
		}
	}
	int test = 0;
}

void cCollision::Update()
{
	D3DXVECTOR3 pos = m_pPlayer[0]->GetPos();
	int keyFirst = pos.x;
	int keySecond = pos.z;
	int moveX = 0;
	int moveZ = 0;
	if (DetectMovement(0, moveX, moveZ))
	{
		WallCollisionX(0, moveX, pos);
		WallCollisionZ(0, moveZ, pos);
		//StaticLineXCollision(0, keyFirst, keySecond, moveX, pos);
		//StaticLineZCollision(0, keyFirst, keySecond, moveZ, pos);
	}
}

bool cCollision::WallCollisionX(int playerNum, int moveX, D3DXVECTOR3& pos)
{
	int keyFirst = (pos.x + (moveX / 2.0f));
	int keySecond = pos.z;
	if (m_mapIsBlockedData.find(make_pair(keyFirst, keySecond)) != m_mapIsBlockedData.end())
	{
		float test = m_pPlayer[playerNum]->GetToGo().x;
		pos.x -= m_pPlayer[playerNum]->GetToGo().x;
		m_pPlayer[playerNum]->SetPos(pos);
		return true;
	}
	return false;
}

bool cCollision::WallCollisionZ(int playerNum, int moveZ, D3DXVECTOR3& pos)
{
	int keyFirst = pos.x;
	int keySecond = (pos.z + (moveZ / 2.0f));
	if (m_mapIsBlockedData.find(make_pair(keyFirst, keySecond)) != m_mapIsBlockedData.end())
	{
		float test = m_pPlayer[playerNum]->GetToGo().z;
		pos.z -= m_pPlayer[playerNum]->GetToGo().z;
		m_pPlayer[playerNum]->SetPos(pos);
		return true;
	}
	return false;
}

void cCollision::WallVertexCollision(int playerNum, D3DXVECTOR3& pos)
{
	int keyFirst = pos.x;
	int keySecond = pos.z;
	for (int i = 0; i < 4; ++i)
	{

	}
}

void cCollision::StaticLineXCollision(int playerNum, int keyFirst, int keySecond, int moveX, D3DXVECTOR3& pos)
{
	float distance = 0.0f;
	m_iterObject = m_mapObject.find(make_pair(keyFirst + moveX, keySecond));
	if (m_iterObject != m_mapObject.end())
	{
		for (int j = 0; j < m_iterObject->second.size(); ++j)
		{
			//if (m_iterObject->second[j]->GetCollisionType() == OBJ_STATIC)
			//{
			//	distance = abs(m_pPlayer[0]->GetPos().x - m_iterObject->second[j]->GetPos().x);
			//	if (distance < 1)
			//	{
			//		pos.x -= moveX * (1 - distance);
			//		m_pPlayer[0]->SetPos(pos);
			//	}
			//}
		}
	}
}

void cCollision::StaticLineZCollision(int playerNum, int keyFirst, int keySecond, int moveZ, D3DXVECTOR3& pos)
{
	float distance = 0.0f;
	m_iterObject = m_mapObject.find(make_pair(keyFirst, keySecond + moveZ));
	if (m_iterObject != m_mapObject.end())
	{
		for (int j = 0; j < m_iterObject->second.size(); ++j)
		{
			//if (m_iterObject->second[j]->GetCollisionType() == OBJ_STATIC)
			//{
			//	distance = abs(m_pPlayer[0]->GetPos().z - m_iterObject->second[j]->GetPos().z);
			//	if (distance < 1)
			//	{
			//		pos.z -= moveZ * (1 - distance);
			//		m_pPlayer[0]->SetPos(pos);
			//	}
			//}
		}
	}
}

void cCollision::StaticVertexCollision(int playerNum, int keyFirst, int keySecond)
{
}

void cCollision::DinamicCollision(int playerNum, int keyFirst, int keySecond)
{
}

bool cCollision::DetectMovement(int playerNum, int& moveX, int& moveZ)
{
	if (m_pPlayer[playerNum]->GetToGo().x > 0) moveX = 1;
	else if (m_pPlayer[playerNum]->GetToGo().x < 0) moveX = -1;
	else moveX = 0;
	if (m_pPlayer[playerNum]->GetToGo().z > 0) moveZ = 1;
	else if (m_pPlayer[playerNum]->GetToGo().z < 0) moveZ = -1;
	else moveZ = 0;
	if (moveX == 0 && moveZ == 0) return false;
	else return true;
}

float cCollision::GetDistance(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
{
	float x = (vec1.x - vec2.x) * (vec1.x - vec2.x);
	float z = (vec1.z - vec2.z) * (vec1.z - vec2.z);
	float result = sqrtf(x + z);
	return result;
}
