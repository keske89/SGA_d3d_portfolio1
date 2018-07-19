#pragma once
#include "cIGObj.h"



class cIGObj;
class cChef;




// action obj
class cCrateLid;

class cChoppingBoard;

class cPot;
class cCooker;

class cSink;
class cBin;

class cPass;
class cPassScroll;

class cPlate;
class cPlateReturnBox;

class cTomato;
class cCounterTop;


class cOnion;
class cKnife;

enum OBJECTTYPE
{
	// CRATE = 10~ 
	//CRATE_LID = 10,
	CRATE_TOMATO = 11,
	CRATE_POTATO = 12,
	CRATE_MUSHROOM = 13,
	CRATE_ONION = 14,

	// ACTION OBJ 20~

	AOBJ_BIN = 20,
	AOBJ_CHOPPIGNBOARD = 21,
	AOBJ_COOKER = 22,
	//AOBJ_KNIFE = 23,
	AOBJ_PASS = 23,
	//AOBJ_PASSSCROLL = 25,
	AOBJ_PLATE = 24,
	AOBJ_PLATERETURNBOX = 25,
	AOBJ_POT = 26,
	AOBJ_SINK = 27,
	AOBJ_TABLE = 28,
	AOBJ_TABLE2 = 29, // ����
	AOBJ_TABLE3 = 30, // ����

	// FOOD OBJ 31~
	FOBJ_POTATO = 34,
	FOBJ_TOMATO = 31,
	FOBJ_MUSHROOM = 32,
	FOBJ_ONION = 33,

};

enum BUTTONSELECT
{
	BUTTON_1,
	BUTTON_2,
	BUTTON_END
};

class cStageObjManager : public cActionDelegate
{
private:
	
	cCrateLid*				m_crateLid;
	cSink*					m_Sink;
	cCooker*				m_Cooker;
	cChoppingBoard*			m_ChoppingBoard;
	cPot*					m_Pot;
	cBin*					m_Bin;
	cPass*					m_Pass;
	cPlate*					m_Plate;
	cPlateReturnBox*		m_PlateReturnBox;
	cTomato*				m_Tomato;
	cCounterTop*			m_Counter;
	cOnion*					m_Onion;
	cKnife*					m_Knife;

	int						m_buttonSelect;
	SYNTHESIZE(std::list<cIGObj*>, m_listObj, ListObj);
	SYNTHESIZE(std::list<cIGObj*>, m_listFoodObj, ListFoodObj);
	SYNTHESIZE(cActionDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(cChef*, m_player1, player1);
	SYNTHESIZE(cChef*, m_player2, player2);

public:
	cStageObjManager();
	~cStageObjManager();

	void Setup();
	void Update();
	void Render();
	void DeleteObject(std::list<cIGObj*>::iterator objectIter);
	void DeleteFood(cIGObj * foodPointer);

	// cActionDelegate��(��) ���� ��ӵ�

	virtual void OnAction(cIGObj* pSender) override;
	void ObjAction(cChef* pSender);
	
	std::list<cIGObj*>::iterator SetIngameObject(OBJECTTYPE objtype, D3DXMATRIX matWorld);
};

