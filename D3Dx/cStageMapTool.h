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
	struct ST_TILE	//타일 구조체
	{
		vector<ST_PNT_VERTEX>	vecVertex;
		D3DXMATRIX				matFinal;
		wstring					wstrTexture;
	};
private:
	cCamera*						m_pCamera;				
	cStageGrid*						m_pGrid;				
	cStageMapToolUI*				m_pUI;					
	D3DXVECTOR3						m_vecPos;				//카메라 룩앳 포지션
	ST_TILE							m_stFloorTileTemplate;	//템플릿 바닥 타일
															
	int								m_nTextureNum;			//바닥타일 텍스쳐 번호
	int								m_nIndexX;				//그리드 x축 인덱스
	int								m_nIndexZ;				//그리드 z축 인덱스
	float							m_fRotAngle;			//타일 회전 각도
	float							m_fTBRXAxis;			//타일 회전 전 위치 보정 x좌표
	float							m_fTBRZAxis;			//타일 회전 전 위치 보정 z좌표

	map<pair<int, int>, ST_TILE>			m_mapFloorTiles;			//바닥 타일 정보 저장 컨테이너
	map<pair<int, int>, ST_TILE>::iterator	m_iterFloorTiles;			//위에꺼 반복자
	map<pair<int, int>, vector<ST_TILE>>			m_mapObjectTiles;	//오브젝트 타일 정보 저장 컨테이너
	map<pair<int, int>, vector<ST_TILE>>::iterator	m_iterObjectTiles;	//위에꺼 반복자
	vector<ST_TILE>					m_vecObjectSample;					//템플릿 오브젝트

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

