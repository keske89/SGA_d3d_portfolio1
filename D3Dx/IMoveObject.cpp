#include "stdafx.h"
#include "IMoveObject.h"


IMoveObject::IMoveObject()
{
	m_isMoving = false;
	m_moveSpeed = 0.2f;
	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;

	m_baseRotY = 0;


}

IMoveObject::~IMoveObject()
{
}

void IMoveObject::UpdateMoving()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_deltaPos.z = 1;
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_deltaPos.z = -1;
	}
	else
	{
		m_deltaPos.z = 0;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
		m_deltaRot.y = 1;
	else if (KEYMANAGER->isStayKeyDown('A'))
		m_deltaRot.y = -1;
	else m_deltaRot.y = 0;

	m_rot += m_deltaRot * m_rotationSpeed;

	D3DXMATRIX matRotY;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

	D3DXVECTOR3 targetPos;

	float temp = 0.0f;

	targetPos = m_vPosition + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate;

	m_vPosition = targetPos;


	//m_pos = targetPos;
	D3DXMATRIX matT, matBaseRotY;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DXMatrixRotationY(&matBaseRotY, m_baseRotY);
	m_matWorld = matRotY * matBaseRotY * matT;

	if (D3DXVec3LengthSq(&m_deltaRot) > 0 || D3DXVec3LengthSq(&m_deltaPos) > 0)
		m_isMoving = true;
	else
		m_isMoving = false;

}
