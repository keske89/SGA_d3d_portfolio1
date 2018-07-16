#pragma once

class cStage 
{
private:
	LPD3DXMESH						m_pMesh;
	vector<wstring>					m_vecTex;
public:
	cStage();
	~cStage();

	void Setup(int stageNum, vector<pair<int, D3DXMATRIX>>& vecNewObj, vector<pair<int, D3DXMATRIX>>& vecSetObj, map<pair<int, int>, int>& mapBlock, D3DXVECTOR3& player1Location, D3DXVECTOR3& player2Location);
	void Update();
	void Render();
};

