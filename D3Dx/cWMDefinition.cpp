#include "stdafx.h"
#include "cWMDefinition.h"

namespace DXUtil
{

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = a;
		mtrl.Diffuse = d;
		mtrl.Specular = s;
		mtrl.Emissive = e;
		mtrl.Power = p;

		return mtrl;
	}

	void ComputeNormal(D3DXVECTOR3* out, D3DXVECTOR3* p0, D3DXVECTOR3* p1, D3DXVECTOR3* p2)
	{
		D3DXVECTOR3 v01 = *p1 - *p0;
		D3DXVECTOR3 v02 = *p2 - *p0;

		D3DXVec3Cross(out, &v01, &v02);
		D3DXVec3Normalize(out, out);
	}

	D3DLIGHT9 InitDirectional(D3DXVECTOR3* dir, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Direction = *dir;

		return light;
	}

	D3DLIGHT9 InitPoint(D3DXVECTOR3* pos, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		light.Type = D3DLIGHT_POINT;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Position = *pos;
		light.Range = 20.0f;
		light.Falloff = 1.0f;
		light.Attenuation0 = 0.005f;
		light.Attenuation1 = 0.005f;
		light.Attenuation2 = 0.005f;

		return light;
	}

	D3DLIGHT9 InitSpot(D3DXVECTOR3* dir, D3DXVECTOR3* pos, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		light.Type = D3DLIGHT_SPOT;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Direction = *dir;
		light.Position = *pos;
		light.Range = 50.0f;
		light.Falloff = 1.0f;
		light.Theta = 0.0f;
		light.Phi = D3DX_PI / 6;
		light.Attenuation0 = 0.005f;
		light.Attenuation1 = 0.005f;
		light.Attenuation2 = 0.005f;

		return light;
	}

	void InitVertexBuffer(LPDIRECT3DVERTEXBUFFER9& pVB, LPVOID vertices, DWORD fvf, UINT vtxCnt, UINT stride)
	{
		g_pD3DDevice->CreateVertexBuffer(vtxCnt*stride, NULL, fvf, D3DPOOL_MANAGED, &pVB, NULL);

		LPVOID pVertex;
		pVB->Lock(0, 0, (LPVOID*)&pVertex, 0);
		memcpy(pVertex, vertices, vtxCnt * stride);
		pVB->Unlock();
	}

	void InitIndexBuffer(LPDIRECT3DINDEXBUFFER9 & pIB, LPVOID indices, UINT idxCnt, UINT stride)
	{
		D3DFORMAT format;
		if (stride == sizeof(WORD))
			format = D3DFMT_INDEX16;
		if (stride == sizeof(DWORD))
			format = D3DFMT_INDEX32;

		g_pD3DDevice->CreateIndexBuffer(idxCnt* stride, NULL, format, D3DPOOL_MANAGED, &pIB, NULL);

		LPVOID pIndex;
		pIB->Lock(0, 0, (LPVOID*)&pIndex, 0);
		memcpy(pIndex, pIB, idxCnt * stride);
		pIB->Unlock();
	}

	D3DXVECTOR2 Convert3DTo2D(D3DXVECTOR3 v)
	{
		D3DXMATRIX proj, view, world;
		D3DVIEWPORT9 vp;
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &proj);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);
		g_pD3DDevice->GetViewport(&vp);
		D3DXMatrixIdentity(&world);
		D3DXVec3Project(&v, &v, &vp, &proj, &view, &world);
		return D3DXVECTOR2(v.x, v.y);
	}

	POINT MakePoint(float x, float y)
	{
		POINT pt;
		pt.x = x; pt.y = y;
		return pt;
	}
}