#pragma once
#include "cGameNode.h"
#include "cRay.h"
#include "cObjLoader.h"
#define TOKEN_SIZE 128

class cCamera;
class cStageGrid;
class cStageMapToolUI;

class cStageMapTool : public cGameNode
{
public:
	struct ST_TILE	//Ÿ�� ����ü
	{
		vector<ST_PNT_VERTEX>	vecVertex;
		D3DXMATRIX				matFinal;
		wstring					wstrTexture;
	};
private:
	cCamera*						m_pCamera;				
	cStageGrid*						m_pGrid;				
	cStageMapToolUI*				m_pUI;					
	D3DXVECTOR3						m_vecPos;				//ī�޶� ��� ������
	ST_TILE							m_stFloorTileTemplate;	//���ø� �ٴ� Ÿ��
															
	int								m_nTextureNum;			//�ٴ�Ÿ�� �ؽ��� ��ȣ
	int								m_nIndexX;				//�׸��� x�� �ε���
	int								m_nIndexZ;				//�׸��� z�� �ε���
	float							m_fRotAngle;			//Ÿ�� ȸ�� ����
	float							m_fTBRXAxis;			//Ÿ�� ȸ�� �� ��ġ ���� x��ǥ
	float							m_fTBRZAxis;			//Ÿ�� ȸ�� �� ��ġ ���� z��ǥ

	map<pair<int, int>, ST_TILE>			m_mapFloorTiles;			//�ٴ� Ÿ�� ���� ���� �����̳�
	map<pair<int, int>, ST_TILE>::iterator	m_iterFloorTiles;			//������ �ݺ���
	map<pair<int, int>, vector<ST_TILE>>			m_mapObjectTiles;	//������Ʈ Ÿ�� ���� ���� �����̳�
	map<pair<int, int>, vector<ST_TILE>>::iterator	m_iterObjectTiles;	//������ �ݺ���
	vector<ST_TILE>					m_vecObjectSample;					//���ø� ������Ʈ

	wstring wstrTest;
public:
	cStageMapTool();
	~cStageMapTool();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Control();
	void LoadObject(LPCTSTR fullpath, vector<ST_TILE>& objectVector);
};

