#pragma once

#define GRID_MAX 25

class cGrid
{
private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXVECTOR3				m_vPosition;
	D3DXMATRIX				m_matWorld;

public:
	cGrid();
	~cGrid();

	void Setup();
	void Update();
	void Render();

	void Draw3DLine(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DCOLOR color);
};

