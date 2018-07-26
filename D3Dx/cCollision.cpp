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
	m_nNewObjSize = m_pSOM->GetListFoodObj().size();
	m_foodList = m_pSOM->GetListFoodObj();
	m_objList = m_pSOM->GetListObj();
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
	for (m_iterList = m_foodList.begin(); m_iterList != m_foodList.end(); ++m_iterList)
	{
		(*m_iterList)->SetDir(D3DXVECTOR3(0, 0, 0));
	}
	m_iterList = m_foodList.begin();
	PlayerObjectCollision(m_iterList, pos[0], pos[1], dir[0], dir[1]);
	m_iterList++;
	ObjectObjectCollision(m_foodList.begin(), m_iterList);
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
	if (m_nNewObjSize != m_pSOM->GetListFoodObj().size())
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

bool cCollision::PlayerObjectCollision(list<cIGObj*>::iterator iter, D3DXVECTOR3& pos1, D3DXVECTOR3& pos2, D3DXVECTOR3& dir1, D3DXVECTOR3& dir2)
{
	if (m_pPlayer[0]->GetInven() != (*iter) &&
		m_pPlayer[1]->GetInven() != (*iter) &&
		(*iter)->GetIsSet() == false)
	{
		float distance1 = GetDistance(pos1, (*iter)->GetPos());
		float distance2 = GetDistance(pos2, (*iter)->GetPos());
		D3DXVECTOR3 objPos = (*iter)->GetPos();
		D3DXVECTOR3 objDir = (*iter)->GetDir();
		float height = objPos.y;
		objPos.y = 0;

		D3DXMATRIX invMat;
		D3DXMATRIX invTransMat;
		float tempDist = 0.0f;
		D3DXVECTOR3 tempPos;
		BOOL isPicked;
		D3DXMatrixInverse(&invTransMat, NULL, &(*iter)->GetWorldMat());
		D3DXVec3TransformCoord(&tempPos, &objPos, &invTransMat);
		D3DXIntersect((*iter)->GetMesh(), &tempPos, &D3DXVECTOR3(0, 1, 0), &isPicked, NULL, NULL, NULL, &tempDist, NULL, NULL);
		if (isPicked == TRUE && tempDist > 0.01f)
		{
			height -= 0.01f;
		}

		pos1 -= dir1;
		pos2 -= dir2;
		objPos -= objDir;
		if (distance1 < 0.7f)
		{
			D3DXVECTOR3 push1;
			D3DXVec3Normalize(&push1, &(pos1 - objPos));
			push1 = push1 * ((0.7f - distance1) / 2.0f);
			D3DXVECTOR3 push2;
			D3DXVec3Normalize(&push2, &(objPos - pos1));
			push2 = push2 * ((0.7f - distance1) / 2.0f);
			dir1 += push1;
			objDir += push2;
		}
		if (distance2 < 0.7f)
		{
			D3DXVECTOR3 push1;
			D3DXVec3Normalize(&push1, &(pos2 - objPos));
			push1 = push1 * ((0.7f - distance2) / 2.0f);
			D3DXVECTOR3 push2;
			D3DXVec3Normalize(&push2, &(objPos - pos2));
			push2 = push2 * ((0.7f - distance2) / 2.0f);
			dir2 += push1;
			objDir += push2;
		}
		pos2 += dir2;
		pos1 += dir1;
		objPos += objDir;
		objPos.y = height;

		D3DXMATRIX matWorld;
		D3DXMatrixTranslation(&matWorld, objPos.x, objPos.y, objPos.z);
		(*iter)->SetWorldMatrix(matWorld);
		(*iter)->SetPos(objPos);
		(*iter)->SetDir(objDir);
	}
	list<cIGObj*>::iterator nextIter = iter;
	nextIter++;
	if (nextIter != m_foodList.end())
	{
		PlayerObjectCollision(nextIter, pos1, pos2, dir1, dir2);
	}

	return false;
}

