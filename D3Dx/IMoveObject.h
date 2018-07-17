#pragma once
#include "IDisplayObject.h"

class IMoveObject : public IDisplayObject
{
protected:

	bool m_isMoving;

	D3DXVECTOR3 m_deltaPos;
	D3DXVECTOR3 m_deltaRot;
	D3DXVECTOR3 m_forward;

	float m_baseRotY;

	float m_moveSpeed;
	float m_currMoveSpeedRate;
	float m_rotationSpeed;

	IMoveObject();
	virtual ~IMoveObject();

public:
	void UpdateMoving();

};

