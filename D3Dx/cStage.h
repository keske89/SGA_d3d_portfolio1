#pragma once
#define MAX_VEC_SIZE 45000
class cStage 
{
private:
	vector<LPD3DXMESH>				m_vecMesh;
	vector<wstring>					m_vecTex;
	int								m_nSoundNum;
public:
	cStage();
	~cStage();

	void Setup(int stageNum, vector<pair<int, D3DXMATRIX>>& vecNewObj, vector<pair<int, D3DXMATRIX>>& vecSetObj, map<pair<int, int>, int>& mapBlock, D3DXVECTOR3& player1Location, D3DXVECTOR3& player2Location);
	void Update();
	void Render();

	void SetupMaterials();
};

