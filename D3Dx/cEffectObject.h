#pragma once
#include "cWMDefinition.h"

class cEffectObject
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	vector<ST_PCT_VERTEX>	m_vecVertex;
	ST_PCT_VERTEX*			m_pV;

	SYNTHESIZE(ST_EFFECT, m_stInfo, Info);

private:
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vMot;
	D3DXMATRIX		m_matWorld;
	float			m_fElapse;
	bool			m_isFlash;

	BoundingSphere	m_stSphere;

public:
	cEffectObject();
	~cEffectObject();

	void Setup(ST_EFFECT info, D3DXVECTOR3 pos);
	void Update();
	void Render();
	bool IsFinish();

	BoundingSphere GetBoundSphere();
};


