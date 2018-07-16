#pragma once

class cStage 
{
private:
	LPD3DXMESH						m_pMesh;
	vector<wstring>					m_vecTex;
	vector<pair<int, D3DXMATRIX>>	m_vecNewObjData;
	vector<pair<int, D3DXMATRIX>>	m_vecSetObjData;
	map<pair<int, int>, int>		m_mapIsBlockedData;
	D3DXVECTOR3						m_vecChefPos[2];
public:
	cStage();
	~cStage();

	void Setup(int stageNum);
	void Update();
	void Render();
	vector<pair<int, D3DXMATRIX>> GetNewObjData() { return m_vecNewObjData; }
	vector<pair<int, D3DXMATRIX>> GetSetObjData() { return m_vecSetObjData; }
};

