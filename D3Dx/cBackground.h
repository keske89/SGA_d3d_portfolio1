#pragma once
class cBackground
{
private:
	LPD3DXMESH m_pMesh;
	LPD3DXMESH m_pSkyMesh;
	D3DXMATRIX m_matSky;
	D3DXMATRIX m_matWorld[2];
	wstring m_strBackgroundName[3];
public:
	cBackground();
	~cBackground();

	void Setup(int num);
	void Render(int num);

	void AddVertex(vector<ST_PNT_VERTEX>& vector, D3DXVECTOR3 vp, D3DXVECTOR2 vt);
	void AddNormalVector(vector<ST_PNT_VERTEX>& vector);
	void SetReverse(vector<ST_PNT_VERTEX>& vector);
	void SetupMaterials();
};

