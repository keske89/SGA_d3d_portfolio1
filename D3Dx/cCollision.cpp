#include "stdafx.h"
#include "cCollision.h"
#include "cStageObjManager.h"
#include "cIGObj.h"
#include "cChef.h"


cCollision::cCollision()
	: m_pSOM(NULL)
	, m_nListSize(0)
	, m_nNewObjSize(0)
{
	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;
}


cCollision::~cCollision()
{
}

void cCollision::Setup()
{
	m_nListSize = m_pSOM->GetListFoodObj().size();
	m_foodList = m_pSOM->GetListFoodObj();
	m_objList = m_pSOM->GetListObj();
	for (m_iterList = m_objList.begin(); m_iterList != m_objList.end(); ++m_iterList)
	{
		vector<cIGObj*> tempVec;
		pair<int, int> tempPair;
		if ((*m_iterList)->GetCollisonType() == OBJ_DYNAMIC)
		{
			m_mapDynamicObject.insert(make_pair((*m_iterList), false));
		}
		else if ((*m_iterList)->GetCollisonType() == OBJ_STATIC)
		{
			tempPair.first = (*m_iterList)->GetPos().x;
			tempPair.second = (*m_iterList)->GetPos().z;
			if (m_mapStaticObject.find(tempPair) == m_mapStaticObject.end())
			{
				tempVec.push_back((*m_iterList));
				m_mapStaticObject.insert(make_pair(tempPair, tempVec));
			}
			else
			{
				m_mapStaticObject.find(tempPair)->second.push_back((*m_iterList));
			}
		}
	}
}

void cCollision::Update()
{
	ListUpdate();
	D3DXVECTOR3 pos[2];
	D3DXVECTOR3 dir[2];
	int moveX[2];
	int moveZ[2];
	bool CDX = false;
	bool CDZ = false;
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
			CDX = WallCollisionX(moveX[i], pos[i], dir[i]);
			CDZ = WallCollisionZ(moveZ[i], pos[i], dir[i]);
			if (CDX == false && CDZ == false) WallVertexCollision(moveX[i], moveZ[i], pos[i], dir[i]);
			m_pPlayer[i]->SetPos(pos[i]);
			m_pPlayer[i]->SetDetect(DetectObject(i));
		}
	}
}

