#pragma once
#include "cGameNode.h"
#include "cRay.h"
#include "cObjLoader.h"
#define TOKEN_SIZE 128
#define BLOCK_HEIGHT 5.0f

class cCamera;
class cStageGrid;
class cStageMapToolUI;
class cStageObjManager;
class cIGObj;
class cActionObj;
class cBackground;

class cStageMapTool : public cGameNode
{
public:
	struct ST_NEWOBJ
	{
		list<cIGObj*>::iterator iter;
		cIGObj*					p;
		D3DXMATRIX				matFinal;
		int						type;
	};
	struct ST_TILE	//Ÿ�� ����ü
	{
		vector<ST_PNT_VERTEX>	vecVertex;
		D3DXMATRIX				matFinal;
		wstring					wstrTexture;
	};
private:
	cCamera*				m_pCamera;				
	cStageGrid*				m_pGrid;				
	cStageMapToolUI*		m_pUI;		
	cStageObjManager*		m_pSOM;
	cBackground*			m_pBG;

	D3DXVECTOR3				m_vecPos;				//ī�޶� ��� ������
													
	int						m_nTextureNum;			//�ٴ�Ÿ�� �ؽ��� ��ȣ
	int						m_nMenuNum;				//������ �޴� ��ȣ
	int						m_nNewObjNum;			//��������Ʈ ��ȣ
	int						m_nIndexX;				//�׸��� x�� �ε���
	int						m_nIndexZ;				//�׸��� z�� �ε���
	unsigned int			m_nCharacterSelect;		//ĳ���� ���� ��ȣ
	float					m_fRotAngle;			//Ÿ�� ȸ�� ����
	float					m_fTBRXAxis;			//Ÿ�� ȸ�� �� ��ġ ���� x��ǥ
	float					m_fTBRZAxis;			//Ÿ�� ȸ�� �� ��ġ ���� z��ǥ

	map<pair<int, int>, ST_TILE>					m_mapFloorTiles;		//�ٴ� Ÿ�� ���� ���� �����̳�
	map<pair<int, int>, ST_TILE>::iterator			m_iterFloorTiles;		//������ �ݺ���
	map<pair<int, int>, vector<ST_TILE>>			m_mapObjectTiles;		//������Ʈ Ÿ�� ���� ���� �����̳�
	map<pair<int, int>, vector<ST_TILE>>::iterator	m_iterObjectTiles;		//������ �ݺ���
	map<pair<int, int>, ST_NEWOBJ>					m_mapNewObject;			//New�� �������ִ� ������Ʈ
	map<pair<int, int>, ST_NEWOBJ>::iterator		m_iterNewObject;		//������ �ݺ���
	map<pair<int, int>, ST_NEWOBJ>					m_mapSetObject;			//NewObj�� �������ִ� ������Ʈ
	map<pair<int, int>, ST_NEWOBJ>::iterator		m_iterSetObject;		//������ �ݺ���
	map<pair<int, int>, ST_TILE>					m_mapBlockTiles;		//���� Ÿ�� ���� ���� �����̳�
	map<pair<int, int>, ST_TILE>::iterator			m_iterBlockTiles;		//������ �ݺ���
	vector<ST_TILE>									m_vecObjectTemplate;	//���ø� ������Ʈ
	ST_TILE											m_stFloorTemplate;		//���ø� �ٴ� Ÿ��
	ST_TILE											m_stBlockTemplate;		//���ø� ���� ������Ʈ
	ST_NEWOBJ										m_stNewObjTemplate;		//���ø� �� ������Ʈ
	ST_TILE											m_stChefLocation[2];	//���ø� ���� ������Ʈ

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
	void MenuOpen();
	void MenuSave();
	void MenuLoad();
	void MenuTexture(int menuNum);
	int getObjectType(bool& isSetObject);
};

