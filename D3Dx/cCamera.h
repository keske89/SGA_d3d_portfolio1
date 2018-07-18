#pragma once
class cCamera
{
public:
	cCamera();
	~cCamera();

private:
	D3DXVECTOR3	m_vEye;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vLookAt;

	float		m_fDistance;
	float		m_fRotX;
	float		m_fRotY;
	bool		m_isRButtonDown;
	POINT		m_ptPrevMouse;
public:
	void Setup();
	void Update(D3DXVECTOR3 * pTarget = NULL);

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	inline void setVLookAt(D3DXVECTOR3 vector) { m_vLookAt = vector; }
	inline void setVEye(D3DXVECTOR3 vector) { m_vEye = vector; }
	inline void setRotX(float angle) { m_fRotX = angle; }
	inline void setDistance(float distance) { m_fDistance = distance; }
};

