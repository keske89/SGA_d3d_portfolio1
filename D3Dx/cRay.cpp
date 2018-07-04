#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
{
}


cRay::~cRay()
{
}

D3DXVECTOR3 cRay::getPickRayDir()
{
	D3DVIEWPORT9	VP;
	D3DXMATRIX		matProj;
	D3DXMATRIX		matView;
	D3DXMATRIX		matInvV;
	D3DXVECTOR3		vecTemp;
	D3DXVECTOR3		PickRayDir;
	g_pD3DDevice->GetViewport(&VP);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvV, NULL, &matView);
	vecTemp.x = ((((_ptMouse.x - VP.X) * 2.0f / VP.Width) - 1.0f) - matProj._31) / matProj._11;
	vecTemp.y = (-(((_ptMouse.y - VP.Y) * 2.0f / VP.Height) - 1.0f) - matProj._32) / matProj._22;
	vecTemp.z = 1.0f;
	PickRayDir.x = vecTemp.x * matInvV._11 + vecTemp.y * matInvV._21 + vecTemp.z * matInvV._31;
	PickRayDir.y = vecTemp.x * matInvV._12 + vecTemp.y * matInvV._22 + vecTemp.z * matInvV._32;
	PickRayDir.z = vecTemp.x * matInvV._13 + vecTemp.y * matInvV._23 + vecTemp.z * matInvV._33;

	return PickRayDir;
}

D3DXVECTOR3 cRay::getPickRayOrg()
{
	D3DXMATRIX		matView;
	D3DXMATRIX		matInvV;
	D3DXVECTOR3		PickRayOrg;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvV, NULL, &matView);
	PickRayOrg.x = matInvV._41;
	PickRayOrg.y = matInvV._42;
	PickRayOrg.z = matInvV._43;

	return PickRayOrg;
}
