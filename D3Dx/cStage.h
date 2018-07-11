#pragma once

class cStage 
{
private:
	LPD3DXMESH			m_pMesh;
	vector<wstring>		m_vecTex;
public:
	cStage();
	~cStage();

	void Setup(int stageNum);
	void Update();
	void Render();
};

