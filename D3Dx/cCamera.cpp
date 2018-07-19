#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	: m_vEye(0, 0, -10.0f)
	, m_vUp(0, 1, 0)
	, m_vLookAt(0, 0, 0)
	, m_fRotX(0.8f)
	, m_fRotY(0)
	, m_fDistance(20.0f)
	, m_isRButtonDown(false)
{
}


cCamera::~cCamera()
{
}

void cCamera::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIX	matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 10000000);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update(D3DXVECTOR3 * pTarget)
{
	D3DXMATRIX matRot;
	D3DXMatrixRotationYawPitchRoll(&matRot, m_fRotY, m_fRotX, 0);
	D3DXVec3TransformNormal(&m_vEye, &D3DXVECTOR3(0, 0, -m_fDistance), &matRot);
	m_vEye = m_vEye + m_vLookAt;

	if (pTarget)
	{
		// 스토커 기법
		m_vLookAt = *pTarget;		// 타겟만 바라봐
		m_vEye = *pTarget + m_vEye;	// 타겟으로 부터 일정 거리 유지
	}

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONDOWN:
	{
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isRButtonDown = true;
	}
	break;
	case WM_RBUTTONUP:
	{
		m_isRButtonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (m_isRButtonDown)
		{
			POINT ptCurrMouse;
			g_ptMouse.x = ptCurrMouse.x = LOWORD(lParam);
			g_ptMouse.y = ptCurrMouse.y = HIWORD(lParam);

			m_fRotY += (ptCurrMouse.x - m_ptPrevMouse.x) / 100.0f;
			m_fRotX += (ptCurrMouse.y - m_ptPrevMouse.y) / 100.0f;

			// X축 회전은 위아래 90도 제한한다.
			if (m_fRotX <= -D3DX_PI * 0.5f + 0.0001f)
				m_fRotX = -D3DX_PI * 0.5f + 0.0001f;
			else if (m_fRotX >= D3DX_PI * 0.5f - 0.0001f)
				m_fRotX = D3DX_PI * 0.5f - 0.0001f;

			m_ptPrevMouse = ptCurrMouse;
		}
	}
	break;
	case WM_MOUSEWHEEL:
	{
		m_fDistance -= GET_WHEEL_DELTA_WPARAM(wParam) / 100.0f;
	}
	break;
	}
}
