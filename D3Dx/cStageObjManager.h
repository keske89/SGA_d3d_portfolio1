#pragma once
#include "cIGObj.h"

typedef 

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

	// FOOD OBJ 30~
	FOBJ_POTATO = 30,
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
	
	int m_buttonSelect;
	SYNTHESIZE(std::list<cIGObj*>, m_listObj, ListObj);


public:
	cStageObjManager();
	~cStageObjManager();

	void Setup();
	void Update();
	void Render();
	void DeleteObject(std::list<cIGObj*>::iterator objectIter);

	void ActionControl();	

	// cActionDelegate을(를) 통해 상속됨

	virtual void OnAction(cIGObj* pSender) override;
	
	std::list<cIGObj*>::iterator SetIngameObject(OBJECTTYPE objtype, D3DXMATRIX matWorld);
};

