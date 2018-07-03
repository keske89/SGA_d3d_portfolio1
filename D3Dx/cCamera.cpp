#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	: m_vEye(0, 0, -5)
	, m_vUp(0, 1, 0)
	, m_vLookAt(0, 0, 0)
	, m_fRotX(0)
	, m_fRotY(0)
	, m_fDistance(20.0f)
	, m_isRButtonDown(false)
	, m_isLButtonDown(false)
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

void cCamera::Update()
{
	D3DXMATRIX matRot;
	D3DXMatrixRotationYawPitchRoll(&matRot, m_fRotY, m_fRotX, 0);
	D3DXVec3TransformNormal(&m_vEye, &D3DXVECTOR3(0, 0, -m_fDistance), &matRot);
	m_vEye = m_vEye + m_vLookAt;
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		D3DVIEWPORT9	VP;
		D3DXMATRIX		matProj;
		D3DXMATRIX		matView;
		D3DXMATRIX		matInvV;
		D3DXVECTOR3		vecTemp;
		D3DXVECTOR3		PickRayDir;
		D3DXVECTOR3		PickRayOrg;
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		g_pD3DDevice->GetViewport(&VP);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matInvV, NULL, &matView);
		vecTemp.x = ((((m_ptMouse.x - VP.X) * 2.0f / VP.Width) - 1.0f) - matProj._31) / matProj._11;
		vecTemp.y = (-(((m_ptMouse.y - VP.Y) * 2.0f / VP.Height) - 1.0f) - matProj._32) / matProj._22;
		vecTemp.z = 1.0f;
		m_vecPickRayDir.x = vecTemp.x * matInvV._11 + vecTemp.y * matInvV._21 + vecTemp.z * matInvV._31;
		m_vecPickRayDir.y = vecTemp.x * matInvV._12 + vecTemp.y * matInvV._22 + vecTemp.z * matInvV._32;
		m_vecPickRayDir.z = vecTemp.x * matInvV._13 + vecTemp.y * matInvV._23 + vecTemp.z * matInvV._33;
		m_vecPickRayOrg.x = matInvV._41;
		m_vecPickRayOrg.y = matInvV._42;
		m_vecPickRayOrg.z = matInvV._43;
		m_isLButtonDown = true;
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}
	break;
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
			ptCurrMouse.x = LOWORD(lParam);
			ptCurrMouse.y = HIWORD(lParam);

			m_fRotY += (ptCurrMouse.x - m_ptPrevMouse.x) / 100.0f;
			m_fRotX += (ptCurrMouse.y - m_ptPrevMouse.y) / 100.0f;

			// X축 회전은 위아래 90도 제한한다.
			if (m_fRotX <= -D3DX_PI * 0.5f + 0.0001f)
				m_fRotX = -D3DX_PI * 0.5f + 0.0001f;
			else if (m_fRotX >= D3DX_PI * 0.5f + 0.0001f)
				m_fRotX = D3DX_PI * 0.5f + 0.0001f;

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
