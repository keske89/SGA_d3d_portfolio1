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

	D3DXVECTOR3	m_vecPickRayDir;
	D3DXVECTOR3	m_vecPickRayOrg;
	bool		m_isLButtonDown;
	POINT		m_ptMouse;
public:
	void Setup();
	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	inline void setVLookAt(D3DXVECTOR3 vector) { m_vLookAt = vector + D3DXVECTOR3(0, 0, 0); }
	inline void setDistance(float distance) { m_fDistance = distance; }

	inline bool getBoolLButton() { return m_isLButtonDown; }
	inline D3DXVECTOR3 getPickRayDir() { return m_vecPickRayDir; }
	inline D3DXVECTOR3 getPickRayOrg() { return m_vecPickRayOrg; }
};