bool cCollision::ObjectObjectCollision(list<cIGObj*>::iterator iter1, list<cIGObj*>::iterator iter2)
{
	if ((*iter1)->GetIsSet() == false)
	{
		D3DXVECTOR3 obj1Dir = (*iter1)->GetDir();
		D3DXVECTOR3 obj1Pos = (*iter1)->GetPos();
		float height1 = (*iter1)->GetPos().y;
		D3DXMATRIX matWorld;
		for (; iter2 != m_foodList.end(); ++iter2)
		{
			if ((*iter2)->GetIsSet() == true) continue;
			D3DXVECTOR3 obj2Dir = (*iter2)->GetDir();
			D3DXVECTOR3 obj2Pos = (*iter2)->GetPos();
			obj1Pos.y = 0;
			float height2 = obj2Pos.y;
			obj2Pos.y = 0;
			float distance = GetDistance(obj1Pos, obj2Pos);
			if (distance < 0.8f)
			{
				D3DXVECTOR3 push1;
				D3DXVec3Normalize(&push1, &(obj1Pos - obj2Pos));
				push1 = push1 * ((0.8f - distance) / 2.0f);
				D3DXVECTOR3 push2;
				D3DXVec3Normalize(&push2, &(obj2Pos - obj1Pos));
				push2 = push2 * ((0.8f - distance) / 2.0f);
				obj1Pos -= obj1Dir;//
				obj2Pos -= obj2Dir;//
				obj1Dir += push1;
				obj2Dir += push2;
				obj1Pos += obj1Dir;
				obj2Pos += obj2Dir;
				obj1Pos.y = height1;
				obj2Pos.y = height2;

				(*iter1)->SetDir(obj1Dir);
				(*iter2)->SetDir(obj2Dir);
				(*iter1)->SetPos(obj1Pos);
				(*iter2)->SetPos(obj2Pos);
			}
		}
		obj1Pos.y = height1;
		bool CDX = false;
		bool CDZ = false;
		float moveX = 0.0f;
		float moveZ = 0.0f;
		if (obj1Dir.x > 0) moveX = 0.8f;
		if (obj1Dir.x < 0) moveX = -0.8f;
		if (obj1Dir.z > 0) moveZ = 0.8f;
		if (obj1Dir.z < 0) moveZ = -0.8f;
		CDX = WallCollisionX(moveX, obj1Pos, obj1Dir);
		CDZ = WallCollisionZ(moveZ, obj1Pos, obj1Dir);
		if (CDX == false && CDZ == false) WallVertexCollision(moveX, moveZ, obj1Pos, obj1Dir);

		D3DXMATRIX transBefore;
		D3DXMATRIX matRoll;
		D3DXMATRIX transAfter;
		D3DXVECTOR3 vecRoll = (*iter1)->GetvecRoll();
		D3DXMatrixTranslation(&transBefore, 0, -0.4f, 0);
		D3DXMatrixTranslation(&transAfter, 0, 0.4f, 0);
		if (obj1Dir.x > 0.01) vecRoll.z -= 0.05f;
		else if (obj1Dir.x < -0.01) vecRoll.z += 0.05f;
		if (obj1Dir.z > 0.01) vecRoll.x -= 0.05f;
		else if (obj1Dir.z < -0.01) vecRoll.x += 0.05f;
		D3DXMatrixRotationYawPitchRoll(&matRoll, 0, vecRoll.x, vecRoll.z);
		(*iter1)->SetvecRoll(vecRoll);
		(*iter1)->SetmatRoll(transBefore * matRoll * transAfter);

		D3DXMatrixTranslation(&matWorld, obj1Pos.x, obj1Pos.y, obj1Pos.z);
		(*iter1)->SetWorldMatrix(matWorld);
	}
	iter1++;
	if (iter1 == m_foodList.end()) return false;
	list<cIGObj*>::iterator nextIter = iter1;
	nextIter++;
	ObjectObjectCollision(iter1, nextIter);
	return false;
}

bool cCollision::WallCollisionX(float moveX, D3DXVECTOR3& pos, D3DXVECTOR3& dir)
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

bool cCollision::WallCollisionZ(float moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir)
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

bool cCollision::WallVertexCollision(float moveX, float moveZ, D3DXVECTOR3& pos, D3DXVECTOR3& dir)
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

cIGObj* cCollision::DetectObject(int playerNum)
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
