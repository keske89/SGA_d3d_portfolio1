#include "stdafx.h"
#include "cEffectObject.h"


cEffectObject::cEffectObject()
{
}


cEffectObject::~cEffectObject()
{
	SAFE_RELEASE(m_pVB);
}

void cEffectObject::Setup(ST_EFFECT info, D3DXVECTOR3 pos)
{
	m_stInfo = info;
	m_vPos = pos;
	D3DXVec3Normalize(&m_stInfo.dir, &m_stInfo.dir);
	D3DXVec3Normalize(&m_stInfo.mot, &m_stInfo.mot);

	m_vMot = D3DXVECTOR3(0, 0, 0);

	if (D3DXVec3Length(&m_stInfo.dir) < 0.1)
		m_isFlash = true;
	else
		m_isFlash = false;

	m_stInfo.rot.x = D3DXToRadian(m_stInfo.rot.x);
	m_stInfo.rot.y = D3DXToRadian(m_stInfo.rot.y);
	m_stInfo.rot.z = D3DXToRadian(m_stInfo.rot.z);

	if (m_stInfo.isRX)
		m_stInfo.rot.x = DXUtil::FRand(-D3DX_PI / 2, D3DX_PI);
	if (m_stInfo.isRY)
		m_stInfo.rot.y = DXUtil::FRand(-D3DX_PI / 2, D3DX_PI);
	if (m_stInfo.isRZ)
		m_stInfo.rot.z = DXUtil::FRand(-D3DX_PI / 2, D3DX_PI);

	if (!m_isFlash && !m_stInfo.isRY)
	{
		D3DXVECTOR3 zero = D3DXVECTOR3(0, 0, 0);
		float angle = DXUtil::GetAngle(zero.x, zero.z, m_stInfo.dir.x, m_stInfo.dir.z);
		m_stInfo.rot.y = angle;
	}

	D3DSURFACE_DESC desc;
	info.tex->GetLevelDesc(0, &desc);

	float rate = info.height / desc.Height;
	float widthH = desc.Width * rate / 2;
	float heightH = desc.Height * rate / 2;

	m_stSphere.radius = heightH;
	m_stSphere.center = D3DXVECTOR3(0, heightH, 0);


	ST_PCT_VERTEX v;
	v.c = 0xFFFFFFFF;
	v.t = D3DXVECTOR2(0, 1);
	v.p = D3DXVECTOR3(-widthH, -heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(0, 0);
	v.p = D3DXVECTOR3(-widthH, heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(1, 0);
	v.p = D3DXVECTOR3(widthH, heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(0, 1);
	v.p = D3DXVECTOR3(-widthH, -heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(1, 0);
	v.p = D3DXVECTOR3(widthH, heightH, 0);
	m_vecVertex.push_back(v);
	v.t = D3DXVECTOR2(1, 1);
	v.p = D3DXVECTOR3(widthH, -heightH, 0);
	m_vecVertex.push_back(v);

	g_pD3DDevice->CreateVertexBuffer(m_vecVertex.size() * sizeof(ST_PCT_VERTEX),
		D3DUSAGE_DYNAMIC, ST_PCT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVB, NULL);

	m_pVB->Lock(0, 0, (void**)&m_pV, 0);
	memcpy(m_pV, &m_vecVertex[0], sizeof(ST_PCT_VERTEX) * m_vecVertex.size());
	m_pVB->Unlock();
}

void cEffectObject::Update()
{
	float t = m_fElapse / m_stInfo.time;
	float speed = pow(1 - t, 2) * m_stInfo.sp0 +
		2 * t *(1 - t) * m_stInfo.sp1 +
		pow(t, 2) * m_stInfo.sp2;
	float scale = pow(1 - t, 2) * m_stInfo.sc0 +
		2 * t *(1 - t) * m_stInfo.sc1 +
		pow(t, 2) * m_stInfo.sc2;
	int alpha = pow(1 - t, 2) * m_stInfo.a0 +
		2 * t *(1 - t) * m_stInfo.a1 +
		pow(t, 2) * m_stInfo.a2;
	float mot = pow(1 - t, 2) * m_stInfo.ms0 +
		2 * t *(1 - t) * m_stInfo.ms1 +
		pow(t, 2) * m_stInfo.ms2;

	m_fElapse += TIMEMANAGER->getElapsedTime();

	if (!m_isFlash)
		m_vPos += m_stInfo.dir * speed;

	m_vMot += m_stInfo.mot * mot;

	for (int i = 0; i < m_vecVertex.size(); i++)
		m_vecVertex[i].c = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	m_pVB->Lock(0, 0, (void**)&m_pV, 0);
	memcpy(m_pV, &m_vecVertex[0], sizeof(ST_PCT_VERTEX) * m_vecVertex.size());
	m_pVB->Unlock();

	//if (m_stInfo.isSphere)
	//{
	//	m_stInfo.rot.x = CAMERA->GetRotation().x;
	//	m_stInfo.rot.y = CAMERA->GetRotation().y;
	//}

	D3DXMATRIX matS, matR, matT;
	D3DXMatrixRotationYawPitchRoll(&matR, m_stInfo.rot.y + m_vMot.y, m_stInfo.rot.x + m_vMot.x, m_stInfo.rot.z + m_vMot.z);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y + m_stInfo.height / 2, m_vPos.z);
	D3DXMatrixScaling(&matS, scale, scale, scale);

	m_matWorld = matS * matR * matT;
}

void cEffectObject::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_stInfo.tex);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PCT_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

bool cEffectObject::IsFinish()
{
	return (m_stInfo.time <= m_fElapse);
}

BoundingSphere cEffectObject::GetBoundSphere()
{
	float t = m_fElapse / m_stInfo.time;
	float scale = pow(1 - t, 2) * m_stInfo.sc0 +
		2 * t *(1 - t) * m_stInfo.sc1 +
		pow(t, 2) * m_stInfo.sc2;

	BoundingSphere sphere = m_stSphere;
	sphere.radius *= scale;
	sphere.center += m_vPos;

	return sphere;
}