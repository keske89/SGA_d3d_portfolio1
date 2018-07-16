#pragma once

#define MAX_FLOOR_TILE 22
//�׸� Ÿ�� Ÿ���� ��ȣ
enum eTileType
{
	TT_FLOOR,
	TT_OBJECT,
	TT_NEWOBJ,
	TT_BLOCK,
	TT_MAX
};
//���� ������ Ÿ�� Ÿ���� ��ȣ
enum eNewObjTileType
{
	NOT_CRATE,
	NOT_BIN,
	NOT_CHOPPINGBOARD,
	NOT_COOKER,
	NOT_PASS,
	NOT_PLATE,
	NOT_PLATERETURNBOX,
	NOT_POT,
	NOT_SINK,
	NOT_TABLE,
	NOT_MAX
};
//���� Ÿ��
enum eCrateType
{
	CT_TOMATO = 00,
	CT_MUSHROOM = 01,
	CT_ONION = 10,
	CT_POTATO = 20,
	CT_MAX = 4
};
//�޴����� ��ȣ
enum eMenuType
{
	MT_FLOOR,
	MT_OBJECT,
	MT_NEWOBJ,
	MT_BLOCK,
	MT_OPEN,
	MT_SAVE,
	MT_LOAD,
	MT_TEXTURE1,
	MT_TEXTURE2,
	MT_TEXTURE3,
	MT_MAX
};
//UI��ư ����ü
struct ST_UI_BUTTON
{
	wstring				wstrTexture;
	D3DXIMAGE_INFO		imageInfo;
	D3DXMATRIX			matrix;
};

class cStageMapToolUI
{
private:
	LPD3DXSPRITE		m_pSprite;						
	ST_UI_BUTTON		m_stFloorTile[MAX_FLOOR_TILE];	//�ٴ� Ÿ�� ��ư
	ST_UI_BUTTON		m_stNewObjTile[NOT_MAX];		//�� ������Ʈ ��ư
	ST_UI_BUTTON		m_stTileSelectButton;			//���� ������ Ÿ���� ��ư
	ST_UI_BUTTON		m_stMenuButton[MT_MAX];			//�޴� ��ư
	ST_UI_BUTTON		m_stMenuSelectButton;			//���� ������ �޴� ��ư
	ST_UI_BUTTON		m_stSubMenuButton;				//���� �޴� ��ư
	ST_UI_BUTTON		m_stSubMenuSelectButton;		//���� �޴� ���� ��ư
	D3DVIEWPORT9		m_VP;							//����Ʈ �޾ƿ� �������

	int					m_nSelectTileNum;				//���� ������ Ÿ�� ��ȣ
	int					m_nTextureNum;					//���� ������Ʈ�� �ؽ��� ����
	eTileType			m_eTileType;					//Ÿ�� Ÿ�� ��ȣ �Ѱ��� ����
	eNewObjTileType		m_eNOTileType;					//�� ������Ʈ Ÿ�� ��ȣ �Ѱ��� ����
	eCrateType			m_eCrateType;					//���� ����
public:
	cStageMapToolUI();
	~cStageMapToolUI();

	void Setup();
	void Update();
	void Render();

	bool SelectTile(int& num);
	bool SelectMenu(int& num);
	bool SelectNewObj(int& num);
	bool SelectSubMenu();
	inline eTileType getTileType() { return m_eTileType; }
	inline eNewObjTileType getNewObjTileType() { return m_eNOTileType; }
	inline eCrateType getCrateType() { return m_eCrateType; }
	inline wstring getTileTexture(int num) { return m_stFloorTile[num].wstrTexture; }
	inline void setTextureNum(int num) { m_nTextureNum = num; }
};

