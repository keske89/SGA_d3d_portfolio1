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
	ListUpdate();
	D3DXVECTOR3 pos[2];
	D3DXVECTOR3 dir[2];
	int moveX[2];
	int moveZ[2];
	for (int i = 0; i < 2; ++i)
	{
		pos[i] = m_pPlayer[i]->GetPos();
		dir[i] = m_pPlayer[i]->GetToGo();
	}
	PlayerPlayerCollision(pos[0], pos[1], dir[0], dir[1]);
	for (int i = 0; i < 2; ++i)
	{
		if (DetectMovement(moveX[i], moveZ[i], dir[i]))
		{
			PlayerWallCollisionX(moveX[i], pos[i], dir[i]);
			PlayerWallCollisionZ(moveZ[i], pos[i], dir[i]);
			m_pPlayer[i]->SetPos(pos[i]);
			m_pPlayer[i]->SetDetect(PlayerDetectObject(i));
		}
	}
}

void cCollision::ListUpdate()
{
	if (m_nListSize = m_pSOM->GetListObj().size()) return;
	else
	{
		m_mapObject.clear();
		m_nListSize = m_pSOM->GetListObj().size();
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
}

bool cCollision::PlayerPlayerCollision(D3DXVECTOR3& pos1, D3DXVECTOR3& pos2, D3DXVECTOR3& dir1, D3DXVECTOR3& dir2)
{
	float distance = GetDistance(pos1, pos2);
	if (distance < 1)
	{
		D3DXVECTOR3 push1; 
		D3DXVec3Normalize(&push1, &(pos1 - pos2));
		push1 = push1 * ((1.0f - distance) / 2.0f);
		D3DXVECTOR3 push2; 
		D3DXVec3Normalize(&push2, &(pos2 - pos1));
		push2 = push2 * ((1.0f - distance) / 2.0f);
		pos1 -= dir1;
		pos2 -= dir2;
		dir1 += push1;
		dir2 += push2;
		pos1 += dir1;
		pos2 += dir2;
		return true;
	}
	return false;
}

bool cCollision::PlayerWallCollisionX(int moveX, D3DXVECTOR3& pos, D3DXVECTOR3& dir)
{
	int keyFirst = (pos.x + (moveX / 2.0f));
	int keySecond = pos.z;
	if (m_mapIsBlockedData.find(make_pair(keyFirst, keySecond)) != m_mapIsBlockedData.end())
	{
		pos.x -= dir.x;
		return true;
	}
	return false;
}

bool cCollision::PlayerWallCollisionZ(int moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir)
{
	int keyFirst = pos.x;
	int keySecond = (pos.z + (moveZ / 2.0f));
	if (m_mapIsBlockedData.find(make_pair(keyFirst, keySecond)) != m_mapIsBlockedData.end())
	{
		pos.z -= dir.z;
		return true;
	}
	return false;
}

void cCollision::PlayerWallVertexCollision(int playerNum, D3DXVECTOR3& pos)
{
	int keyFirst = pos.x;
	int keySecond = pos.z;
	for (int i = 0; i < 4; ++i)
	{

	}
}

cIGObj* cCollision::PlayerDetectObject(int playerNum)
{
	D3DXVECTOR3 pos = m_pPlayer[playerNum]->GetPos(); 
	D3DXVECTOR3 dir = m_pPlayer[playerNum]->GetDir();
	D3DXVec3Normalize(&dir, &dir);
	pos = pos + dir * 0.7;
	int keyFirst = pos.x;
	int keySecond = pos.z;
	float distance = 10000000.0f;
	cIGObj* tempAddress = NULL;
	m_iterObject = m_mapObject.find(make_pair(keyFirst, keySecond));
	if (m_iterObject != m_mapObject.end())
	{
		for (int j = 0; j < m_iterObject->second.size(); ++j)
		{
			float tempDist = GetDistance(m_pPlayer[playerNum]->GetPos(), m_iterObject->second[j]->GetPos());
			if (tempDist > distance) continue;
			else if (tempDist < distance)
			{
				distance = tempDist;
				tempAddress = m_iterObject->second[j];
			}
		}
	}
	return tempAddress;
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

bool cCollision::DetectMovement(int& moveX, int& moveZ, D3DXVECTOR3 dir)
{
	if (dir.x > 0) moveX = 1;
	else if (dir.x < 0) moveX = -1;
	else moveX = 0;
	if (dir.z > 0) moveZ = 1;
	else if (dir.z < 0) moveZ = -1;
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
