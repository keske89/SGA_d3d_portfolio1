#pragma once

#define MAX_FLOOR_TILE 22
//그릴 타일 타잎의 번호
enum eTileType
{
	TT_FLOOR,
	TT_OBJECT,
	TT_NEWOBJ,
	TT_BLOCK,
	TT_MAX
};
//새로 생성할 타일 타잎의 번호
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
//상자 타잎
enum eCrateType
{
	CT_TOMATO = 00,
	CT_MUSHROOM = 01,
	CT_ONION = 10,
	CT_POTATO = 20,
	CT_MAX = 4
};
//메뉴들의 번호
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
//UI버튼 구조체
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
	ST_UI_BUTTON		m_stFloorTile[MAX_FLOOR_TILE];	//바닥 타일 버튼
	ST_UI_BUTTON		m_stNewObjTile[NOT_MAX];		//뉴 오브젝트 버튼
	ST_UI_BUTTON		m_stTileSelectButton;			//현재 선택한 타일의 버튼
	ST_UI_BUTTON		m_stMenuButton[MT_MAX];			//메뉴 버튼
	ST_UI_BUTTON		m_stMenuSelectButton;			//현재 선택한 메뉴 버튼
	ST_UI_BUTTON		m_stSubMenuButton;				//서브 메뉴 버튼
	ST_UI_BUTTON		m_stSubMenuSelectButton;		//서브 메뉴 선택 버튼
	D3DVIEWPORT9		m_VP;							//뷰포트 받아올 멤버변수

	int					m_nSelectTileNum;				//현재 선택한 타일 번호
	int					m_nTextureNum;					//현재 오브젝트의 텍스쳐 갯수
	eTileType			m_eTileType;					//타일 타잎 번호 넘겨줄 변수
	eNewObjTileType		m_eNOTileType;					//뉴 오브젝트 타일 번호 넘겨줄 변수
	eCrateType			m_eCrateType;					//상자 종류
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