void cCollision::ListUpdate()
{
	if (m_nListSize != m_pSOM->GetListFoodObj().size())
	{
		m_foodList = m_pSOM->GetListFoodObj();
		m_nNewObjSize = m_pSOM->GetListFoodObj().size();
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

bool cCollision::WallCollisionX(int moveX, D3DXVECTOR3& pos, D3DXVECTOR3& dir)
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

bool cCollision::WallCollisionZ(int moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir)
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

bool cCollision::WallVertexCollision(int moveX, int moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir)
{
	int keyFirst = pos.x;
	int keySecond = pos.z;
	float distance = 0.0f;
	if (moveX == 0)
	{
		if (pos.x - keyFirst < 0.5f)
		{
			if (m_mapIsBlockedData.find(make_pair(keyFirst - 1, keySecond + moveZ)) != m_mapIsBlockedData.end())
			{
				distance = GetDistance(pos, D3DXVECTOR3(keyFirst, 0, keySecond + (moveZ + 1) * 0.5f));
				D3DXVECTOR3 push = pos - D3DXVECTOR3(keyFirst, 0, keySecond + (moveZ + 1) * 0.5f);
				if (distance < 0.6f)
				{
					pos += (0.6f - distance) * push;
					return true;
				}
			}
		}
		else
		{
			if (m_mapIsBlockedData.find(make_pair(keyFirst + 1, keySecond + moveZ)) != m_mapIsBlockedData.end())
			{
				distance = GetDistance(pos, D3DXVECTOR3(keyFirst + 1, 0, keySecond + (moveZ + 1) * 0.5f));
				D3DXVECTOR3 push = pos - D3DXVECTOR3(keyFirst + 1, 0, keySecond + (moveZ + 1) * 0.5f);
				if (distance < 0.6f)
				{
					pos += (0.6f - distance) * push;
					return true;
				}
			}
		}
	}
	else if (moveZ == 0)
	{
		if (pos.z - keySecond < 0.5f)
		{
			if (m_mapIsBlockedData.find(make_pair(keyFirst + moveX, keySecond - 1)) != m_mapIsBlockedData.end())
			{
				distance = GetDistance(pos, D3DXVECTOR3(keyFirst + (moveX + 1) * 0.5f, 0, keySecond));
				D3DXVECTOR3 push = pos - D3DXVECTOR3(keyFirst + (moveX + 1) * 0.5f, 0, keySecond);
				if (distance < 0.6f)
				{
					pos += (0.6f - distance) * push;
					return true;
				}
			}
		}
		else
		{
			if (m_mapIsBlockedData.find(make_pair(keyFirst + moveX, keySecond + 1)) != m_mapIsBlockedData.end())
			{
				distance = GetDistance(pos, D3DXVECTOR3(keyFirst + (moveX + 1) * 0.5f, 0, keySecond + 1));
				D3DXVECTOR3 push = pos - D3DXVECTOR3(keyFirst + (moveX + 1) * 0.5f, 0, keySecond + 1);
				if (distance < 0.6f)
				{
					pos += (0.6f - distance) * push;
					return true;
				}
			}
		}
	}
	else
	{
		if (m_mapIsBlockedData.find(make_pair(keyFirst + moveX, keySecond + moveZ)) != m_mapIsBlockedData.end())
		{
			distance = GetDistance(pos, D3DXVECTOR3(keyFirst + (moveX + 1) * 0.5f, 0, keySecond + (moveZ + 1) * 0.5f));
			D3DXVECTOR3 push = pos - D3DXVECTOR3(keyFirst + (moveX + 1) * 0.5f, 0, keySecond + (moveZ + 1) * 0.5f);
			if (distance < 0.6f)
			{
				pos += (0.6f - distance) * push;
				return true;
			}
		}
	}
	return false;
}

cIGObj* cCollision::PlayerDetectObject(int playerNum)
{
	D3DXVECTOR3 pos = m_pPlayer[playerNum]->GetPos(); 
	D3DXVECTOR3 dir = m_pPlayer[playerNum]->GetDir();
	D3DXVec3Normalize(&dir, &dir);
	pos = pos + dir * 0.8;
	int keyFirst = pos.x;
	int keySecond = pos.z;
	float distance = 10000000.0f;
	cIGObj* tempAddress = NULL;
	m_iterStaticObject = m_mapStaticObject.find(make_pair(keyFirst, keySecond));
	if (m_iterStaticObject != m_mapStaticObject.end())
	{
		for (int j = 0; j < m_iterStaticObject->second.size(); ++j)
		{
			float tempDist = GetDistance(m_pPlayer[playerNum]->GetPos(), m_iterStaticObject->second[j]->GetPos());
			if (tempDist > distance) continue;
			else if (tempDist < distance)
			{
				distance = tempDist;
				if (m_iterStaticObject->second[j]->GetInven() && m_iterStaticObject->second[j]->GetInven()->GetCollisonType() == OBJ_STATIC)
				{
					tempAddress = m_iterStaticObject->second[j]->GetInven();
				}
				else
				{
					tempAddress = m_iterStaticObject->second[j];
				}
			}
		}
	}
	for (m_iterDynamicObject = m_mapDynamicObject.begin(); m_iterDynamicObject != m_mapDynamicObject.end(); ++m_iterDynamicObject)
	{
		float tempDist = GetDistance(m_pPlayer[playerNum]->GetPos(), m_iterDynamicObject->first->GetPos());
		if (tempDist > distance) continue;
		else if (tempDist < distance)
		{
			distance = tempDist;
			tempAddress = m_iterDynamicObject->first;
		}
	}
	return tempAddress;
}

cIGObj * cCollision::DetectObject(int playerNum)
{
	D3DXVECTOR3 pos = m_pPlayer[playerNum]->GetPos();
	D3DXVECTOR3 dir = m_pPlayer[playerNum]->GetDir();
	D3DXVec3Normalize(&dir, &dir);
	pos = pos + dir * 0.8;

	float distance = 10000000.0f;
	BOOL isPicked = FALSE;
	cIGObj* tempAddress = NULL;
	D3DXMATRIX invMat;
	D3DXMATRIX invTransMat;
	D3DXMATRIX invRotMat;

	for (m_iterList = m_objList.begin(); m_iterList != m_objList.end(); ++m_iterList)
	{
		float tempDist = 0.0f;
		D3DXVECTOR3 tempPos;
		D3DXVECTOR3 tempDir;
		D3DXMatrixTranspose(&invRotMat, &(*m_iterList)->GetWorldMat());
		D3DXMatrixInverse(&invTransMat, NULL, &(*m_iterList)->GetWorldMat());
		D3DXVec3TransformCoord(&tempPos, &pos, &invTransMat);
		D3DXVec3TransformNormal(&tempDir, &D3DXVECTOR3(0, 1, 0), &invRotMat);
		D3DXIntersect((*m_iterList)->GetMesh(), &tempPos, &tempDir, &isPicked, NULL, NULL, NULL, &tempDist, NULL, NULL);
		if (isPicked == TRUE && tempDist < distance)
		{
			distance = tempDist;
			tempAddress = (*m_iterList);
		}
	}
	for (m_iterList = m_foodList.begin(); m_iterList != m_foodList.end(); ++m_iterList)
	{
		float tempDist = 0.0f;
		D3DXVECTOR3 tempPos;
		D3DXMatrixInverse(&invTransMat, NULL, &(*m_iterList)->GetWorldMat());
		D3DXVec3TransformCoord(&tempPos, &pos, &invTransMat);
		D3DXIntersect((*m_iterList)->GetMesh(), &tempPos, &D3DXVECTOR3(0, 1, 0), &isPicked, NULL, NULL, NULL, &tempDist, NULL, NULL);
		if (isPicked == TRUE && tempDist < distance)
		{
			distance = tempDist;
			tempAddress = (*m_iterList);
		}
	}

	return tempAddress;
}

void cCollision::StaticLineXCollision(int playerNum, int keyFirst, int keySecond, int moveX, D3DXVECTOR3& pos)
{
	/*
	float distance = 0.0f;
	m_iterObject = m_mapObject.find(make_pair(keyFirst + moveX, keySecond));
	if (m_iterObject != m_mapObject.end())
	{
		for (int j = 0; j < m_iterObject->second.size(); ++j)
		{
			if (m_iterObject->second[j]->GetCollisionType() == OBJ_STATIC)
			{
				distance = abs(m_pPlayer[0]->GetPos().x - m_iterObject->second[j]->GetPos().x);
				if (distance < 1)
				{
					pos.x -= moveX * (1 - distance);
					m_pPlayer[0]->SetPos(pos);
				}
			}
		}
	}
	*/
}

void cCollision::StaticLineZCollision(int playerNum, int keyFirst, int keySecond, int moveZ, D3DXVECTOR3& pos)
{
	/*
	float distance = 0.0f;
	m_iterObject = m_mapObject.find(make_pair(keyFirst, keySecond + moveZ));
	if (m_iterObject != m_mapObject.end())
	{
		for (int j = 0; j < m_iterObject->second.size(); ++j)
		{
			if (m_iterObject->second[j]->GetCollisionType() == OBJ_STATIC)
			{
				distance = abs(m_pPlayer[0]->GetPos().z - m_iterObject->second[j]->GetPos().z);
				if (distance < 1)
				{
					pos.z -= moveZ * (1 - distance);
					m_pPlayer[0]->SetPos(pos);
				}
			}
		}
	}
	*/
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
