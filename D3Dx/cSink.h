#pragma once
#include "cActionObj.h"

class cSink : public cActionObj
{
private:
	LPD3DXMESH m_pMesh2;
	LPDIRECT3DTEXTURE9 m_pTexture2;
public:
	cSink();
	~cSink();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void SetWorldMat(D3DXMATRIX matWorld);
	virtual void Setup(D3DXMATRIX matWorld, D3DXVECTOR3 pos, int lidtype);
	virtual void SetLight() override;
	void Inventory();
};


